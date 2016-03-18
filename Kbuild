
CONFIG_SND_SAMPLE_I2S = m
CONFIG_SND_SAMPLE_DRIVER = m
CONFIG_SND_SAMPLE_DEVICE = m
# For debug
CONFIG_SND_SAMPLE_DEBUG = y

ifeq ($(CONFIG_SND_SAMPLE_DEBUG),y)
  DBGFLAGS = -O1 -g -DCONFIG_SND_SAMPLE_DEBUG
endif

EXTRA_CFLAGS += $(DBGFLAGS)
EXTRA_CFLAGS += -I$(LDDINC)


# Sample ALSA SoC driver
snd-sample-driver-objs := sample-driver.o sample-utils.o
obj-$(CONFIG_SND_SAMPLE_DRIVER) += snd-sample-driver.o

# Sample ALSA SoC device
snd-sample-device-objs := sample-device.o sample-utils.o
obj-$(CONFIG_SND_SAMPLE_DEVICE) += snd-sample-device.o
