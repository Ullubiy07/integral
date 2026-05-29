CFLAGS ?= -g

CFLAGS += -std=gnu99

CFLAGS += -Wall -Werror -Wformat-security -Wignored-qualifiers -Winit-self \
	-Wswitch-default -Wpointer-arith -Wtype-limits -Wempty-body \
	-Wstrict-prototypes -Wold-style-declaration -Wold-style-definition \
	-Wmissing-parameter-type -Wmissing-field-initializers -Wnested-externs \
	-Wstack-usage=4096 -Wmissing-prototypes -Wfloat-equal -Wabsolute-value

CFLAGS += -fsanitize=undefined -fsanitize-undefined-trap-on-error

CC += -m32 -no-pie -fno-pie

LDLIBS = -lm
LDFLAGS = -fsanitize=undefined

AS = nasm
ASFLAGS = -f elf32

BUILD_DIR = build/

SOURCES = src/main.c src/calculus/root.c src/calculus/integral.c src/functions.asm \
	      src/cli/parser.c src/cli/handler.c src/cli/actions.c
OBJECTS = $(addprefix $(BUILD_DIR), $(addsuffix .o, $(basename $(SOURCES))))

TARGET = integral

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJECTS)
	@echo "[LD] Linking C executable $@"
	@$(CC) $(LDFLAGS) -o $@ $^ $(LDLIBS)
	@echo "[OK] Built target integral"

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
