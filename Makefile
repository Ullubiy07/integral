CFLAGS ?= -O2 -g

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

INTEGRAL_OBJ = $(BUILD_DIR)integral.o
FUNCTIONS_OBJ = $(BUILD_DIR)functions.o

INTEGRAL = integral
TARGETS = $(INTEGRAL)

.PHONY: all clean

all: $(TARGETS)

$(INTEGRAL): $(INTEGRAL_OBJ) $(FUNCTIONS_OBJ)
	@echo "[LD] Linking C executable $@"
	@$(CC) $(LDFLAGS) -o $@ $^ $(LDLIBS)
	@echo "[OK] Built target integral"

$(INTEGRAL_OBJ): src/integral.c | $(BUILD_DIR)
	@echo "[CC] Building C object $@"
	@$(CC) $(CFLAGS) -c -o $@ $<

$(FUNCTIONS_OBJ): src/functions.asm | $(BUILD_DIR)
	@echo "[AS] Building ASM object $@"
	@$(AS) $(ASFLAGS) -o $@ $<

$(BUILD_DIR):
	@mkdir -p $@

clean:
	@echo "Cleaning up object files"
	@rm -rf $(BUILD_DIR)*
