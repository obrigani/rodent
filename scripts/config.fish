#!/usr/bin/env fish

# BTW, this script exists only for the Makefiles to function when I use my shell,
# there is no plan to remake other scripts in fish

set -gx HOST i686-elf
# Should be either 'limine' or 'grub' (CASE SENSITIVE!!)
set -gx BOOTLOADER limine
# set -gx BOOTLOADER 'grub'

set -gx CPUCORES (grep -c '^processor' /proc/cpuinfo)

set -gx QEMUFLAGS '-vga virtio'
set -gx QEMUFLAGS_SERIAL -nographic
set -gx MAKEFLAGS "-j$CPUCORES -l$(math $CPUCORES + 1)"

set -gx CC $HOST-gcc
set -gx CSTANDARD '-std=gnu23'
set -gx CFLAGS '-O2 -g -pedantic -Werror'
set -gx CPPFLAGS

set -gx AS $HOST-as
set -gx AR $HOST-ar

set -gx PREFIX /usr
set -gx EXEC_PREFIX $PREFIX
set -gx BOOTDIR /boot
set -gx LIBDIR $EXEC_PREFIX/lib
set -gx INCLUDEDIR $PREFIX/include

set -gx SYSROOT "$(pwd)/sysroot"
set -gx CC "$CC --sysroot=$SYSROOT"

if echo "$HOST" | grep -Eq -- '-elf($|-)'
    set -gx CC "$CC -isystem=$INCLUDEDIR"
end

echo 'Config applied'
echo $MAKEFLAGS
