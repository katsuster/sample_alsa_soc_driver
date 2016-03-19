
CONFIG_SND_SAMPLE_CORE = m
CONFIG_SND_SAMPLE_I2S = m
CONFIG_SND_SAMPLE_I2S_SPDIF = m
CONFIG_SND_SAMPLE_DEVICE = m
# For debug
CONFIG_SND_SAMPLE_DEBUG = y

ifeq ($(CONFIG_SND_SAMPLE_DEBUG),y)
  DBGFLAGS = -O1 -g -DCONFIG_SND_SAMPLE_DEBUG
endif

EXTRA_CFLAGS += $(DBGFLAGS)
EXTRA_CFLAGS += -I$(LDDINC)


# Sample ALSA SoC driver
snd-sample-core-objs := sample-core.o sample-util.o
obj-$(CONFIG_SND_SAMPLE_CORE) += snd-sample-core.o

snd-sample-i2s-objs := sample-i2s.o
obj-$(CONFIG_SND_SAMPLE_I2S) += snd-sample-i2s.o

snd-sample-i2s-spdif-objs := sample-i2s-spdif.o
obj-$(CONFIG_SND_SAMPLE_I2S_SPDIF) += snd-sample-i2s-spdif.o


# Sample ALSA SoC device
snd-sample-device-objs := sample-device.o
obj-$(CONFIG_SND_SAMPLE_DEVICE) += snd-sample-device.o
