# 目录变量
TOP_DIR:= $(patsubst %/,%,$(dir $(abspath $(firstword $(MAKEFILE_LIST)))))
CUR_DIR:= $(CURDIR)

# 源文件和目标文件
SRC_DIR:= $(TOP_DIR)/src
BUILD_DIR:= $(TOP_DIR)/build

# 交叉编译工具链
CROSS_COMPILE = riscv64-elf-
CC = $(CROSS_COMPILE)gcc
CXX = $(CROSS_COMPILE)g++
LD = $(CROSS_COMPILE)ld
OBJCOPY = $(CROSS_COMPILE)objcopy
GDB = $(CROSS_COMPILE)gdb

# 编译选项
INCLUDE_DIR = -I$(SRC_DIR) -I$(SRC_DIR)/sbi -I$(SRC_DIR)/util -I$(SRC_DIR)/syscall
CFLAGS = -nostdlib -march=rv64gc -mabi=lp64d -mcmodel=medany
CXXFLAGS = $(CFLAGS) -ffreestanding $(INCLUDE_DIR)
LINK_SCRIPT = $(SRC_DIR)/linker.ld
LDFLAGS = -T $(LINK_SCRIPT) -nostdlib

# 源文件和目标文件
SRC:= $(shell find $(SRC_DIR) -name "*.s")
SRC+= $(shell find $(SRC_DIR) -name "*.S")
SRC+= $(shell find $(SRC_DIR) -name "*.cpp")

OBJS:= $(patsubst $(SRC_DIR)/%.cpp, $(BUILD_DIR)/%.o, $(SRC))
OBJS:= $(patsubst $(SRC_DIR)/%.s, $(BUILD_DIR)/%.o, $(OBJS))
OBJS:= $(patsubst $(SRC_DIR)/%.S, $(BUILD_DIR)/%.o, $(OBJS))

# QEMU
QEMU:= qemu-system-riscv64
BOOTLOADER:= $(TOP_DIR)/bootloader/rustsbi-qemu.bin
QEMU_FLAGS:= -machine virt -nographic -bios $(BOOTLOADER)

NAME:= ntrCore

################################
all: user_bin $(NAME).bin

user_bin:
	$(MAKE) -C user
	./scripts/link_app_gen.sh

$(NAME).bin: $(NAME).elf
	$(OBJCOPY) -O binary $< $@

$(NAME).elf: $(OBJS)
	@mkdir -p $(dir $@)
	$(LD) $^ -o $@ $(LDFLAGS)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.s
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.S
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

run: user_bin $(NAME).bin
	$(QEMU) $(QEMU_FLAGS) -device loader,file=$(NAME).bin,addr=0x80200000

debug: user_bin $(NAME).bin
	$(QEMU) $(QEMU_FLAGS) -device loader,file=$<,addr=0x80200000 -s -S

gdb:
	$(GDB) -ex 'file $(NAME).elf' \
		-ex 'set arch riscv:rv64' \
		-ex 'target remote localhost:1234' \
		-ex 'tui enable'

clean:
	$(MAKE) -C user clean
	rm -rf $(BUILD_DIR) $(NAME).elf $(NAME).bin user_bin

.PHONY: clean run all debug gdb
