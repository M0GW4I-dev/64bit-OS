ISO := os.iso
OUTPUT := kernel.sys

OBJS := boot.o main.o

all: $(ISO)

$(ISO): $(OUTPUT)
	mkdir -p iso/boot/grub
	cp grub.cfg iso/boot/grub
	cp $(OUTPUT) iso/boot
	i386-elf-grub-mkrescue -o $@ iso

$(OUTPUT): $(OBJS) linker.ld
	x86_64-elf-ld -nodefaultlibs -Tlinker.ld -o $@ $(OBJS)

.s.o:
	nasm -felf64 $< -o $@

.c.o:
	x86_64-elf-gcc -m64 -mcmodel=kernel -ffreestanding -nostdlib -mno-red-zone -c $< -o $@

clean:
	@rm -f $(OBJS) $(OUTPUT)


