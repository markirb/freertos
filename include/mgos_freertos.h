/*
 * Copyright (c) 2014-2019 Cesanta Software Limited
 * All rights reserved
 *
 * Licensed under the Apache License, Version 2.0 (the ""License"");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an ""AS IS"" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#pragma once

#include <stdbool.h>

#include "freertos/FreeRTOS.h"
#include "freertos/queue.h"
#include "freertos/task.h"

#include "mgos_init.h"
#include "mongoose.h"

#ifndef MGOS_TASK_STACK_SIZE_BYTES
#define MGOS_TASK_STACK_SIZE_BYTES 8192
#endif

#ifndef MGOS_TASK_PRIORITY
#define MGOS_TASK_PRIORITY 5
#endif

#ifndef MGOS_BG_TASK_PRIORITY
#ifndef STM32L4
#define MGOS_BG_TASK_PRIORITY 1  // Set to 0 to disable
#else
// L4 places .bss in SRAM2 and there just isn't enough of it.
#define MGOS_BG_TASK_PRIORITY 0
#endif
#endif

#ifndef MGOS_TASK_QUEUE_LENGTH
#define MGOS_TASK_QUEUE_LENGTH 32
#endif

#ifndef MGOS_MONGOOSE_MAX_POLL_SLEEP_MS
#define MGOS_MONGOOSE_MAX_POLL_SLEEP_MS 1000
#endif

#ifndef MGOS_EARLY_WDT_TIMEOUT
#define MGOS_EARLY_WDT_TIMEOUT 30 /* seconds */
#endif

#if CS_PLATFORM == CS_P_ESP32
#define MGOS_TASK_STACK_SIZE_UNIT 1
#else
#define MGOS_TASK_STACK_SIZE_UNIT sizeof(portSTACK_TYPE)
#endif

#ifdef __cplusplus
extern "C" {
#endif

void mgos_freertos_run_mgos_task(bool start_scheduler);

extern enum mgos_init_result mgos_freertos_pre_init(void);

void mgos_freertos_core_dump(void);

// This function extracts registers from the task's stack frame
// and populates GDB stack frame.
size_t mgos_freertos_extract_regs(StackType_t *sp, void *buf, size_t buf_size);

#ifdef __cplusplus
}
#endif
