.SUFFIXES:

QEMUFLAGS := $(QEMUFLAGS)

override IMAGE_NAME := rodent

HOST_CC := cc
HOST_CFLAGS := -g -O2 -pipe

.PHONY: all
all: $(IMAGE_NAME)-i386-$(BOOTLOADER).iso
	@echo System image with the $(BOOTLOADER) bootloader built successfully

.PHONY: run
run: $(IMAGE_NAME)-i386-$(BOOTLOADER).iso
	qemu-system-i386 \
	-cdrom $(IMAGE_NAME)-i386-$(BOOTLOADER).iso \
	$(QEMUFLAGS)

.PHONY: install-headers
install-headers:
	make DESTDIR="$(SYSROOT)" -C kernel install-headers $(MAKEFLAGS)
	make DESTDIR="$(SYSROOT)" -C libk install-headers $(MAKEFLAGS)

sysroot/usr/lib/libk.a:
	make DESTDIR="$(SYSROOT)" -C kernel install-headers $(MAKEFLAGS)
	make DESTDIR="$(SYSROOT)" -C libk install $(MAKEFLAGS)

sysroot/boot/kernel.elf: sysroot/usr/lib/libk.a
	make DESTDIR="$(SYSROOT)" -C kernel install $(MAKEFLAGS)

limine-binary/.downloaded:
	curl -L https://github.com/Limine-Bootloader/Limine/releases/latest/download/limine-binary.tar.gz | gunzip | tar -xf -
	touch $@

limine-binary/.built: limine-binary/.downloaded
	make -C limine-binary $(MAKEFLAGS)
	touch $@

$(IMAGE_NAME)-i386-limine.iso: sysroot/boot/kernel.elf limine-binary/.built
	mkdir -p isodir

	mkdir -p isodir/boot
	cp -v sysroot/boot/kernel.elf isodir/boot
	mkdir -p isodir/boot/limine
	cp -v limine.conf limine-binary/limine-bios.sys limine-binary/limine-bios-cd.bin limine-binary/limine-uefi-cd.bin isodir/boot/limine/

	mkdir -p isodir/EFI/BOOT
	cp -v limine-binary/BOOTX64.EFI isodir/EFI/BOOT/
	cp -v limine-binary/BOOTIA32.EFI isodir/EFI/BOOT/

	xorriso -as mkisofs -R -r -J -b boot/limine/limine-bios-cd.bin \
	        -no-emul-boot -boot-load-size 4 -boot-info-table -hfsplus \
	        -apm-block-size 2048 --efi-boot boot/limine/limine-uefi-cd.bin \
	        -efi-boot-part --efi-boot-image --protective-msdos-label \
	        isodir -o $(IMAGE_NAME)-i386-limine.iso

	./limine-binary/limine bios-install $(IMAGE_NAME)-i386-limine.iso

	rm -fr isodir

$(IMAGE_NAME)-i386-grub.iso: sysroot/boot/kernel.elf
	mkdir -p isodir/boot/grub
	cp -v sysroot/boot/kernel.elf isodir/boot/kernel.elf
	cp -v grub.cfg isodir/boot/grub/grub.cfg
	grub-mkrescue -o $(IMAGE_NAME)-i386-grub.iso isodir

	rm -fr isodir
	
.PHONY: clean
clean:
	make -C kernel clean
	make -C libk clean
	rm -fr sysroot isodir
	rm -fr *.log

.PHONY: distclean
distclean:
	rm -fr limine-binary
