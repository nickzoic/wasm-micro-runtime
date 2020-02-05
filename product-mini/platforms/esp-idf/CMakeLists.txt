# from ESP-IDF 4.0 examples/build_system/cmake/idf_as_lib
cmake_minimum_required(VERSION 3.5)
project(idf_as_lib C)

enable_language (ASM)

# Include for ESP-IDF build system functions
include($ENV{IDF_PATH}/tools/cmake/idf.cmake)
# Create idf::esp32 and idf::freertos static libraries
idf_build_process(esp32
                # try and trim the build; additional components
                # will be included as needed based on dependency tree
                #
                # although esptool_py does not generate static library,
                # processing the component is needed for flashing related
                # targets and file generation
                COMPONENTS esp32 freertos esptool_py
                SDKCONFIG ${CMAKE_BINARY_DIR}/sdkconfig
                BUILD_DIR ${CMAKE_BINARY_DIR})

include_directories(
    ../../../core/shared/platform/esp-idf/
    ../../../core/shared/platform/include/
    ../../../core/shared/include/
    ../../../core/iwasm/include/
)

include_directories(
    build/config/
    xtensa/include/
    $ENV{IDF_PATH}/components/esp32/include/
    $ENV{IDF_PATH}/components/esp_common/include/
    $ENV{IDF_PATH}/components/esp_rom/include/
    $ENV{IDF_PATH}/components/freertos/include/
    $ENV{IDF_PATH}/components/heap/include/
    $ENV{IDF_PATH}/components/soc/esp32/include/
    $ENV{IDF_PATH}/components/xtensa/include/
    $ENV{IDF_PATH}/components/xtensa/esp32/include/
)

set(WAMR_BUILD_PLATFORM "esp-idf")
set(WAMR_BUILD_TARGET "XTENSA")
set(WAMR_BUILD_INTERP 1)
set(WAMR_BUILD_AOT 1)
set(WAMR_BUILD_JIT 0)
set(WAMR_BUILD_LIBC_BUILTIN 0)
set(WAMR_BUILD_LIBC_WASI 0)
set(WAMR_ROOT_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../../..)

include (${WAMR_ROOT_DIR}/build-scripts/runtime_lib.cmake)
add_library(vmlib ${WAMR_RUNTIME_LIB_SOURCE})

set(elf_file ${CMAKE_PROJECT_NAME}.elf)
add_executable(${elf_file} main.c ext_lib_export.c)

add_library(wamr STATIC ../../../core/shared/platform/esp-idf/bh_time.c)

# Link the static libraries to the executable
target_link_libraries(${elf_file} idf::esp32 idf::freertos idf::spi_flash wamr vmlib)

# Attach additional targets to the executable file for flashing,
# linker script generation, partition_table generation, etc.
idf_build_executable(${elf_file})

set(CMAKE_EXPORT_COMPILE_COMMANDS 1)
