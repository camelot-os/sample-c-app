/*
 * SPDX-License-Identifier: Apache-2.0
 *
 * Copyright 2023 Ledger SAS
 */

#include <stdio.h>
#include <uapi.h>
#include <platform.h>
#include <types.h>
#include <libecc/hash/sha256.h>


#define RUST_HELLO_APP_ID 0xC001F001UL


void hexdump(const u8 *buf, u16 buflen)
{
	u32 i;

	if (buf == NULL) {
		goto err;
	}
    printf("SHA256: 0x");
	for (i = 0; i < (u32)buflen; i++) {
		printf("%02x", buf[i]);
	}
	printf("\n");

err:
	return;
}

sha256_context ctx;
uint8_t data[SENTRY_SVCEXCHANGE_LEN] = {0};

void handle_messages(taskh_t handle)
{
    Status ret;
    exchange_event_t *header;
    uint8_t sha256_buffer[32] = {0};

    int32_t timeout = 0L; /* unlimited wait */

    ret = __sys_wait_for_event(EVENT_TYPE_IPC, 1000UL);
    if (ret != STATUS_OK) {
        return;
    }
    copy_from_kernel(data, SENTRY_SVCEXCHANGE_LEN);
    header = (exchange_event_t*)&data[0];
    uint32_t source = header->source;
    char *content = (char*)&header->data[0];
    printf("IPC received, calculating SHA256\n");
    sha256_init(&ctx);
    sha256_update(&ctx, content, header->length);
    sha256_final(&ctx, sha256_buffer);
    hexdump(sha256_buffer, 32);
    return;
}

int main(void)
{
    taskh_t handle = 0;
    Status ret;
    SleepDuration duration;
    int32_t timeout = 100L; /* milisecond timeout */
    exchange_event_t *header;
    uint32_t sleep_time = 1000UL;
    duration.tag = SLEEP_DURATION_ARBITRARY_MS;
    duration.arbitrary_ms = sleep_time;

    //const char *hello_msg = "Hello, World from sample C app\n";

    //printf(hello_msg);
    /* staying on UAPI bare API, while shield do not yet offer other than POSIX-like */
    if (__sys_get_process_handle(RUST_HELLO_APP_ID) != STATUS_OK) {
        printf("Rust hello app is not running, exiting\n");
        return -1;
    }
    copy_from_kernel((uint8_t*)&handle, sizeof(taskh_t));


    while (1) {
        handle_messages(handle);
    	__sys_sleep(duration, SLEEP_MODE_DEEP);
    }
    return 0;
}
