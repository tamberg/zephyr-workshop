# IoT Embedded Programmierung mit Zephyr RTOS

## Meta
> Hinweis: Das Workshop-Material ist neu, Typos und Fehler gerne als [Issue](../../issues) erfassen.

Das Internet of Things ([IoT](http://www.tamberg.org/fhnw/2021/hs/IoT01Introduction.pdf)) ist die Verschmelzung von Internet und physischer Welt. IoT embedded Devices haben typischerweise beschränkte Ressourcen, sie werden aber auch mit jeder Generation performanter. Dies ermöglicht komplexere Software vor Ort, stellt aber auch höhere Anforderungen an die Plattform. Zephyr OS, ein open source Betriebssystem für eingebettete Geräte, bietet die notwendigen Abstraktionen, insbesondere POSIX Threads, BSD Sockets und Debugging Mechanismen. Diese erlauben professionelles Software Engineering für robuste, zuverlässige IoT Anwendungen.

### Ablauf
- [Einführung](#einführung)
- [Toolchain Setup](#toolchain-setup)
- [Hardware Setup](#hardware-setup)
- [GPIO & Sensoren](#gpio--sensoren)
- [Threads & Mutex](#threads--mutex)
- [Message Queues](#message-queues)
- [Sockets & HTTP](#sockets--http)
- [Debugging](#debugging)

### Ziel
Der Workshop vermittelt die Grundlagen der embedded Programmierung auf neuster IoT Hardware, mit Zephyr OS, in der Sprache C.

### Publikum
Der Workshop richtet sich an interessierte Personen mit Programmier-Erfahrung, idealerweise in C, aber gerne auch in Python oder Java.

### Voraussetzungen
Teilnehmende brauchen einen Laptop mit MacOS, Windows oder Linux, und falls verfügbar ein Daten-fähiges USB-C Kabel. IoT Hardware inklusive Sensoren steht leihweise zur Verfügung.

Der Workshop setzt ein Wi-Fi Netzwerk voraus, das ohne Portal zugänglich ist. Falls im Gebäude kein solches Netz vorhanden ist, können persönliche Smartphones als Hotspot verwendet werden.

## Einführung
### Zephyr RTOS
> The Zephyr Project strives to deliver the best-in-class RTOS for connected resource-constrained devices, built to be secure and safe.

> Secure - Developed with security in mind. Includes CNA with PSIRT response team.

> Open Source - Available through the Apache 2.0 open source license. Free to use in commercial and non-commercial solutions.

> Product Ready - Long term support (LTS) with security updates. Auditable code base developed with a goal of safety certifications.

> Connected - Supports BLE, Wi-Fi, 802.15.4. Supports standards like 6LoWPAN, CoAP, IPv4, IPv6, Ethernet, USB, CAN and Thread.

https://zephyrproject.org/

> The Zephyr OS is based on a small-footprint kernel designed for use on resource-constrained and embedded systems: from simple embedded environmental sensors and LED wearables to sophisticated embedded controllers, smart watches, and IoT wireless applications.

https://docs.zephyrproject.org/latest/introduction/index.html

> * Extensive suite of Kernel services
> * Multiple Scheduling Algorithms
> * Highly configurable / Modular for flexibility
> * Cross Architecture
> * Memory Protection
> * Compile-time resource definition
> * Optimized Device Driver Model
> * Devicetree Support
> * Native Networking Stack supporting multiple protocols
> * Bluetooth Low Energy 5.0 support
> * Native Linux, macOS, and Windows Development
> * Virtual File System Interface with LittleFS and FATFS Support
> * Powerful multi-backend logging Framework
> * User friendly and full-featured Shell interface
> *  Settings on non-volatile storage
> * Non-volatile storage (NVS)
> * Native POSIX port

https://docs.zephyrproject.org/latest/introduction/index.html#distinguishing-features

### Build System
> CMake is used to build your application together with the Zephyr kernel. A CMake build is done in two stages. The first stage is called configuration. During configuration, the CMakeLists.txt build scripts are executed. After configuration is finished, CMake has an internal model of the Zephyr build, and can generate build scripts that are native to the host platform.

https://docs.zephyrproject.org/latest/build/cmake/index.html

> <img text="Build Config Phase, (c) Zephyr Project" src="https://docs.zephyrproject.org/latest/_images/build-config-phase.svg" width="540"/>
https://docs.zephyrproject.org/latest/build/cmake/index.html#configuration-phase

> <img text="Build Phase I, (c) Zephyr Project" src="https://docs.zephyrproject.org/latest/_images/build-build-phase-1.svg" width="100"/> <img text="Build Phase II, (c) Zephyr Project" src="https://docs.zephyrproject.org/latest/_images/build-build-phase-2.svg" width="100"/> <img text="Build Phase III, (c) Zephyr Project" src="https://docs.zephyrproject.org/latest/_images/build-build-phase-3.svg" width="100"/> <img text="Build Phase IV, (c) Zephyr Project" src="https://docs.zephyrproject.org/latest/_images/build-build-phase-4.svg" width="100"/> <img text="Build Phase V, (c) Zephyr Project" src="https://docs.zephyrproject.org/latest/_images/build-build-phase-5.svg" width="100"/> <img text="Build Phase VI, (c) Zephyr Project" src="https://docs.zephyrproject.org/latest/_images/build-build-phase-6.svg" width="100"/>

https://docs.zephyrproject.org/latest/build/cmake/index.html#pre-build, [#intermediate-binaries](https://docs.zephyrproject.org/latest/build/cmake/index.html#intermediate-binaries), [#intermediate-binaries-post-processing](https://docs.zephyrproject.org/latest/build/cmake/index.html#intermediate-binaries-post-processing), [#final-binary](https://docs.zephyrproject.org/latest/build/cmake/index.html#final-binary), [#post-processing](https://docs.zephyrproject.org/latest/build/cmake/index.html#post-processing)

### Device Tree
https://docs.zephyrproject.org/latest/build/dts/intro.html

### ...

## Toolchain Setup
https://docs.zephyrproject.org/latest/develop/getting_started/index.html

### Zephyr (MacOS)
    $ brew install cmake ninja gperf python3 ccache qemu dtc wget
    $ pip3 install -U west

    $ mkdir Zephyr
    $ cd Zephyr

    $ west init zephyrproject
    $ cd zephyrproject
    $ west update
    $ west zephyr-export
    $ pip3 install -r zephyr/scripts/requirements.txt 

    $ wget https://github.com/zephyrproject-rtos/sdk-ng/releases/download/v0.14.1/zephyr-sdk-0.14.1_macos-x86_64.tar.gz
    $ wget -O - https://github.com/zephyrproject-rtos/sdk-ng/releases/download/v0.14.1/sha256.sum | shasum --check --ignore-missing
    $ tar xvf zephyr-sdk-0.14.1_macos-x86_64.tar.gz
    $ cd zephyr-sdk-0.14.1
    $ ./setup.sh

(Tipps zu Brew, XCode, etc. siehe https://learn.adafruit.com/blinking-led-with-zephyr-rtos/installing-zephyr-osx)

### Zephyr (Linux)
TODO

### Zephyr (Windows)
TODO

### Hello World (any OS)
    $ west build -p auto -b qemu_x86 samples/hello_world
    $ west build -t run

## Hardware Setup
https://docs.zephyrproject.org/latest/boards/index.html

### ESP32-S2 (MacOS)
https://docs.zephyrproject.org/latest/boards/xtensa/esp32s2_saola/doc/index.html

https://www.adafruit.com/product/5325 (Adafruit QT Py ESP32-S2 WiFi Dev Board)

https://learn.adafruit.com/assets/107493 (Pinout)

    $ pip3 install --upgrade esptool
    $ cd ~/Documents/Zephyr/zephyrproject
    $ west espressif update
    $ cd ~/Documents/Zephyr/zephyrproject/zephyr
    $ cat samples/basic/blinky/src/main.c
    $ west build -p auto -b esp32s2_saola samples/basic/blinky
    $ west flash

### ESP32-C3 (MacOS)
https://docs.zephyrproject.org/latest/boards/riscv/esp32c3_devkitm/doc/index.html

https://www.adafruit.com/product/5405 (Adafruit QT Py ESP32-C3 WiFi Dev Board)

https://learn.adafruit.com/assets/109663 (Pinout)

    $ west espressif update
    $ cat samples/hello_world/src/main.c
    $ west build -p auto -b esp32c3_devkitm samples/hello_world
    <press & hold reset, press user button, release user button, release reset>
    $ west flash
    $ west espressif monitor

TODO: https://forums.adafruit.com/viewtopic.php?f=8&t=191501&p=926488#p926488

### STM32F405 (MacOS)
    $ brew install dfu-util
    $ brew install gcc-arm-embedded --cask
    $ which arm-none-eabi-gdb
    $ nano ~/.zshenv
    export ZEPHYR_TOOLCHAIN_VARIANT=gnuarmemb
	export GNUARMEMB_TOOLCHAIN_PATH=/usr/local/
    $ source ~/.zshenv
    $ echo $ZEPHYR_TOOLCHAIN_VARIANT
    $ echo $GNUARMEMB_TOOLCHAIN_PATH
    $ cat samples/basic/blinky/src/main.c
    $ west build -p auto -b adafruit_feather_stm32f405 samples/basic/blinky
    $ west flash

## GPIO & Sensoren
* https://github.com/zephyrproject-rtos/zephyr/tree/main/samples/basic/blinky
* https://github.com/zephyrproject-rtos/zephyr/tree/main/samples/basic/button
* https://github.com/zephyrproject-rtos/zephyr/tree/main/samples/sensor/dht
    * https://github.com/zephyrproject-rtos/zephyr/blob/main/samples/sensor/dht/boards/nrf52dk_nrf52832.overlay
* https://github.com/zephyrproject-rtos/zephyr/tree/main/samples/sensor

## Threads & Mutex
TODO

## Message Queues
TODO

## Sockets & HTTP
https://docs.zephyrproject.org/latest/connectivity/networking/net-stack-architecture.html

https://docs.zephyrproject.org/latest/connectivity/networking/api/sockets.html

TODO

## Debugging
    $ west debug

* https://www.zephyrproject.org/zephyr-rtos-boards-configurations-hardware-interaction/ (Debugging)
* https://blog.golioth.io/debugging-zephyr-for-beginners-printk-and-the-logging-subsystem/
* https://docs.zephyrproject.org/latest/kernel/services/other/fatal.html (Runtime Assertions)
* https://www.irnas.eu/remote-zephyr-development-with-segger-tunnel-and-a-raspberry-pi/
