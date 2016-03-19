
#define pr_fmt(fmt) SND_SAMPLE_DRV_NAME "-i2s: " fmt

#include <linux/module.h>
#include <linux/platform_device.h>

#include "sample-core.h"

int snd_sample_dai_ops_startup(struct snd_pcm_substream *substream, struct snd_soc_dai *dai)
{
	pr_info("DAI ops startup.\n");

	return 0;
}

void snd_sample_dai_ops_shutdown(struct snd_pcm_substream *substream, struct snd_soc_dai *dai)
{
	pr_info("DAI ops shutdown.\n");
}

int snd_sample_dai_ops_hw_params(struct snd_pcm_substream *substream, struct snd_pcm_hw_params *hwparam, struct snd_soc_dai *dai)
{
	pr_info("DAI ops hw_params.\n");

	return 0;
}

int snd_sample_dai_ops_hw_free(struct snd_pcm_substream *substream, struct snd_soc_dai *dai)
{
	pr_info("DAI ops hw_free.\n");

	return 0;
}

int snd_sample_dai_ops_prepare(struct snd_pcm_substream *substream, struct snd_soc_dai *dai)
{
	pr_info("DAI ops prepare.\n");

	return 0;
}

int snd_sample_dai_ops_trigger(struct snd_pcm_substream *substream, int cmd, struct snd_soc_dai *dai)
{
	pr_info("DAI ops trigger.\n");

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
	pr_info("DAI probe.\n");

	return 0;
}

int snd_sample_dai_remove(struct snd_soc_dai *dai)
{
	pr_info("DAI remove.\n");

	return 0;
}

static struct snd_soc_dai_driver snd_sample_dai[] = {
	{
		.name   = SND_SAMPLE_DRV_NAME "-i2s-dai0",
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
		.name   = SND_SAMPLE_DRV_NAME "-i2s-dai1",
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
	.name = SND_SAMPLE_DRV_NAME "-i2s-component",
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
	pr_info("open.\n");

	snd_soc_set_runtime_hwparams(substream, &snd_sample_pcm_hw);

	return 0;
}

static struct snd_pcm_ops snd_sample_pcm_ops = {
	.open = snd_sample_pcm_open,
};




int snd_sample_soc_platform_new(struct snd_soc_pcm_runtime *rtd)
{
	pr_info("New.\n");

	return 0;
}

void snd_sample_soc_platform_free(struct snd_pcm *pcm)
{
	pr_info("Free.\n");
}

static struct snd_soc_platform_driver snd_sample_soc_platform = {
	.pcm_new  = snd_sample_soc_platform_new,
	.pcm_free = snd_sample_soc_platform_free,
	.ops      = &snd_sample_pcm_ops,
};




static int snd_sample_i2s_probe(struct platform_device *pdev)
{
	struct snd_sample_i2s *d;
	struct device *dev = &pdev->dev;
	int result;

	pr_info("Probed.\n");

	d = devm_kzalloc(dev, sizeof(struct snd_sample_i2s),
		GFP_KERNEL);
	if (d == NULL) {
		pr_err("Failed devm_kzalloc(snd_sample_i2s).\n");
		return -ENOMEM;
	}
	d->pdev = pdev;
	d->dev = dev;

	platform_set_drvdata(pdev, d);

	result = devm_snd_soc_register_platform(dev, &snd_sample_soc_platform);
	if (result) {
		pr_err("Failed devm_snd_soc_register_platform().\n");
		return result;
	}

	result = devm_snd_soc_register_component(dev, &snd_sample_soc_component,
		snd_sample_dai, ARRAY_SIZE(snd_sample_dai));
	if (result) {
		pr_err("Failed devm_snd_soc_register_component().\n");
		return result;
	}

	/* example of common utility function in an other *.ko */
	snd_sample_util_func();

	return 0;
}

static int snd_sample_i2s_remove(struct platform_device *pdev)
{
	//struct snd_sample_i2s *d = platform_get_drvdata(pdev);

	pr_info("Removed.\n");

	return 0;
}

static struct platform_driver snd_sample_i2s_driver = {
	.driver = {
		.name   = SND_SAMPLE_DRV_NAME "-i2s"
	},
	.probe  = snd_sample_i2s_probe,
	.remove = snd_sample_i2s_remove,
};
module_platform_driver(snd_sample_i2s_driver);

MODULE_AUTHOR("Katsuhiro Suzuki <katsuhiro@katsuster.net>");
MODULE_DESCRIPTION("Sample ALSA SoC I2S driver");
MODULE_LICENSE("GPL");
