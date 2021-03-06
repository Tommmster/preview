#! /bin/bash

for sub in ./uvm ./compat/sa ./compat/linux/common ./compat/linux/arch/avr32 \
	   ./compat/common ./kern ./miscfs/specfs \
           ./ufs/ext2fs ./ufs/ufs ./ufs/ffs ./miscfs/genfs ./miscfs/deadfs \
           ./miscfs/syncfs ./miscfs/fifofs ./net ./conf ./arch/avr32/avr32 \
           ./arch/avr32/boot ./arch/avr32/conf ./dev ./dev/dkwedge \
           ./lib/libkern ../common/lib/libc/stdlib \
           ../common/lib/libc/string ../common/lib/libc/quad \
           ../common/lib/libc/gen ../common/lib/libc/atomic \
           ../common/lib/libc/sys ../common/lib/libc/net \
           ../common/lib/libprop ../common/lib/libc/arch/avr32/atomic; do
	make -C $sub "$@" || break
done
