# IoT Embedded Programmierung mit Zephyr OS
Das Internet of Things (IoT) ist die Verschmelzung von Internet und physischer Welt. IoT embedded Devices haben typischerweise beschränkte Ressourcen, sie werden aber auch mit jeder Generation performanter. Dies ermöglicht komplexere Software vor Ort, stellt aber auch höhere Anforderungen an die Plattform. Zephyr OS, ein open source Betriebssystem für eingebettete Geräte, bietet die notwendigen Abstraktionen, insbesondere POSIX Threads, BSD Sockets und Debugging Mechanismen. Diese erlauben professionelles Software Engineering für robuste, zuverlässige IoT Anwendungen.

- [Einführung](#einführung)
- [Toolchain Setup](#toolchain-setup)
- [Hardware Setup](#hardware-setup)
- [GPIO & Sensoren](#gpio--sensoren)
- [Threads & Mutex](#threads--mutex)
- [Message Queues](#message-queues)
- [Sockets & HTTP](#sockets--http)
- [Debugging](#debugging)

Der Workshop vermittelt die Grundlagen der embedded Programmierung auf neuster IoT Hardware, mit Zephyr OS, in der Sprache C.

Der Workshop richtet sich an interessierte Personen mit Programmier-Erfahrung, idealerweise in C, aber gerne auch in Python oder Java.

Teilnehmende brauchen einen Laptop mit MacOS, Windows oder Linux, und falls verfügbar ein Daten-fähiges USB-C Kabel. IoT Hardware inklusive Sensoren steht leihweise zur Verfügung.

Der Workshop setzt ein Wi-Fi Netzwerk voraus, das ohne Portal zugänglich ist. Falls im Gebäude kein solches Netz vorhanden ist, können persönliche Smartphones als Hotspot verwendet werden.

## Einführung
TODO

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

## Hardware Setup
https://docs.zephyrproject.org/latest/boards/index.html
https://docs.zephyrproject.org/latest/boards/xtensa/esp32s2_saola/doc/index.html

### ESP32-S2 (MacOS)
    $ cd ~/Documents/Zephyr/zephyrproject
    $ west espressif update
    $ cd ~/Documents/Zephyr/zephyrproject/zephyr
    $ cat samples/hello_world/src/main.c
    $ west build -b esp32s2_saola samples/hello_world

    $ pip3 install --upgrade esptool

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
* https://www.zephyrproject.org/zephyr-rtos-boards-configurations-hardware-interaction/ (Debugging)
* https://blog.golioth.io/debugging-zephyr-for-beginners-printk-and-the-logging-subsystem/
* https://docs.zephyrproject.org/latest/kernel/services/other/fatal.html (Runtime Assertions)
* https://www.irnas.eu/remote-zephyr-development-with-segger-tunnel-and-a-raspberry-pi/
