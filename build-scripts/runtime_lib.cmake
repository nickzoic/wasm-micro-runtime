# Copyright (C) 2019 Intel Corporation. All rights reserved.
# SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception


if (NOT DEFINED WAMR_ROOT_DIR)
    set (WAMR_ROOT_DIR ${CMAKE_CURRENT_LIST_DIR}/../)
endif ()
if (NOT DEFINED SHARED_DIR)
    set (SHARED_DIR ${WAMR_ROOT_DIR}/core/shared)
endif ()
if (NOT DEFINED IWASM_DIR)
    set (IWASM_DIR ${WAMR_ROOT_DIR}/core/iwasm)
endif ()
if (NOT DEFINED APP_MGR_DIR)
    set (APP_MGR_DIR ${WAMR_ROOT_DIR}/core/app-mgr)
endif ()
if (NOT DEFINED APP_FRAMEWORK_DIR)
    set (APP_FRAMEWORK_DIR ${WAMR_ROOT_DIR}/core/app-framework)
endif ()
if (NOT DEFINED DEPS_DIR)
    set (DEPS_DIR ${WAMR_ROOT_DIR}/core/deps)
endif ()

if (DEFINED EXTRA_SDK_INCLUDE_PATH)
    message(STATUS, "EXTRA_SDK_INCLUDE_PATH = ${EXTRA_SDK_INCLUDE_PATH} ")
    include_directories (
        ${EXTRA_SDK_INCLUDE_PATH}
    )
endif ()

# Set default options

# Set WAMR_BUILD_TARGET, currently values supported:
# "X86_64", "AMD_64", "X86_32", "ARM[sub]", "THUMB[sub]", "MIPS", "XTENSA"
if (NOT DEFINED WAMR_BUILD_TARGET)
    if (CMAKE_SIZEOF_VOID_P EQUAL 8)
        # Build as X86_64 by default in 64-bit platform
        set (WAMR_BUILD_TARGET "X86_64")
    else ()
        # Build as X86_32 by default in 32-bit platform
        set (WAMR_BUILD_TARGET "X86_32")
    endif ()
endif ()

################ optional according to settings ################
if (WAMR_BUILD_INTERP EQUAL 1 OR WAMR_BUILD_JIT EQUAL 1)
    include (${IWASM_DIR}/interpreter/iwasm_interp.cmake)
endif ()

if (WAMR_BUILD_AOT EQUAL 1)
    include (${IWASM_DIR}/aot/iwasm_aot.cmake)
    if (WAMR_BUILD_JIT EQUAL 1)
        include (${IWASM_DIR}/compilation/iwasm_compl.cmake)
    endif ()
endif ()

if (WAMR_BUILD_APP_FRAMEWORK EQUAL 1)
    include (${APP_FRAMEWORK_DIR}/app_framework.cmake)
    include (${SHARED_DIR}/coap/lib_coap.cmake)
    include (${APP_MGR_DIR}/app-manager/app_mgr.cmake)
    include (${APP_MGR_DIR}/app-mgr-shared/app_mgr_shared.cmake)
endif ()

if (WAMR_BUILD_LIBC_BUILTIN EQUAL 1)
    include (${IWASM_DIR}/libraries/libc-builtin/libc_builtin.cmake)
endif ()

if (WAMR_BUILD_LIBC_WASI EQUAL 1)
    include (${IWASM_DIR}/libraries/libc-wasi/libc_wasi.cmake)
endif ()

####################### Common sources #######################
set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=gnu99 -ffunction-sections -fdata-sections \
                                     -Wall -Wno-unused-parameter -Wno-pedantic")

# include the build config template file
include (${CMAKE_CURRENT_LIST_DIR}/config_common.cmake)

include_directories (${SHARED_DIR}/include
                     ${IWASM_DIR}/include)

file (GLOB header
    ${SHARED_DIR}/include/*.h
    ${IWASM_DIR}/include/*.h
)
LIST (APPEND RUNTIME_LIB_HEADER_LIST ${header})

enable_language (ASM)

include (${SHARED_DIR}/platform/${WAMR_BUILD_PLATFORM}/shared_platform.cmake)
include (${SHARED_DIR}/mem-alloc/mem_alloc.cmake)
include (${IWASM_DIR}/common/iwasm_common.cmake)
include (${SHARED_DIR}/utils/shared_utils.cmake)


set (source_all
    ${PLATFORM_SHARED_SOURCE}
    ${MEM_ALLOC_SHARED_SOURCE}
    ${UTILS_SHARED_SOURCE}
    ${LIBC_BUILTIN_SOURCE}
    ${LIBC_WASI_SOURCE}
    ${IWASM_COMMON_SOURCE}
    ${IWASM_INTERP_SOURCE}
    ${IWASM_AOT_SOURCE}
    ${IWASM_COMPL_SOURCE}
    ${WASM_APP_LIB_SOURCE_ALL}
    ${NATIVE_INTERFACE_SOURCE}
    ${APP_MGR_SOURCE}
)

set (WAMR_RUNTIME_LIB_SOURCE ${source_all})
