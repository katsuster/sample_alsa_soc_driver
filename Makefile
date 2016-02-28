
ARCH ?= x86_64
CROSS_COMPILE ?=
V ?= 0

# Tools
MKDIR   ?= mkdir
INSTALL ?= install

# Kernel path
KERNEL_DIR       ?= /usr/src/linux
INSTALL_MOD_PATH ?= /
PWD              := $(shell pwd)
MFLAGS           := ARCH=$(ARCH) CROSS_COMPILE=$(CROSS_COMPILE) -C $(KERNEL_DIR) M=$(CURDIR) LDDINC=$(PWD)

modules:
	$(MAKE) $(MFLAGS) modules

install:
	$(MAKE) $(MFLAGS) INSTALL_MOD_PATH=$(INSTALL_MOD_PATH) modules_install

clean:
	$(MAKE) $(MFLAGS) clean

.PHONY: all modules install clean
