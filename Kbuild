
CONFIG_SND_SAMPLE_DRIVER = m
CONFIG_SND_SAMPLE_DEVICE = m
# For debug
CONFIG_SND_SAMPLE_DEBUG = y

ifeq ($(CONFIG_SND_SAMPLE_DEBUG),y)
  DBGFLAGS = -O1 -g -DCONFIG_SND_SAMPLE_DEBUG
endif

EXTRA_CFLAGS += $(DBGFLAGS)
EXTRA_CFLAGS += -I$(LDDINC)


# Sample platform bus driver
snd-sample-drv-objs := snd-sample-driver.o snd-sample-utils.o
obj-$(CONFIG_SND_SAMPLE_DRIVER) += snd-sample-drv.o

# Sample platform bus device
snd-sample-dev1-objs := snd-sample-device.o snd-sample-utils.o
obj-$(CONFIG_SND_SAMPLE_DEVICE) += snd-sample-dev1.o
