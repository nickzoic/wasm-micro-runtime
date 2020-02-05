/* Hello World Example

   This example code is in the Public Domain (or CC0 licensed, at your option.)

   Unless required by applicable law or agreed to in writing, this
   software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
   CONDITIONS OF ANY KIND, either express or implied.
*/
#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "esp_spi_flash.h"

#include "wasm_export.h"
#include "bh_time.h"
#include "bh_log.h"

#include "test_wasm.h"

#define CONFIG_GLOBAL_HEAP_BUF_SIZE 131072
#define CONFIG_APP_STACK_SIZE 8192
#define CONFIG_APP_HEAP_SIZE 8192
#define CONFIG_MAIN_THREAD_STACK_SIZE 4096

static char global_heap_buf[CONFIG_GLOBAL_HEAP_BUF_SIZE] = { 0 };
static char *argv[1] = { "x" };

void app_main()
{
    wasm_module_t wasm_module = NULL;
    wasm_module_inst_t wasm_module_inst = NULL;
    char error_buf[128];
    const char *exception;

    if (bh_memory_init_with_pool(global_heap_buf, sizeof(global_heap_buf))
        != 0) {
        bh_printf("Init global heap failed.\n");
        return;
    }

    //bh_memory_init_with_allocator(malloc, free);

    wasm_runtime_init();

    bh_log_set_verbose_level(5);

    vTaskDelay(1000 / portTICK_PERIOD_MS);

    bh_printf("wasm_runtime_load\n");

    wasm_module = wasm_runtime_load(wasm_test_file, sizeof(wasm_test_file), error_buf, sizeof(error_buf));
    if (!wasm_module) { bh_printf("1 %s\n", error_buf); goto fail; }
   
    vTaskDelay(1000 / portTICK_PERIOD_MS);

    bh_printf("wasm_runtime_instantiate\n");

    wasm_module_inst = wasm_runtime_instantiate(wasm_module, CONFIG_APP_STACK_SIZE, CONFIG_APP_HEAP_SIZE, error_buf, sizeof(error_buf));

    if (!wasm_module_inst) { bh_printf("2 %s\n", error_buf); goto fail; }

    vTaskDelay(1000 / portTICK_PERIOD_MS);

    bh_printf("wasm_application_execute_main\n");

    wasm_application_execute_main(wasm_module_inst, 1, argv);

    vTaskDelay(1000 / portTICK_PERIOD_MS);

    bh_printf("wasm_runtime_get_exception\n");

    exception = wasm_runtime_get_exception(wasm_module_inst);

    if (exception) { bh_printf("3 %s\n", exception); }

fail:

    vTaskDelay(1000 / portTICK_PERIOD_MS);
    printf("Restarting now.\n");
    esp_restart();
}
