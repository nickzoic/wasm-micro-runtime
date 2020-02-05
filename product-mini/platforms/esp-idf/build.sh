#!/bin/bash
# from ESP-IDF 4.0 examples/build_system/cmake/idf_as_lib
rm -rf build && mkdir build && cd build
cp ../sdkconfig .
cmake .. -DCMAKE_TOOLCHAIN_FILE=$IDF_PATH/tools/cmake/toolchain-esp32.cmake
cmake --build .
