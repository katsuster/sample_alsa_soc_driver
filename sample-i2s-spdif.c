
#include <linux/module.h>
#include <linux/platform_device.h>

#include "sample-core.h"

static struct snd_soc_dai_link snd_sample_soc_dai_links[] = {
	{
		.name           = SND_SAMPLE_DRV_NAME "-dai-link",
		.stream_name    = SND_SAMPLE_DRV_NAME "-stream",
		.cpu_dai_name   = SND_SAMPLE_DRV_NAME "-i2s-dai0",
		.platform_name  = SND_SAMPLE_DRV_NAME "-i2s.0",

#if IS_ENABLED(CONFIG_SND_SOC_SPDIF)
		/* use this part if you enable the CONFIG_SND_SOC_SPDIF */
		.codec_name     = "spdif-dit.0",
		.codec_dai_name = "dit-hifi",
#else /* CONFIG_SND_SOC_SPDIF */
		/* use this part if you have no CODEC driver */
		.codec_name     = "snd-soc-dummy",
		.codec_dai_name = "snd-soc-dummy-dai",
#endif /* CONFIG_SND_SOC_SPDIF */
	},
};

static int snd_sample_i2s_spdif_probe(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	struct snd_sample_i2s_spdif *d;
	int result;

	dev_info(dev, "Probed.\n");

	d = devm_kzalloc(dev, sizeof(struct snd_sample_i2s_spdif),
		GFP_KERNEL);
	if (d == NULL) {
		dev_err(dev, "Failed devm_kzalloc(snd_sample_i2s_spdif).\n");
		return -ENOMEM;
	}
	d->pdev = pdev;
	d->dev = dev;

	d->card = devm_kzalloc(dev, sizeof(struct snd_soc_card),
		GFP_KERNEL);
	if (d == NULL) {
		dev_err(dev, "Failed devm_kzalloc(snd_soc_card).\n");
		return -ENOMEM;
	}
	snd_soc_card_set_drvdata(d->card, d);

	d->card->name      = SND_SAMPLE_DRV_NAME "-card";
	d->card->dev       = dev;
	d->card->owner     = THIS_MODULE;
	d->card->dai_link  = snd_sample_soc_dai_links;
	d->card->num_links = ARRAY_SIZE(snd_sample_soc_dai_links);
	result = snd_soc_register_card(d->card);
	if (result) {
		dev_err(dev, "Failed snd_soc_register_card().\n");
		return result;
	}

	return 0;
}

static int snd_sample_i2s_spdif_remove(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	struct snd_soc_card *card = platform_get_drvdata(pdev);
	struct snd_sample_i2s_spdif *d = snd_soc_card_get_drvdata(card);

	dev_info(dev, "Removed.\n");

	snd_soc_unregister_card(d->card);

	return 0;
}

static struct platform_driver snd_sample_i2s_spdif_driver = {
	.driver = {
		.name   = SND_SAMPLE_DRV_NAME "-i2s-spdif"
	},
	.probe  = snd_sample_i2s_spdif_probe,
	.remove = snd_sample_i2s_spdif_remove,
};
module_platform_driver(snd_sample_i2s_spdif_driver);

MODULE_AUTHOR("Katsuhiro Suzuki <katsuhiro@katsuster.net>");
MODULE_DESCRIPTION("Sample ALSA SoC driver");
MODULE_LICENSE("GPL");
