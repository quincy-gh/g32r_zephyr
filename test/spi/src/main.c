/*
 * Copyright (c) 2026, Quincy.W <wangqyfm@foxmail.com>
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * On-target ztest for the G32R5 SPI driver. SPI_MODE_LOOP closes the
 * internal SIMO-to-SOMI path, so the suite does not need a second
 * device or a pin. It checks the shifter, the character-length mask
 * and the LSPCLK baud limits. It does not measure SCLK on a pin.
 */

#include <stdint.h>
#include <string.h>

#include <zephyr/drivers/spi.h>
#include <zephyr/kernel.h>
#include <zephyr/ztest.h>

#define SPI_HZ 1000000U

static const struct device *const spia = DEVICE_DT_GET(DT_NODELABEL(spia));

#if DT_NODE_EXISTS(DT_NODELABEL(spib)) && DT_NODE_HAS_STATUS(DT_NODELABEL(spib), okay)
static const struct device *const spib = DEVICE_DT_GET(DT_NODELABEL(spib));
#endif

static uint32_t spi_op(uint32_t word_bits, uint32_t extra)
{
	return SPI_OP_MODE_CONTROLLER | SPI_WORD_SET(word_bits) | SPI_MODE_LOOP | extra;
}

static void loopback_bytes(const struct device *spi, uint32_t extra, const uint8_t *tx,
			   size_t len)
{
	uint8_t rx[32];
	const struct spi_buf txb = {
		.buf = (void *)tx,
		.len = len,
	};
	const struct spi_buf rxb = {
		.buf = rx,
		.len = len,
	};
	const struct spi_buf_set txs = {
		.buffers = &txb,
		.count = 1,
	};
	const struct spi_buf_set rxs = {
		.buffers = &rxb,
		.count = 1,
	};
	const struct spi_config cfg = {
		.frequency = SPI_HZ,
		.operation = spi_op(8, extra),
	};

	zassert_true(len <= sizeof(rx));
	memset(rx, 0xA5, len);
	zassert_ok(spi_transceive(spi, &cfg, &txs, &rxs));
	zassert_mem_equal(rx, tx, len);
}

