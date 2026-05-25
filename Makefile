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
to_build_dir = $(addprefix $(BUILD_DIR), $(notdir $(1)))

SOURCES = src/main.c src/calculus/integral.c src/calculus/root.c src/functions.asm
OBJECTS = $(addsuffix .o, $(basename $(SOURCES)))

TARGET = integral

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJECTS)
	@echo "[LD] Linking C executable $@"
	@$(CC) $(LDFLAGS) -o $@ $(call to_build_dir, $^) $(LDLIBS)
	@echo "[OK] Built target integral"

%.o: %.c | $(BUILD_DIR)
	@echo "[CC] Building C object $@"
	@$(CC) $(CFLAGS) -c -o $(call to_build_dir, $@) $<

%.o: %.asm | $(BUILD_DIR)
	@echo "[AS] Building ASM object $@"
	@$(AS) $(ASFLAGS) -o $(call to_build_dir, $@) $<

$(BUILD_DIR):
	@mkdir -p $@

clean:
	@echo "Cleaning up object files"
	@rm -rf $(BUILD_DIR)*
