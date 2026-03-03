#!/usr/bin/env bash

root_path=${root_path:-$(dirname $(realpath $0))}

gcc_arm_none_eabi_bin=/c/Users/link/AppData/Local/mind+/Arduino/packages/mindplus/tools/gcc-arm-none-eabi/0.0.1/bin
export PATH=$gcc_arm_none_eabi_bin:$PATH

function gen() {
    local target=$1

    mkdir -p $root_path/build

    echo

    arm-none-eabi-g++ $(< ./parameters/build_args.txt) ./src/${target}.c -o ./build/${target}.o \
    && echo "${root_path}/gen.sh: 成功生成 -> $target.o"

    arm-none-eabi-g++ ./build/${target}.o $(< ./parameters/link_args.txt) -Wl,-Map,./build/${target}.map -o ./build/${target}.elf \
    && echo "${root_path}/gen.sh: 成功生成 -> $target.elf"

    arm-none-eabi-objcopy -O ihex ./build/${target}.elf ./build/${target}.hex \
    && echo "${root_path}/gen.sh: 成功生成 -> $target.hex"

    echo
}

gen template
# gen pathfinding