static void test_controller(const struct device *spi)
{
	static const uint8_t pattern[] = {0x00, 0xFF, 0xA5, 0x5A, 0x01, 0x80, 0x7E, 0x12};
	static const uint16_t words[] = {0x0000, 0xFFFF, 0x1234, 0xABCD};
	uint16_t rx_words[4];
	uint8_t rx4;
	uint8_t tx4 = 0x1B;
	uint8_t rx_pad[4];
	uint8_t tx_short[2] = {0x11, 0x22};
	const struct spi_buf txb16 = {
		.buf = (void *)words,
		.len = sizeof(words),
	};
	const struct spi_buf rxb16 = {
		.buf = rx_words,
		.len = sizeof(rx_words),
	};
	const struct spi_buf_set txs16 = {
		.buffers = &txb16,
		.count = 1,
	};
	const struct spi_buf_set rxs16 = {
		.buffers = &rxb16,
		.count = 1,
	};
	const struct spi_config cfg16 = {
		.frequency = SPI_HZ,
		.operation = spi_op(16, 0),
	};
	const struct spi_buf txb4 = {
		.buf = &tx4,
		.len = 1,
	};
	const struct spi_buf rxb4 = {
		.buf = &rx4,
		.len = 1,
	};
	const struct spi_buf_set txs4 = {
		.buffers = &txb4,
		.count = 1,
	};
	const struct spi_buf_set rxs4 = {
		.buffers = &rxb4,
		.count = 1,
	};
	const struct spi_config cfg4 = {
		.frequency = SPI_HZ,
		.operation = spi_op(4, 0),
	};
	const struct spi_buf tx_short_b = {
		.buf = tx_short,
		.len = sizeof(tx_short),
	};
	const struct spi_buf rx_pad_b = {
		.buf = rx_pad,
		.len = sizeof(rx_pad),
	};
	const struct spi_buf_set txs_short = {
		.buffers = &tx_short_b,
		.count = 1,
	};
	const struct spi_buf_set rxs_pad = {
		.buffers = &rx_pad_b,
		.count = 1,
	};
	const struct spi_config cfg8 = {
		.frequency = SPI_HZ,
		.operation = spi_op(8, 0),
	};
	struct spi_config bad;
	uint8_t one = 0x5A;
	uint8_t odd[3];
	const struct spi_buf oddb = {
		.buf = odd,
		.len = sizeof(odd),
	};
	const struct spi_buf_set odds = {
		.buffers = &oddb,
		.count = 1,
	};

	zassert_true(device_is_ready(spi));

	loopback_bytes(spi, 0, pattern, sizeof(pattern));
	loopback_bytes(spi, SPI_MODE_CPHA, pattern, sizeof(pattern));
	loopback_bytes(spi, SPI_MODE_CPOL, pattern, sizeof(pattern));
	loopback_bytes(spi, SPI_MODE_CPOL | SPI_MODE_CPHA, pattern, sizeof(pattern));

	memset(rx_words, 0, sizeof(rx_words));
	zassert_ok(spi_transceive(spi, &cfg16, &txs16, &rxs16));
	zassert_mem_equal(rx_words, words, sizeof(words));

	/* 4-bit frame keeps the low nibble. 0x1B must come back as 0x0B. */
	rx4 = 0xFF;
	zassert_ok(spi_transceive(spi, &cfg4, &txs4, &rxs4));
	zassert_equal(rx4, 0x0B);

	memset(rx_pad, 0xA5, sizeof(rx_pad));
	zassert_ok(spi_transceive(spi, &cfg8, &txs_short, &rxs_pad));
	zassert_equal(rx_pad[0], 0x11);
	zassert_equal(rx_pad[1], 0x22);
	zassert_equal(rx_pad[2], 0x00);
	zassert_equal(rx_pad[3], 0x00);

	bad = cfg8;
	bad.operation = SPI_OP_MODE_PERIPHERAL | SPI_WORD_SET(8) | SPI_MODE_LOOP;
	zassert_equal(spi_transceive(spi, &bad, &txs_short, &rxs_pad), -ENOTSUP);

	bad.operation = spi_op(8, SPI_TRANSFER_LSB);
	zassert_equal(spi_transceive(spi, &bad, &txs_short, &rxs_pad), -ENOTSUP);

	bad.operation = spi_op(0, 0);
	zassert_equal(spi_transceive(spi, &bad, &txs_short, &rxs_pad), -EINVAL);

	bad.operation = spi_op(17, 0);
	zassert_equal(spi_transceive(spi, &bad, &txs_short, &rxs_pad), -EINVAL);

	bad = cfg8;
	bad.frequency = 0U;
	zassert_equal(spi_transceive(spi, &bad, &txs_short, &rxs_pad), -EINVAL);

	bad.frequency = 1U;
	zassert_equal(spi_transceive(spi, &bad, &txs_short, &rxs_pad), -EINVAL);

	bad.frequency = 50000000U;
	zassert_equal(spi_transceive(spi, &bad, &txs_short, &rxs_pad), -EINVAL);

	bad = cfg16;
	zassert_equal(spi_transceive(spi, &bad, &odds, &odds), -EINVAL);

	bad = cfg8;
	bad.operation |= SPI_LOCK_ON;
	zassert_ok(spi_transceive(spi, &bad,
				  &(struct spi_buf_set){
					  .buffers = &(struct spi_buf){.buf = &one, .len = 1},
					  .count = 1,
				  },
				  NULL));
	zassert_ok(spi_release(spi, &bad));
}

ZTEST(g32r5_spi, test_spia_loopback)
{
	test_controller(spia);
}

#if DT_NODE_EXISTS(DT_NODELABEL(spib)) && DT_NODE_HAS_STATUS(DT_NODELABEL(spib), okay)
ZTEST(g32r5_spi, test_spib_loopback)
{
	test_controller(spib);
}
#endif

ZTEST_SUITE(g32r5_spi, NULL, NULL, NULL, NULL, NULL);
