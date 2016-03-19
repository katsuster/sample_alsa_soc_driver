
#define pr_fmt(fmt) SND_SAMPLE_DRV_NAME "-dev: " fmt

#include <linux/module.h>
#include <linux/platform_device.h>

#include "sample-core.h"

static struct platform_device *pdev_i2s = NULL;
static struct platform_device *pdev_spdif = NULL;
static struct platform_device *pdev_i2s_spdif = NULL;

static int __init snd_sample_device_init(void)
{
	int ret;

	/* Add sample I2S device */
	pdev_i2s = platform_device_alloc(SND_SAMPLE_DRV_NAME "-i2s", 0);
	if (pdev_i2s == NULL) {
		ret = -ENOMEM;
		goto err_out;
	}

	ret = platform_device_add(pdev_i2s);
	if (ret != 0) {
		ret = -ENOMEM;
		goto err_out_i2s;
	}

	/*
	 * Add SPDIF CODEC.
	 *
	 * NOTE: You should enable the CONFIG_SND_SOC_SPDIF to build
	 *       SPDIF CODEC driver.
	 *       And insmod or modprobe 'snd-soc-spdif-rx.ko' module.
	 */
	pdev_spdif = platform_device_alloc("spdif-dit", 0);
	if (pdev_spdif == NULL) {
		ret = -ENOMEM;
		goto err_out_i2s;
	}

	ret = platform_device_add(pdev_spdif);
	if (ret != 0) {
		ret = -ENOMEM;
		goto err_out_spdif;
	}

	/* Add sample ASoC card */
	pdev_i2s_spdif = platform_device_alloc(SND_SAMPLE_DRV_NAME "-i2s-spdif", 0);
	if (pdev_i2s_spdif == NULL) {
		ret = -ENOMEM;
		goto err_out_spdif;
	}

	ret = platform_device_add(pdev_i2s_spdif);
	if (ret != 0) {
		ret = -ENOMEM;
		goto err_out_i2s_spdif;
	}

	pr_info("loaded.\n");

	return 0;

err_out_i2s_spdif:
	platform_device_del(pdev_i2s_spdif);

err_out_spdif:
	platform_device_del(pdev_spdif);

err_out_i2s:
	platform_device_del(pdev_i2s);

err_out:
	return ret;
}

static void __exit snd_sample_device_exit(void)
{
	platform_device_del(pdev_i2s_spdif);
	platform_device_del(pdev_spdif);
	platform_device_del(pdev_i2s);

	pr_info("unloaded.\n");
}

module_init(snd_sample_device_init);
module_exit(snd_sample_device_exit);

MODULE_AUTHOR("Katsuhiro Suzuki <katsuhiro@katsuster.net>");
MODULE_DESCRIPTION("Sample ALSA SoC device");
MODULE_LICENSE("GPL");
