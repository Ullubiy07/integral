CFLAGS ?= -g

CFLAGS += -std=gnu99
CFLAGS += -I src

CFLAGS += -Wall -Werror -Wformat-security -Wignored-qualifiers -Winit-self \
	-Wswitch-default -Wpointer-arith -Wtype-limits -Wempty-body \
	-Wstrict-prototypes -Wold-style-declaration -Wold-style-definition \
	-Wmissing-parameter-type -Wmissing-field-initializers -Wnested-externs \
	-Wstack-usage=4096 -Wmissing-prototypes -Wfloat-equal -Wabsolute-value

CFLAGS += -fsanitize=undefined -fsanitize-undefined-trap-on-error

CC += -m32 -no-pie -fno-pie

LDLIBS = -lm
LDFLAGS = -fsanitize=undefined -Wl,-z,noexecstack

AS = nasm
ASFLAGS = -f elf32

BUILD_DIR = build/

SOURCES = src/main.c src/calculus/root.c src/calculus/integral.c src/functions.asm \
	      src/cli/parser.c src/cli/handler.c src/cli/options.c
OBJECTS = $(addprefix $(BUILD_DIR), $(addsuffix .o, $(basename $(SOURCES))))

TEST_SOURCES = src/calculus/root.c src/calculus/integral.c \
	           test/main.c test/root_test.c test/integral_test.c test/functions.c
TEST_OBJECTS = $(addprefix $(BUILD_DIR), $(addsuffix .o, $(basename $(TEST_SOURCES))))

TEST_TARGET = test_integral
TARGET = integral

.PHONY: all clean test

all: $(TARGET)
test: $(TEST_TARGET)
	@./$(TEST_TARGET)

$(TARGET): $(OBJECTS)
	@echo "[LD] Linking C executable $@"
	@$(CC) $(LDFLAGS) -o $@ $^ $(LDLIBS)
	@echo "[OK] Built target $@"

$(TEST_TARGET): $(TEST_OBJECTS)
	@echo "[LD] Linking C executable $@"
	@$(CC) $(LDFLAGS) -o $@ $^ $(LDLIBS)
	@echo "[OK] Built target $@"

$(BUILD_DIR)%.o: %.c | $(BUILD_DIR)
	@echo "[CC] Building C object $@"
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c -o $@ $<

$(BUILD_DIR)%.o: %.asm | $(BUILD_DIR)
	@echo "[AS] Building ASM object $@"
	@mkdir -p $(dir $@)
	@$(AS) $(ASFLAGS) -o $@ $<

$(BUILD_DIR):
	@mkdir -p $@

clean:
	@echo "Cleaning up object files"
	@rm -rf $(BUILD_DIR)*
