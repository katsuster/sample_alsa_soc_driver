
#ifndef SAMPLE_CORE_H__
#define SAMPLE_CORE_H__

#include <sound/soc.h>

#include "sample-util.h"

struct snd_sample_i2s {
	struct platform_device *pdev;
	struct device *dev;

};

struct snd_sample_i2s_spdif {
	struct platform_device *pdev;
	struct device *dev;

	struct snd_soc_card *card;
};

#endif /* SAMPLE_CORE_H__ */
