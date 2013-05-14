#! /bin/sh
#
# Creates and links the inc directory.

if test -e inc; then :; else
	mkdir inc;
fi

if test -e ./inc/avr32; then :; else
	cd inc && ln -s ../arch/avr32/include avr32 && cd ..;
fi

if test -e ./inc/machine; then :; else
	cd inc && ln -s ../arch/avr32/include machine && cd ..;
fi
