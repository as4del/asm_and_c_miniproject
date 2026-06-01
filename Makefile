CFLAGS := -m32 -I.
ASMFLAGS := -f elf32


BUILD_DIR := build_dir
TEST_DIR := test_dir
TEST_BIN := test_bin
TEST_HELP_DIR := test_h


C_FILES := $(wildcard *.c)
ASM_FILES := $(wildcard *.nasm)
TEST_FILES := $(wildcard tests/*.c)



TARGET_O := $(patsubst %.c, $(BUILD_DIR)/%.o, $(C_FILES)) \
$(patsubst %.nasm, $(BUILD_DIR)/%.o, $(ASM_FILES))

HELP_TEST := $(filter-out main.c, $(C_FILES))
TEST_B := $(patsubst tests/%.c, $(TEST_BIN)/%, $(TEST_FILES))
TEST_O := $(patsubst %.c, $(TEST_DIR)/%.o, $(HELP_TEST))
TEST_2O := $(patsubst tests/%.c, $(TEST_HELP_DIR)/%.o, $(TEST_FILES))


all: target

target: $(TARGET_O)
	gcc $(CFLAGS) $^ -o $@ -lm


$(BUILD_DIR)/%.o: %.c
	@mkdir -p $(BUILD_DIR)
	gcc $(CFLAGS) -c $^ -o $@


$(BUILD_DIR)/%.o: %.nasm
	@mkdir -p $(BUILD_DIR)
	nasm $(ASMFLAGS) $^ -o $@



test: $(TEST_B) 
	for test in $(TEST_B); do ./$$test; done


$(TEST_B): $(TEST_BIN)/%: $(TEST_HELP_DIR)/%.o $(TEST_O)
	@mkdir -p $(TEST_BIN)
	gcc $(CFLAGS) $^ -o $@ 

$(TEST_DIR)/%.o: %.c
	@mkdir -p $(TEST_DIR)
	gcc $(CFLAGS) -c $< -o $@ 

$(TEST_HELP_DIR)/%.o: tests/%.c
	@mkdir -p $(TEST_HELP_DIR)
	gcc $(CFLAGS) -c $< -o $@


clean:
	rm -rf $(BUILD_DIR) $(TEST_DIR) $(TEST_BIN) $(TEST_HELP_DIR) target



