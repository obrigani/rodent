#!/usr/bin/env fish

export HOST='i686-elf'

export QEMUFLAGS='-vga virtio'

export CC=$HOST-gcc
export CFLAGS='-O2 -g'

export AS=$HOST-as
export AR=$HOST-ar

export PREFIX=/usr
export EXEC_PREFIX=$PREFIX
export BOOTDIR=/boot
export LIBDIR=$EXEC_PREFIX/lib
export INCLUDEDIR=$PREFIX/include

export SYSROOT="$(pwd)/sysroot"
export CC="$CC --sysroot=$SYSROOT"

if echo "$HOST" | grep -Eq -- '-elf($|-)'
    export CC="$CC -isystem=$INCLUDEDIR"
end

echo 'Config applied'
