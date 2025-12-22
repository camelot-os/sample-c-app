/*
 * SPDX-License-Identifier: Apache-2.0
 *
 * Copyright 2023 Ledger SAS
 */

#include <stdio.h>
#include <uapi.h>
#include <types.h>

int main(void)
{
    SleepDuration duration;
    uint32_t sleep_time = 1000UL;
    duration.tag = SLEEP_DURATION_ARBITRARY_MS;
    duration.arbitrary_ms = sleep_time;


    while (1) {
    	printf("Hello, World from sample C app\n");
    	__sys_sleep(duration, SLEEP_MODE_DEEP);
    }
    return 0;
}
