CROSS_COMPILE?=arm-none-eabi-
CC:=$(CROSS_COMPILE)gcc
LD:=$(CROSS_COMPILE)gcc
OBJDUMP:=$(CROSS_COMPILE)objdump

OUTPUT:=uhk

TARGETS:=$(OUTPUT).elf $(OUTPUT).lst $(OUTPUT).map

all: $(TARGETS)

OPTIMIZATION:=-Og
INCLUDES:=-I.
CFLAGS:=-Wall -march=armv6-m -mthumb $(OPTIMIZATION) $(INCLUDES)
LDFLAGS:=-nostartfiles -T mkl25z4.ld -Wl,-Map=$(OUTPUT).map

SOURCES:= \
		_startup.c \
		clock.c \
		interrupts.c \
		main.c \
		tpm.c \

OBJECTS:=$(SOURCES:%.c=%.o)

%.elf %.map: $(OBJECTS)
	$(LD) $(LDFLAGS) -o $@ $^

%.lst: %.elf
	$(OBJDUMP) -S $< > $@

clean:
	rm -f $(TARGETS) $(OBJECTS)

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

.PHONY: all clean
