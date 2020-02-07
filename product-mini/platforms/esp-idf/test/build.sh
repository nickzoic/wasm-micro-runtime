#!/bin/bash
clang-8 --target=wasm32 -O3 -z stack-size=4096 -nostdlib test.c -Wl,--allow-undefined -Wl,--export=main, -Wl,--no-threads,--strip-all,--no-entry -o test.wasm
(
    echo // GENERATED FROM $PWD/test.c
    echo // `date -Iseconds`
    echo 
    echo unsigned char wasm_test_file[] = {
    cat test.wasm | xxd -i
    echo }\;
) > ../test_wasm.h
