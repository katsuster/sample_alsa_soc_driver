
#define pr_fmt(fmt) SND_SAMPLE_DRV_NAME ": " fmt

#include <linux/module.h>
#include <linux/platform_device.h>

#include "sample-core.h"

MODULE_AUTHOR("Katsuhiro Suzuki <katsuhiro@katsuster.net>");
MODULE_DESCRIPTION("Sample ALSA SoC driver");
MODULE_LICENSE("GPL");
