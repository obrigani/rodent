.SUFFIXES:

QEMUFLAGS := $(QEMUFLAGS)

override IMAGE_NAME := rodent

HOST_CC := cc
HOST_CFLAGS := -g -O2 -pipe

.PHONY: all
all: $(IMAGE_NAME)-limine.iso

.PHONY: run
run: $(IMAGE_NAME)-limine.iso
	qemu-system-i386 \
	-cdrom $(IMAGE_NAME)-limine.iso \
	$(QEMUFLAGS)

.PHONY: all $(IMAGE_NAME).iso
	@echo System image with the Limine bootloader built successfully

sysroot/usr/lib/libk.a:
	make DESTDIR="$(SYSROOT)" -C kernel install-headers
	make DESTDIR="$(SYSROOT)" -C libk install

sysroot/boot/kernel.elf: sysroot/usr/lib/libk.a
	make DESTDIR="$(SYSROOT)" -C kernel install

limine-binary/.downloaded:
	curl -L https://github.com/Limine-Bootloader/Limine/releases/latest/download/limine-binary.tar.gz | gunzip | tar -xf -
	touch $@

limine-binary/.built: limine-binary/.downloaded
	make -C limine-binary
	touch $@

$(IMAGE_NAME)-limine.iso: sysroot/boot/kernel.elf limine-binary/.built
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
	        isodir -o $(IMAGE_NAME)-limine.iso

	./limine-binary/limine bios-install $(IMAGE_NAME)-limine.iso

	rm -fr isodir

.PHONY: clean
clean:
	make -C kernel clean
	make -C libk clean
	rm -fr sysroot isodir
	rm -fr *.iso

.PHONY: distclean
distclean:
	rm -fr limine-binary
