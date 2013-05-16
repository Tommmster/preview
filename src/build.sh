#! /bin/bash

for sub in ./sys/uvm ./sys/compat/sa ./sys/compat/ossaudio ./sys/compat/common  \
	   ./sys/compat/linux/common ./sys/compat/linux/arch/avr32 ./sys/kern \
           ./sys/miscfs/specfs ./sys/ufs/ext2fs ./sys/ufs/ufs ./sys/ufs/ffs \
           ./sys/miscfs/genfs ./sys/miscfs/deadfs ./sys/miscfs/syncfs \
           ./sys/miscfs/fifofs ./sys/net ./sys/conf ./sys/arch/avr32/avr32 \
           ./sys/arch/avr32/conf ./sys/dev ./sys/dev/dkwedge \
           ./sys/lib/libkern ./common/lib/libc/stdlib \
           ./common/lib/libc/string ./common/lib/libc/quad \
           ./common/lib/libc/gen ./common/lib/libc/atomic \
           ./common/lib/libc/sys ./common/lib/libc/net ./common/lib/libprop \
           ./common/lib/libc/arch/avr32/atomic; do
	make -C $sub "$@" || break
done
