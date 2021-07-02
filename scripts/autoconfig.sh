#!/bin/bash

# Get git submodules
git submodule update --init --recursive

# Configure mindvision sdk usb connect rules
sudo cp 3rdparty/mindvision/linux/88-mvusb.rules /etc/udev/rules.d/

# Update source
sudo apt update

# Install dependicies
cat dependencies.txt | xargs sudo apt install -y
