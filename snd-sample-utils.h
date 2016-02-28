
#ifndef SND_SAMPLE_UTILS_H__
#define SND_SAMPLE_UTILS_H__

#include <linux/kernel.h>
#include <linux/version.h>

#define SND_SAMPLE_DRV_NAME "snd-sample"

#define PRINT_ERR(fmt, args...)  printk(KERN_ERR     SND_SAMPLE_DRV_NAME ": " fmt, ##args)
#define PRINT_WARN(fmt, args...) printk(KERN_WARNING SND_SAMPLE_DRV_NAME ": " fmt, ##args)
#define PRINT_INFO(fmt, args...) printk(KERN_NOTICE  SND_SAMPLE_DRV_NAME ": " fmt, ##args)

#ifdef CONFIG_SND_SAMPLE_DEBUG
#  define DPRINT(fmt, args...) printk(KERN_NOTICE SND_SAMPLE_DRV_NAME ": " fmt, ##args)
#else
#  define DPRINT(fmt, args...) no_printk(KERN_NOTICE SND_SAMPLE_DRV_NAME ": " fmt, ##args)
#endif

#endif /* SND_SAMPLE_UTILS_H__ */
