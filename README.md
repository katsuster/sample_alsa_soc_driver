# sample_alsa_soc_driver

This is a sample code for Linux ALSA SoC sound card device driver.

# How to Use

Get the Linux kernel source and extract to /usr/src/linux.

* ex) apt-get install linux-source
* ex) wget https://cdn.kernel.org/pub/linux/kernel/v4.x/linux-x.y.z.tar.xz

Build the Linux kernel.

This device driver depends on ALSA SoC audio kernel libraries.
Please set CONFIG_SND_SOC=m (or y) to enable the libraries.

    # cd /usr/src/linux
    # make menuconfig
    # make

Location of CONFIG_SND_SOC as follows.

    -> Device Drivers
      -> Sound card support (CONFIG_SOUND)
        -> Advanced Linux Sound Architecture (CONFIG_SND)
          -> ALSA for SoC audio support (CONFIG_SND_SOC)

Build this sample.

    $ cd sample_alsa_soc_driver
    $ make
    make ARCH=x86_64 CROSS_COMPILE= -C /usr/src/linux M=/home/user/sample_alsa_soc_driver LDDINC=/home/user/sample_alsa_soc_driver modules
    make[1]: Entering directory '/usr/src/linux'
      CC [M]  /home/katsuhiro/share/projects/c/sample_alsa_soc_driver/snd-sample-device.o
      CC [M]  /home/katsuhiro/share/projects/c/sample_alsa_soc_driver/snd-sample-utils.o
      ...
      CC      /home/katsuhiro/share/projects/c/sample_alsa_soc_driver/snd-sample-drv.mod.o
      LD [M]  /home/katsuhiro/share/projects/c/sample_alsa_soc_driver/snd-sample-drv.ko
    make[1]: Leaving directory '/usr/src/linux'

Do insmod and rmmod.

Run modprobe if you set CONFIG_SND_SOC=m before running insmod.

    # modprobe snd-soc-core

    # insmod snd-sample-core.ko
    # insmod snd-sample-i2s.ko
    # insmod snd-sample-i2s-spdif.ko
    # insmod snd-sample-device.ko
    snd-sample-i2s: Probed.
    snd-sample: util_func.
    snd-sample-i2s-spdif: Probed.
    snd-sample-i2s: DAI probe.
    snd-sample-i2s: New.
    snd-sample-i2s-spdif snd-sample-i2s-spdif.0: dit-hifi <-> snd-sample-i2s-dai0 mapping ok
    snd-sample-dev: loaded.

    # rmmod snd-sample-device
    snd-sample-i2s-spdif: Removed.
    snd-sample-i2s: DAI remove.
    snd-sample-i2s: Free.
    snd-sample-i2s: Removed.
    snd-sample-dev: unloaded.

    # rmmod snd-sample-i2s
    # rmmod snd-sample-i2s-spdif
    # rmmod snd-sample-core
