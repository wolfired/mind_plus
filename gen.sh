#!/usr/bin/env bash

root_path=${root_path:-$(dirname $(realpath $0))}

function path_style_win2linux() {
    local path=${1:-''}
    echo $path | sed 's#\\#/#g' | sed -E 's#^([a-zA-Z]):#/\L\1#g'
}

MIND_PLUS_HOME=${MIND_PLUS_HOME:?"请设置环境变量: MIND_PLUS_HOME=C:\Users\用户名\AppData\Local\mind+"}
MIND_PLUS_HOME=`path_style_win2linux $MIND_PLUS_HOME`

if [[ ! -d $MIND_PLUS_HOME/Arduino/packages/mindplus/tools/gcc-arm-none-eabi/0.0.1/bin ]]; then
    echo "目录不存在: $MIND_PLUS_HOME"
    exit 1
fi
export PATH=$MIND_PLUS_HOME/Arduino/packages/mindplus/tools/gcc-arm-none-eabi/0.0.1/bin:$PATH

function gen() {
    local target=$1

    mkdir -p $root_path/build

    arm-none-eabi-g++ $(< ./parameters/build_args.txt) ./src/${target}.c -o ./build/${target}.o \
    && echo "成功生成: $target.o"

    arm-none-eabi-g++ ./build/${target}.o $(< ./parameters/link_args.txt) -Wl,-Map,./build/${target}.map -o ./build/${target}.elf \
    && echo "成功生成: $target.elf"

    arm-none-eabi-objcopy -O ihex ./build/${target}.elf ./build/${target}.hex \
    && echo "成功生成: $target.hex"

    echo
}

gen main
