CC = clang
LD = ld
CFLAGS = -target x86_64-unknown-freebsd12 -ffreestanding -nostdlib -fPIC -O2 -mno-red-zone

loader.bin: loader.elf
	objcopy -O binary $< $@

loader.elf: loader.o
	$(LD) -Ttext 0x0 -e _start -o $@ $<

loader.o: loader.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f loader.o loader.elf loader.bin