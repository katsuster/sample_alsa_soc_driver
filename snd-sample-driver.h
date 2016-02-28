
#ifndef SND_SAMPLE_DRIVER_H__
#define SND_SAMPLE_DRIVER_H__

#include <sound/soc.h>

#include "snd-sample-utils.h"

struct snd_sample_device {
	struct platform_device *pdev;
	struct device *dev;

	struct snd_soc_card *card;
};

#endif /* SND_SAMPLE_DRIVER_H__ */
