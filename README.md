# IoT Embedded Programmierung mit Zephyr RTOS

## Workshop
> Hinweis: [Neuer Workshop](https://workshoptage.ch/workshops/2022/iot-embedded-programmierung-mit-zephyr-os/) für die [Workshop Tage 2022](https://workshoptage.ch/) von [CH Open](https://www.ch-open.ch/). Feedback gerne [als Issue erfassen](../../issues).

Das Internet of Things ([IoT](http://www.tamberg.org/fhnw/2021/hs/IoT01Introduction.pdf)) ist die Verschmelzung von Internet und physischer Welt. IoT embedded Devices haben typischerweise beschränkte Ressourcen, sie werden aber auch mit jeder Generation performanter. Dies ermöglicht komplexere Software vor Ort, stellt aber auch höhere Anforderungen an die Plattform. Zephyr RTOS, ein open source Betriebssystem für eingebettete Geräte, bietet die notwendigen Abstraktionen, insbesondere POSIX Threads, BSD Sockets und Debugging Mechanismen. Diese erlauben professionelles Software Engineering für robuste, zuverlässige IoT Anwendungen.

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

> Extensive suite of Kernel services • Multiple Scheduling Algorithms • Highly configurable / Modular for flexibility • Cross Architecture • Memory Protection • Compile-time resource definition • Optimized Device Driver Model • Devicetree Support • Native Networking Stack supporting multiple protocols • Bluetooth Low Energy 5.0 support • Native Linux • macOS • and Windows Development • Virtual File System Interface with LittleFS and FATFS Support • Powerful multi-backend logging Framework • User friendly and full-featured Shell interface • Settings on non-volatile storage • Non-volatile storage (NVS) • Native POSIX port.

https://docs.zephyrproject.org/latest/introduction/index.html#distinguishing-features

### Kernel Services
> The Zephyr kernel lies at the heart of every Zephyr application. It provides a low footprint, high performance, multi-threaded execution environment with a rich set of available features. The rest of the Zephyr ecosystem, including device drivers, networking stack, and application-specific code, uses the kernel’s features to create a complete application.

> * Scheduling, Interrupts, and Synchronization
> * Data Passing
> * Memory Management
> * Timing
> * Other

https://docs.zephyrproject.org/latest/kernel/services/index.html

### OS Services
> Cryptography • Debugging • Device Management • File Systems • Formatted Output • Logging • Tracing • Resource Management • Modbus • Asynchronous Notifications • Power Management • OS Abstraction • Shell • Settings • State Machine Framework • Storage • Task Watchdog • Trusted Firmware-M • USB device support • Virtualization • Miscellaneous.

https://docs.zephyrproject.org/latest/services/index.html

### Build System
> CMake is used to build your application together with the Zephyr kernel. A CMake build is done in two stages. The first stage is called configuration. During configuration, the CMakeLists.txt build scripts are executed. After configuration is finished, CMake has an internal model of the Zephyr build, and can generate build scripts that are native to the host platform.

https://docs.zephyrproject.org/latest/build/cmake/index.html

> <img text="Build Config Phase, (c) Zephyr Project" src="https://docs.zephyrproject.org/latest/_images/build-config-phase.svg" width="540"/>
https://docs.zephyrproject.org/latest/build/cmake/index.html#configuration-phase

> <img text="Build Phase I, (c) Zephyr Project" src="https://docs.zephyrproject.org/latest/_images/build-build-phase-1.svg" width="150"/> <img text="Build Phase II, (c) Zephyr Project" src="https://docs.zephyrproject.org/latest/_images/build-build-phase-2.svg" width="150"/> <img text="Build Phase III, (c) Zephyr Project" src="https://docs.zephyrproject.org/latest/_images/build-build-phase-3.svg" width="150"/> <img text="Build Phase IV, (c) Zephyr Project" src="https://docs.zephyrproject.org/latest/_images/build-build-phase-4.svg" width="150"/> <img text="Build Phase V, (c) Zephyr Project" src="https://docs.zephyrproject.org/latest/_images/build-build-phase-5.svg" width="150"/> <img text="Build Phase VI, (c) Zephyr Project" src="https://docs.zephyrproject.org/latest/_images/build-build-phase-6.svg" width="150"/>

https://docs.zephyrproject.org/latest/build/cmake/index.html#pre-build, [#intermediate-binaries](https://docs.zephyrproject.org/latest/build/cmake/index.html#intermediate-binaries), [#intermediate-binaries-post-processing](https://docs.zephyrproject.org/latest/build/cmake/index.html#intermediate-binaries-post-processing), [#final-binary](https://docs.zephyrproject.org/latest/build/cmake/index.html#final-binary), [#post-processing](https://docs.zephyrproject.org/latest/build/cmake/index.html#post-processing)

### Devicetree Überblick
> A devicetree is a hierarchical data structure that describes hardware.

> There are two types of devicetree input files: devicetree sources and devicetree bindings. The sources contain the devicetree itself. The bindings describe its contents, including data types.

> <img text="Devicetree Build Flow, (c) Zephyr Project" src="https://docs.zephyrproject.org/latest/_images/zephyr_dt_build_flow.png" width="540"/>

https://docs.zephyrproject.org/latest/build/dts/intro.html

> a devicetree is a tree. The human-readable text format for this tree is called DTS (for devicetree source)

> Devicetree nodes have _paths_ identifying their locations in the tree [and] _properties_ [which] are name/value pairs.

> In practice, devicetree nodes usually correspond to some hardware, and the node hierarchy reflects the hardware’s physical layout.

https://docs.zephyrproject.org/latest/build/dts/intro.html#syntax-and-structure

> A devicetree binding declares requirements on the contents of nodes, and provides semantic information about the contents of valid nodes. Zephyr devicetree bindings are YAML files

https://docs.zephyrproject.org/latest/build/dts/bindings.html

### Devicetree im Detail

> Step-by-step advice for getting things done with devicetree.

> Show final devicetree after a build
    
    $ cat build/zephyr/zephyr.dts

> Show final devicetree includes

    $ cat build/zephyr/include/generated/devicetree_unfixed.h

https://docs.zephyrproject.org/latest/build/dts/howtos.html

> Devicetree input (green) and output (yellow) files

> <img text="Devicetree Inputs and Outputs, (c) Zephyr Project" src="https://docs.zephyrproject.org/latest/_images/zephyr_dt_inputs_outputs.svg" width="640"/>

> There are four types of devicetree input files:
>
> * sources (.dts)
> * includes (.dtsi)
> * overlays (.overlay)
> * bindings (.yaml)

> Every supported board has a BOARD.dts file describing its hardware

> BOARD.dts includes one or more .dtsi files [which] describe the CPU or system-on-chip Zephyr runs on [and] common hardware features shared by multiple boards.

> BOARD.dts can be extended or modified using [...] .overlay [...] DTS files [to] adapt the base devicetree for different purposes

> Zephyr applications can use overlays to enable a peripheral that is disabled by default, select a sensor on the board for an application specific purpose, etc. [or] defining shields.

https://docs.zephyrproject.org/latest/build/dts/intro.html#input-and-output-files

### Devicetree Troubleshooting

> Here are some tips for fixing devicetree related code.
>
> * Try again with a pristine build directory
> * Make sure <devicetree.h> is included
> * Make sure you’re using the right names
> * Look at the preprocessor output
> * Validate properties
> * Check for missing bindings
> * Errors with DT_INST_() APIs

https://docs.zephyrproject.org/latest/build/dts/troubleshooting.html#dt-trouble

## Toolchain Setup
https://docs.zephyrproject.org/latest/develop/getting_started/index.html

### Zephyr
#### Zephyr auf MacOS
Install the Zephyr command line tool _west_ 

    $ brew install cmake ninja gperf python3 ccache qemu dtc wget
    $ pip3 install -U west

Create a Zephyr workspace _zephyrproject_

    $ mkdir ~/Documents/Zephyr
    $ cd ~/Documents/Zephyr
    $ west init zephyrproject
    $ cd zephyrproject
    $ west update
    $ west zephyr-export
    $ pip3 install -r zephyr/scripts/requirements.txt 

Install the Zephyr SDK

    $ cd ~
    $ wget https://github.com/zephyrproject-rtos/sdk-ng/releases/download/v0.14.2/zephyr-sdk-0.14.2_macos-x86_64.tar.gz
    $ wget -O - https://github.com/zephyrproject-rtos/sdk-ng/releases/download/v0.14.2/sha256.sum | shasum --check --ignore-missing
    $ tar xvf zephyr-sdk-0.14.2_macos-x86_64.tar.gz
    $ cd zephyr-sdk-0.14.2
    $ ./setup.sh

Clone the workshop directory into the workspace

    $ cd ~/Documents/Zephyr/zephyrproject
    $ git clone https://github.com/tamberg/zephyr-workshop

(Tipps zu Brew, XCode, etc. siehe https://learn.adafruit.com/blinking-led-with-zephyr-rtos/installing-zephyr-osx)

#### Zephyr auf Linux
TODO

#### Zephyr auf Windows
TODO

### Hello World
Siehe [samples/hello_world](https://github.com/zephyrproject-rtos/zephyr/blob/main/samples/hello_world)

    #include <zephyr/zephyr.h>

    void main(void) {
        printk("Hello World! %s\n", CONFIG_BOARD);
    }

#### Hello World auf x86 Qemu
Dieses Beispiel läuft ohne embedded Hardware, auf MacOS, Linux oder Windows.

    $ west build -p auto -b qemu_x86 samples/hello_world
    $ west build -t run

    SeaBIOS (version rel-1.15.0-0-g2dd4b9b3f840-prebuilt.qemu.org)
    Booting from ROM..
    *** Booting Zephyr OS build zephyr-v3.0.0-3797-gc28874657b70  ***
    Hello World! qemu_x86

### West Troubleshooting
https://docs.zephyrproject.org/latest/develop/west/troubleshooting.html

## Hardware Setup
* https://docs.zephyrproject.org/latest/boards/index.html (Zephyr Project list of "supported" boards)
* https://www.espressif.com/en/news/Zephyr_updates (Update on Espressif’s Support for Zephyr)

### Boards
* [ESP32-S2](#esp32-s2)
* [ESP32-C3](#esp32-c3)
* [STM32F405](#stm32f405)

### ESP32-S2
#### Buy
https://www.adafruit.com/product/5325 (Adafruit QT Py ESP32-S2 WiFi Dev Board)

#### Board
https://docs.zephyrproject.org/latest/boards/xtensa/esp32s2_saola/doc/index.html

#### Pinout
<img text="ESP32-S2 Pinout, (c) Adafruit" src="https://cdn-learn.adafruit.com/assets/assets/000/107/493/original/adafruit_products_Adafruit_QT_Py_ESP32-S2_Pinout.png?1640130293" width="800"/>

* https://learn.adafruit.com/assets/107493 (Pinout)
* https://learn.adafruit.com/adafruit-qt-py-esp32-s2/pinouts
* https://docs.espressif.com/projects/esp-idf/en/latest/esp32s2/_images/esp32-s2_saola1-pinout.jpg (esp32s2_saola)

#### Schematic
<img text="ESP32-S2 Schematic, (c) Adafruit" src="https://cdn-learn.adafruit.com/assets/assets/000/110/384/original/adafruit_products_QT_Py_rev_C_sch.png?1648589651" width="640"/>

* https://learn.adafruit.com/assets/110384 (Schematic)
* https://learn.adafruit.com/adafruit-qt-py-esp32-s2/downloads
* https://github.com/adafruit/Adafruit-QT-Py-ESP32-S2-PCB

#### Datasheets
* [ESP32-S2 Series Datasheet](https://www.espressif.com/sites/default/files/documentation/esp32-s2_datasheet_en.pdf)
* [ESP32-S2 Technical Reference Manual](https://www.espressif.com/sites/default/files/documentation/esp32-s2_technical_reference_manual_en.pdf)
* [ESP32-S2 WROVER Technical Reference Manual](https://www.espressif.com/sites/default/files/documentation/esp32-s2-wrover_esp32-s2-wrover-i_datasheet_en.pdf)
* https://docs.espressif.com/projects/esp-idf/en/latest/esp32s2/hw-reference/esp32s2/user-guide-saola-1-v1.2.html (esp32s2_saola)

#### Devicetree
- [boards/xtensa/esp32s2_saola/esp32s2_saola.dts](https://github.com/zephyrproject-rtos/zephyr/blob/main/boards/xtensa/esp32s2_saola/esp32s2_saola.dts)
- [dts/xtensa/espressif/esp32s2.dtsi](https://github.com/zephyrproject-rtos/zephyr/blob/main/dts/xtensa/espressif/esp32s2.dtsi)
- [boards/xtensa/esp32s2_saola/esp32s2_saola-pinctrl.dtsi](https://github.com/zephyrproject-rtos/zephyr/blob/main/boards/xtensa/esp32s2_saola/esp32s2_saola-pinctrl.dtsi)
- [boards/xtensa/esp32s2_saola/esp32s2_saola.yaml](https://github.com/zephyrproject-rtos/zephyr/blob/main/boards/xtensa/esp32s2_saola/esp32s2_saola.yaml)
- [boards/xtensa/esp32s2_saola/esp32s2_saola_defconfig](https://github.com/zephyrproject-rtos/zephyr/blob/main/boards/xtensa/esp32s2_saola/esp32s2_saola_defconfig)

#### Pinmux macros
- https://github.com/zephyrproject-rtos/hal_espressif/blob/zephyr/include/dt-bindings/pinctrl/esp32s2-pinctrl.h

#### ESP32-S2 auf MacOS
    $ pip3 install --upgrade esptool
    $ cd ~/Documents/Zephyr/zephyrproject
    $ west espressif update
    $ cd ~/Documents/Zephyr/zephyrproject/zephyr
    $ cat samples/basic/blinky/src/main.c
    $ west build -p auto -b esp32s2_saola samples/basic/blinky
    $ west flash

#### ESP32-S2 auf Linux
TODO

#### ESP32-S2 auf Windows
TODO

### ESP32-C3
#### Buy
https://www.adafruit.com/product/5405 (Adafruit QT Py ESP32-C3 WiFi Dev Board)

#### Board
https://docs.zephyrproject.org/latest/boards/riscv/esp32c3_devkitm/doc/index.html

#### Pinout
<img text="ESP32-C3 Pinout, (c) Adafruit" src="https://cdn-learn.adafruit.com/assets/assets/000/109/663/original/adafruit_products_image.png" width="640"/>

* https://learn.adafruit.com/assets/109663 (Pinout)
* https://learn.adafruit.com/adafruit-qt-py-esp32-c3-wifi-dev-board/pinouts

#### Schematic
<img text="ESP32-C3 Layout, (c) Adafruit" src="https://cdn-learn.adafruit.com/assets/assets/000/109/793/original/adafruit_products_QTC3_sch.png?1647545127" width="640"/>

* https://learn.adafruit.com/assets/109793 (Schematic)
* https://learn.adafruit.com/adafruit-qt-py-esp32-c3-wifi-dev-board/downloads
* https://github.com/adafruit/Adafruit-QT-Py-ESP32-C3-PCB

#### Datasheets
* [ESP32-C3 Series Datasheet](https://www.espressif.com/sites/default/files/documentation/esp32-c3_datasheet_en.pdf)
* [ESP32-C3 Technical Reference Manual](https://www.espressif.com/sites/default/files/documentation/esp32-c3_technical_reference_manual_en.pdf)

#### Devicetree
- [/boards/riscv/esp32c3_devkitm/esp32c3_devkitm.dts](https://github.com/zephyrproject-rtos/zephyr/blob/main/boards/riscv/esp32c3_devkitm/esp32c3_devkitm.dts)
- [/dts/riscv/espressif/esp32c3.dtsi](https://github.com/zephyrproject-rtos/zephyr/blob/main/dts/riscv/espressif/esp32c3.dtsi)
- [/boards/riscv/esp32c3_devkitm/esp32c3_devkitm-pinctrl.dtsi](https://github.com/zephyrproject-rtos/zephyr/blob/main/boards/riscv/esp32c3_devkitm/esp32c3_devkitm-pinctrl.dtsi)
- [/boards/riscv/esp32c3_devkitm/esp32c3_devkitm.yaml](https://github.com/zephyrproject-rtos/zephyr/blob/main/boards/riscv/esp32c3_devkitm/esp32c3_devkitm.yaml)
- [/boards/riscv/esp32c3_devkitm/esp32c3_devkitm_defconfig](https://github.com/zephyrproject-rtos/zephyr/blob/main/boards/riscv/esp32c3_devkitm/esp32c3_devkitm_defconfig)

#### Pinmux macros
- https://github.com/zephyrproject-rtos/hal_espressif/blob/zephyr/include/dt-bindings/pinctrl/esp32c3-pinctrl.h

#### ESP32-C3 auf MacOS
    $ west espressif update
    $ cat samples/hello_world/src/main.c
    $ west build -p auto -b esp32c3_devkitm samples/hello_world
    <press & hold reset, press user button, release user button, release reset>
    $ west flash
    $ west espressif monitor

TODO: https://forums.adafruit.com/viewtopic.php?f=8&t=191501&p=926488#p926488

#### ESP32-C3 auf Linux
TODO

#### ESP32-C3 auf Windows
TODO

### STM32F405
#### STM32F405 auf MacOS
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

#### STM32F405 auf Linux
TODO

#### STM32F405 auf Windows
TODO

## GPIO & Sensoren
### Blinky (Digital Output)
Siehe [samples/basic/blinky](https://github.com/zephyrproject-rtos/zephyr/tree/main/samples/basic/blinky)

### Button (Digital Input)
Siehe [samples/basic/button](https://github.com/zephyrproject-rtos/zephyr/tree/main/samples/basic/button)

### DHT11 Temperatur & Feuchtigkeit
Siehe [samples/sensor/dht](https://github.com/zephyrproject-rtos/zephyr/tree/main/samples/sensor/dht)

Und [samples/sensor/dht/boards/nrf52dk_nrf52832.overlay](https://github.com/zephyrproject-rtos/zephyr/blob/main/samples/sensor/dht/boards/nrf52dk_nrf52832.overlay)

### Weitere Sensoren
Siehe [samples/sensor](https://github.com/zephyrproject-rtos/zephyr/tree/main/samples/sensor)

## Threads & Mutex
TODO

## Message Queues
TODO

## Sockets & HTTP
* https://docs.zephyrproject.org/latest/connectivity/networking/net-stack-architecture.html
* https://docs.zephyrproject.org/latest/connectivity/networking/api/sockets.html
* https://github.com/zephyrproject-rtos/zephyr/tree/main/samples/net/sockets

* https://github.com/zephyrproject-rtos/zephyr/tree/main/samples/net/wifi
* https://github.com/zephyrproject-rtos/zephyr/blob/main/samples/net/sockets/http_get
* https://github.com/zephyrproject-rtos/zephyr/tree/main/samples/net/sockets/http_client
* https://github.com/zephyrproject-rtos/zephyr/tree/main/samples/net/sockets/dumb_http_server
* https://github.com/zephyrproject-rtos/zephyr/tree/main/samples/net/mqtt_publisher
* https://github.com/zephyrproject-rtos/zephyr/tree/main/samples/net/sockets/coap_client
* https://github.com/zephyrproject-rtos/zephyr/tree/main/samples/net/sockets/coap_server

* https://blog.golioth.io/zephyr-does-ethernet-too/
* https://blog.golioth.io/esp32-esp-at-enables-connectivity-on-any-zephyr-project/ (TODO)
* https://github.com/golioth/golioth-zephyr-sdk/tree/main/samples/hello#nrf52840-dk--esp32-wroom-32
* https://github.com/uLipe/zephyr-esp32-mqtt-demo

TODO

## Debugging
    $ west debug

* https://www.zephyrproject.org/zephyr-rtos-boards-configurations-hardware-interaction/ (Debugging)
* https://blog.golioth.io/debugging-zephyr-for-beginners-printk-and-the-logging-subsystem/
* https://docs.zephyrproject.org/latest/kernel/services/other/fatal.html (Runtime Assertions)
* https://www.irnas.eu/remote-zephyr-development-with-segger-tunnel-and-a-raspberry-pi/
* https://blog.golioth.io/debugging-zephyr-for-beginners-printk-and-the-logging-subsystem/

## Random
### Golioth Posts zu Zephyr
* https://blog.golioth.io/adding-an-out-of-tree-sensor-driver-to-zephyr/
* https://blog.golioth.io/category/zephyr/ (More)
### Nordic Fork von Zephyr
* https://github.com/nrfconnect/sdk-zephyr
* https://developer.nordicsemi.com/nRF_Connect_SDK/doc/latest/zephyr/index.html
* https://devzone.nordicsemi.com/f/nordic-q-a/77257/relationship-sdk-zephyr-and-zephyhrproject-zephyr
### Videos
* https://www.youtube.com/watch?v=4m0DPV6-GCs&list=PLzRQULb6-ipG39tVb-DEkIoSS5wQlbK6i&index=30 (Introduction to Zephyr)
* https://www.youtube.com/watch?v=HqDxohtaFUU&list=PLzRQULb6-ipG39tVb-DEkIoSS5wQlbK6i&index=16 (Using OPC-UA with Zephyr)
