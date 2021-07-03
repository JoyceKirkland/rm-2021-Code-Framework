#!/bin/bash

# Get git submodules
git submodule update --init --recursive

# Enable pre-commit cpplint
chmod +x scripts/cpplint-pre-commit.sh
ln -sf $(pwd)/scripts/cpplint-pre-commit.sh .git/hooks/pre-commit

# Configure mindvision sdk usb connect rules
sudo ln -sf 3rdparty/mindvision/linux/88-mvusb.rules /etc/udev/rules.d/

# Update source
sudo apt update

# Install dependicies
cat dependencies.txt | xargs sudo apt install -y
