# mind_plus
Mind+项目模板

## 注意

1. 为了能让 `clangd` 能正常工作，把 `./src/main.c` 中的代码（ __包括头文件的全部代码__ ）复制到 `Mind+项目` 中（上传模式，手动编辑）并 __编译一次__

2. 请检查以下文本中配置的程序、文件、目录是否存在
```bash
# clangd程序
# g++程序
.zed/settings.json

# git程序
.zed/tasks.json

# .h文件
# .o文件
# .a文件: core.a在不同机器上有不同的输出, 可以在Mind+输出窗口的日志中找到
# 头文件搜索目录
# 库文件搜索目录
parameters/build_args
parameters/link_args

# g++程序
# 头文件搜索目录
.clangd

# gcc工具链目录: gcc_arm_none_eabi_bin
gen.sh
```
