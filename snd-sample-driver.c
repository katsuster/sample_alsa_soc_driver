
#include <linux/module.h>
#include <linux/platform_device.h>

#include "snd-sample-driver.h"

int snd_sample_dai_ops_startup(struct snd_pcm_substream *substream, struct snd_soc_dai *dai)
{
	PRINT_INFO("DAI ops startup.\n");

	return 0;
}

void snd_sample_dai_ops_shutdown(struct snd_pcm_substream *substream, struct snd_soc_dai *dai)
{
	PRINT_INFO("DAI ops shutdown.\n");
}

int snd_sample_dai_ops_hw_params(struct snd_pcm_substream *substream, struct snd_pcm_hw_params *hwparam, struct snd_soc_dai *dai)
{
	PRINT_INFO("DAI ops hw_params.\n");

	return 0;
}

int snd_sample_dai_ops_hw_free(struct snd_pcm_substream *substream, struct snd_soc_dai *dai)
{
	PRINT_INFO("DAI ops hw_free.\n");

	return 0;
}

int snd_sample_dai_ops_prepare(struct snd_pcm_substream *substream, struct snd_soc_dai *dai)
{
	PRINT_INFO("DAI ops prepare.\n");

	return 0;
}

int snd_sample_dai_ops_trigger(struct snd_pcm_substream *substream, int cmd, struct snd_soc_dai *dai)
{
	PRINT_INFO("DAI ops trigger.\n");

	return 0;
}

static struct snd_soc_dai_ops snd_sample_dai_ops = {
	.startup   = snd_sample_dai_ops_startup,
	.shutdown  = snd_sample_dai_ops_shutdown,
	.hw_params = snd_sample_dai_ops_hw_params,
	.hw_free   = snd_sample_dai_ops_hw_free,
	.prepare   = snd_sample_dai_ops_prepare,
	.trigger   = snd_sample_dai_ops_trigger,
};

int snd_sample_dai_probe(struct snd_soc_dai *dai)
{
	PRINT_INFO("DAI probe.\n");

	return 0;
}

int snd_sample_dai_remove(struct snd_soc_dai *dai)
{
	PRINT_INFO("DAI remove.\n");
	return 0;
}

static struct snd_soc_dai_driver snd_sample_dai[] = {
	{
		.name   = "sample_dai0",
		.probe  = snd_sample_dai_probe,
		.remove = snd_sample_dai_remove,
		.playback = {
			.formats = SNDRV_PCM_FMTBIT_S16_LE | SNDRV_PCM_FMTBIT_S32_LE,
			.rates   = SNDRV_PCM_RATE_8000_48000,
			.channels_min = 1,
			.channels_max = 2,
		},
		.ops = &snd_sample_dai_ops,
	},
	{
		.name   = "sample_dai1",
		.probe  = snd_sample_dai_probe,
		.remove = snd_sample_dai_remove,
		.capture = {
			.formats = SNDRV_PCM_FMTBIT_S16_LE | SNDRV_PCM_FMTBIT_S32_LE,
			.rates   = SNDRV_PCM_RATE_8000_48000,
			.channels_min = 1,
			.channels_max = 2,
		},
		.ops = &snd_sample_dai_ops,
	},
};

static struct snd_soc_component_driver snd_sample_soc_component = {
	.name = "snd-sample-component",
};

static struct snd_soc_dai_link snd_sample_soc_dai_links[] = {
	{
		.name           = "sample_dai_link",
		.stream_name    = "sample_stream",
		.cpu_dai_name   = "sample_dai0",
		.platform_name  = "snd_sample_driver.0",
		.codec_name     = "snd-soc-dummy",
		.codec_dai_name = "snd-soc-dummy-dai",
	},
};




static struct snd_pcm_hardware snd_sample_pcm_hw = {
	.info = SNDRV_PCM_INFO_MMAP |
		SNDRV_PCM_INFO_MMAP_VALID |
		SNDRV_PCM_INFO_INTERLEAVED,
	.period_bytes_min	= 256,
	.period_bytes_max	= 256 * 1024,
	.periods_min		= 2,
	.periods_max		= 127,
	.buffer_bytes_max	= 512 * 1024,
};

static int snd_sample_pcm_open(struct snd_pcm_substream *substream)
{
	PRINT_INFO("open.\n");

	snd_soc_set_runtime_hwparams(substream, &snd_sample_pcm_hw);

	return 0;
}

static struct snd_pcm_ops snd_sample_pcm_ops = {
	.open = snd_sample_pcm_open,
};




int snd_sample_soc_platform_new(struct snd_soc_pcm_runtime *rtd)
{
	PRINT_INFO("New.\n");

	return 0;
}

void snd_sample_soc_platform_free(struct snd_pcm *pcm)
{
	PRINT_INFO("Free.\n");
}

static struct snd_soc_platform_driver snd_sample_soc_platform = {
	.pcm_new  = snd_sample_soc_platform_new,
	.pcm_free = snd_sample_soc_platform_free,
	.ops      = &snd_sample_pcm_ops,
};




static int snd_sample_probe(struct platform_device *pdev)
{
	struct snd_sample_device *d;
	struct device *dev = &pdev->dev;
	int result;

	PRINT_INFO("Probed.\n");

	d = devm_kzalloc(dev, sizeof(struct snd_sample_device),
		GFP_KERNEL);
	if (d == NULL) {
		PRINT_ERR("Failed devm_kzalloc(snd_sample_device).\n");
		return -ENOMEM;
	}
	d->pdev = pdev;
	d->dev = dev;

	d->card = devm_kzalloc(dev, sizeof(struct snd_soc_card),
		GFP_KERNEL);
	if (d == NULL) {
		PRINT_ERR("Failed devm_kzalloc(snd_soc_card).\n");
		return -ENOMEM;
	}

	result = devm_snd_soc_register_platform(dev, &snd_sample_soc_platform);
	if (result) {
		PRINT_ERR("Failed devm_snd_soc_register_platform().\n");
		return result;
	}

	result = devm_snd_soc_register_component(dev, &snd_sample_soc_component,
		snd_sample_dai, ARRAY_SIZE(snd_sample_dai));
	if (result) {
		PRINT_ERR("Failed devm_snd_soc_register_component().\n");
		return result;
	}

	d->card->name  = "sample_soc_card";
	d->card->dev   = dev;
	d->card->owner = THIS_MODULE;
	d->card->dai_link = snd_sample_soc_dai_links;
	d->card->num_links = ARRAY_SIZE(snd_sample_soc_dai_links);
	snd_soc_card_set_drvdata(d->card, d);
	result = snd_soc_register_card(d->card);
	if (result) {
		PRINT_ERR("Failed snd_soc_register_card().\n");
		return result;
	}

	return 0;
}

static int snd_sample_remove(struct platform_device *pdev)
{
	struct snd_soc_card *card = platform_get_drvdata(pdev);
	struct snd_sample_device *d = snd_soc_card_get_drvdata(card);
	PRINT_INFO("Removed.\n");

	snd_soc_unregister_card(d->card);

	return 0;
}

static struct platform_driver snd_sample_driver = {
	.probe  = snd_sample_probe,
	.remove = snd_sample_remove,
	.driver = {
		.name   = "snd_sample_driver"
	},
};

module_platform_driver(snd_sample_driver);

MODULE_AUTHOR("Katsuhiro Suzuki <katsuhiro@katsuster.net>");
MODULE_DESCRIPTION("Sample ALSA SoC driver");
MODULE_LICENSE("GPL");
