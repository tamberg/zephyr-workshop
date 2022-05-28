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
https://zephyrproject.org/
https://docs.zephyrproject.org/latest/introduction/index.html

### Build System
https://docs.zephyrproject.org/latest/build/cmake/index.html

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
TODO

## Threads & Mutex
TODO

## Message Queues
TODO

## Sockets & HTTP
TODO

## Debugging
    $ west debug

* https://www.zephyrproject.org/zephyr-rtos-boards-configurations-hardware-interaction/ (Debugging)
* https://blog.golioth.io/debugging-zephyr-for-beginners-printk-and-the-logging-subsystem/
* https://docs.zephyrproject.org/latest/kernel/services/other/fatal.html (Runtime Assertions)
* https://www.irnas.eu/remote-zephyr-development-with-segger-tunnel-and-a-raspberry-pi/
