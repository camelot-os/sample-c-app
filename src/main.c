/*
 * SPDX-License-Identifier: Apache-2.0
 *
 * Copyright 2023 Ledger SAS
 */

#include <stdio.h>
#include <uapi.h>
#include <types.h>
#include <libecc/hash/sha256.h>

int main(void)
{
    SleepDuration duration;
    uint32_t sleep_time = 1000UL;
    duration.tag = SLEEP_DURATION_ARBITRARY_MS;
    duration.arbitrary_ms = sleep_time;

    const char *hello_msg = "Hello, World from sample C app\n";
    sha256_context ctx;
    sha256_init(&ctx);
    sha256_update(&ctx, hello_msg, strlen(hello_msg));
    while (1) {
    	printf(hello_msg);
    	__sys_sleep(duration, SLEEP_MODE_DEEP);
    }
    return 0;
}
