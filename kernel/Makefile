HOSTARCH != ../scripts/tt-to-arch $(HOST)

CFLAGS? = -O2 -g
CPPFLAGS? = 
LDFLAGS? =
LIBS? =

DESTDIR? =
PREFIX? = /usr/local
EXEC_PREFIX? = $(PREFIX)
BOOTDIR? = $(EXEC_PREFIX)/boot
INCLUDEDIR? = $(PREFIX)/include

CFLAGS := $(CFLAGS) -ffreestanding -Wall -Wextra
CPPFLAGS := $(CPPFLAGS) -D__is_kernel -Iinclude 
LDFLAGS := $(LDFLAGS)
LIBS := $(LIBS) -nostdlib -lk -lgcc

ARCHDIR = arch/$(HOSTARCH)

include $(ARCHDIR)/make.config

CFLAGS := $(CFLAGS) $(KERNEL_ARCH_CFLAGS)
CPPFLAGS := $(CPPFLAGS) $(KERNEL_ARCH_CPPFLAGS)
LDFLAGS := $(LDFLAGS) $(KERNEL_ARCH_LDFLAGS)
LIBS := $(LIBS) $(KERNEL_ARCH_LIBS)

KERNEL_OBJS = $(KERNEL_ARCH_OBJS) \
			  kernel/main.o \

OBJS = $(ARCHDIR)/crti.o \
	   $(ARCHDIR)/crtbegin.o \
	   $(KERNEL_OBJS) \
	   $(ARCHDIR)/crtend.o \
	   $(ARCHDIR)/crtn.o \

LINK_LIST = $(LDFLAGS) \
			$(ARCHDIR)/crti.o \
			$(ARCHDIR)/crtbegin.o \
			$(KERNEL_OBJS) \
			$(LIBS) \
			$(ARCHDIR)/crtend.o \
			$(ARCHDIR)/crtn.o \

.SUFFIXES: .o .c .S

.PHONY: all
all: kernel.elf
kernel.elf: $(OBJS) $(ARCHDIR)/linker.ld
	$(CC) -T $(ARCHDIR)/linker.ld -o $@ $(CFLAGS) $(LINK_LIST)
	grub-file --is-x86-multiboot kernel.elf

$(ARCHDIR)/crtbegin.o $(ARCHDIR)/crtend.o:
	OBJ=`$(CC) $(CFLAGS) $(LDFLAGS) -print-file-name=$(@F)` && cp "$$OBJ" $@

.c.o:
	$(CC) -MD -c $< -o $@ $(CSTANDARD) $(CFLAGS) $(CPPFLAGS)

.S.o:
	$(CC) -MD -c $< -o $@ $(CFLAGS) $(CPPFLAGS)

.PHONY: clean
clean:
	rm -f kernel.elf
	rm -f $(OBJS) *.o */*.o */*/*.o
	rm -f $(OBJS:.o=.d) *.d */*.d */*/*.d

.PHONY: install
install: install-headers install-kernel

.PHONY: install-headers
install-headers:
	mkdir -p $(DESTDIR)$(INCLUDEDIR)
	cp -R --preserve=timestamps include/. $(DESTDIR)$(INCLUDEDIR)/.

.PHONY: install-kernel
install-kernel: kernel.elf
	mkdir -p $(DESTDIR)$(BOOTDIR)
	cp kernel.elf $(DESTDIR)$(BOOTDIR)

-include $(OBJS:.o=.d)
