# --------------- 工具链 -----------------
CROSS    := riscv64-elf-
CC       := $(CROSS)gcc
CXX      := $(CROSS)g++
LD       := $(CROSS)ld
OBJCOPY  := $(CROSS)objcopy
OBJDUMP  := $(CROSS)objdump

# --------------- 路径 -------------------
APPS_DIR := apps
LIBS_DIR := libs
OUT_DIR  := out
LINKER   := linker_user.ld

# --------------- 编译参数 --------------- 
ARCH_FLAGS := -march=rv64gc -mabi=lp64d -mcmodel=medany
COMMON_FLAGS := -nostdlib -ffreestanding $(ARCH_FLAGS)
INC_LIBS     := -I$(LIBS_DIR)

# --------------- 源文件 -----------------
APP_SRCS := $(wildcard $(APPS_DIR)/*.cpp)
APP_ELF  := $(patsubst $(APPS_DIR)/%.cpp,$(OUT_DIR)/%.elf,$(APP_SRCS))
RUNTIME  := $(LIBS_DIR)/libs.cpp
BIN := $(patsubst $(OUT_DIR)/%.elf,$(OUT_DIR)/%.bin,$(APP_ELF))

# --------------- 默认目标 ---------------
all: $(APP_ELF) $(BIN)

# --------------- 模式规则 ---------------
# 编译 app 源文件
$(OUT_DIR)/%.o: $(APPS_DIR)/%.cpp | $(OUT_DIR)
	$(CXX) $(COMMON_FLAGS) $(INC_LIBS) -c $< -o $@

# 编译运行时库
$(LIBS_DIR)/libs.o: $(RUNTIME)
	$(CXX) $(COMMON_FLAGS) $(INC_LIBS) -c $< -o $@

# 链接生成 ELF
$(OUT_DIR)/%.elf: $(OUT_DIR)/%.o $(LIBS_DIR)/libs.o
	$(LD) $^ -T $(LINKER) -o $@

$(OUT_DIR)/%.bin: $(OUT_DIR)/%.elf
	$(OBJCOPY) -O binary $< $@

# --------------- 辅助目标 ---------------
$(OUT_DIR):
	mkdir -p $@

clean:
	rm -rf $(OUT_DIR) $(LIBS_DIR)/*.o

.PHONY: all clean
