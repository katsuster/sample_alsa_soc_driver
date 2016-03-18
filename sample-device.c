
#define pr_fmt(fmt) SND_SAMPLE_DRV_NAME ": " fmt

#include <linux/module.h>
#include <linux/platform_device.h>

#include "sample-device.h"

static struct platform_device *pdev = NULL;

static int __init snd_sample_device_init(void)
{
	int ret;

	pdev = platform_device_alloc("snd-sample-driver", 0);
	if (pdev == NULL) {
		//error
		return -ENOMEM;
	}

	ret = platform_device_add(pdev);
	if (ret != 0) {
		//error
		platform_device_put(pdev);
		return -ENOMEM;
	}

	pr_info("loaded.\n");

	return 0;
}

static void __exit snd_sample_device_exit(void)
{
	platform_device_del(pdev);

	pr_info("unloaded.\n");
}

module_init(snd_sample_device_init);
module_exit(snd_sample_device_exit);

MODULE_AUTHOR("Katsuhiro Suzuki <katsuhiro@katsuster.net>");
MODULE_DESCRIPTION("Sample ALSA SoC device");
MODULE_LICENSE("GPL");
