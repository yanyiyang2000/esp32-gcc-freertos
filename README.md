# Prerequisites

## Installing Dependencies
See [Standard Toolchain Setup for Linux and macOS](https://docs.espressif.com/projects/esp-idf/en/release-v5.0/esp32s3/get-started/linux-macos-setup.html).

## Installing ESP-IDF
The following command installs ESP-IDF v5.0.

```shell
mkdir -p ~/esp
cd ~/esp
git clone -b release/v5.0 --recursive https://github.com/espressif/esp-idf.git
```

## Setting Up Tools
The following command sets up the tools used by ESP-IDF for ESP32-S2 and ESP32-S3.

```shell
cd ~/esp/esp-idf-5.0
./install.sh esp32s2, esp32s3
```

## Setting Up Environment Variables
```shell
. ~/esp/esp-idf/export.sh
```

# Configuring
The following command sets ESP32-S3 as the target for the project.

```shell
idf.py set-target esp32s3
```

> After this command, a header file called `sdkconfig.h` would be created in the `build` directory.

# Building
In the project root directory, use the following command:

```shell
idf.py build
```

# Flashing
In the project root directory, use the following command:

```shell
idf.py -p <PORT> flash
```

> `PORT` may be `/dev/ttyACM0` on Linux.

# Monitoring
In the project root directory, use the following command:

```shell
idf.py -p <PORT> monitor
```

> `PORT` may be `/dev/ttyACM0` on Linux.

# Cleaning
In the project root directory, use the following command:

```shell
idf.py fullclean
```

# Reference
- [Standard Toolchain Setup for Linux and macOS](https://docs.espressif.com/projects/esp-idf/en/release-v5.0/esp32s3/get-started/linux-macos-setup.html)