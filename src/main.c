/*
 * SPDX-License-Identifier: Apache-2.0
 *
 * Copyright 2023 Ledger SAS
 */

#include <stdio.h>
#include <uapi.h>
#include <types.h>
#include <libecc/hash/sha256.h>

void hexdump(const u8 *buf, u16 buflen)
{
	u32 i;

	if (buf == NULL) {
		goto err;
	}
	for (i = 0; i < (u32)buflen; i++) {
		printf("%02x", buf[i]);
	}
	printf("\n");

err:
	return;
}

int main(void)
{
    SleepDuration duration;
    uint32_t sleep_time = 1000UL;
    duration.tag = SLEEP_DURATION_ARBITRARY_MS;
    duration.arbitrary_ms = sleep_time;
    uint8_t sha256_buffer[32] = {0};

    const char *hello_msg = "Hello, World from sample C app\n";
    sha256_context ctx;
    sha256_init(&ctx);
    sha256_update(&ctx, hello_msg, strlen(hello_msg));
    sha256_final(&ctx, sha256_buffer);
    while (1) {
    	printf(hello_msg);
        hexdump(ctx.sha256_buffer, 32);
    	__sys_sleep(duration, SLEEP_MODE_DEEP);
    }
    return 0;
}
