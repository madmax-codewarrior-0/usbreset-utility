# usbreset Utility
CC=gcc

usbreset: usbreset.c
        $(CC) -o usbreset usbreset.c
        @echo "Run 'make install' to install to sbin"

.PHONY: install
install: 
        @mv ./usbreset /usr/local/sbin
        @chmod 550 /usr/local/sbin/usbreset
        @ls -lh /usr/local/sbin/usbreset

.PHONY: uninstall
uninstall:
        rm -f /usr/local/sbin/usbreset

.PHONY: default
default: usbreset

.PHONY: clean
clean:
        rm -f usbreset
