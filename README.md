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

    # insmod snd-sample-drv.ko
    # insmod snd-sample-dev1.ko
    snd-sample: Probed.
    snd-sample: DAI probe.
    snd-sample: New.
    snd_sample_driver snd_sample_driver.0: snd-soc-dummy-dai <-> sample_dai0 mapping ok
    snd-sample: loaded.

    # rmmod snd-sample-dev1
    snd-sample: Removed.
    snd-sample: DAI remove.
    snd-sample: Free.
    snd-sample: unloaded.
    # rmmod snd-sample-drv
