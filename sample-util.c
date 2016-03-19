
#define pr_fmt(fmt) SND_SAMPLE_DRV_NAME ": " fmt

#include <linux/module.h>

#include "sample-util.h"

int snd_sample_util_func(void)
{
	pr_info("util_func.\n");

	return 0;
}
EXPORT_SYMBOL(snd_sample_util_func);

MODULE_AUTHOR("Katsuhiro Suzuki <katsuhiro@katsuster.net>");
MODULE_DESCRIPTION("Sample ALSA SoC driver");
MODULE_LICENSE("GPL");
