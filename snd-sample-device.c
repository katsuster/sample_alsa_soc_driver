
#include <linux/module.h>
#include <linux/platform_device.h>

#include "snd-sample-device.h"

static struct platform_device *pdev = NULL;

static int __init snd_sample_device_init(void)
{
	int ret;

	pdev = platform_device_alloc("snd_sample_driver", 0);
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

	PRINT_INFO("loaded.\n");

	return 0;
}

static void __exit snd_sample_device_exit(void)
{
	platform_device_del(pdev);

	PRINT_INFO("unloaded.\n");
}

module_init(snd_sample_device_init);
module_exit(snd_sample_device_exit);

MODULE_AUTHOR("Katsuhiro Suzuki <katsuhiro@katsuster.net>");
MODULE_DESCRIPTION("Sample ALSA SoC device");
MODULE_LICENSE("GPL");
