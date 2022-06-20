#! /bin/sh
# This is used to install the linux app and it's dependencies.
# Currently not building SDL from source for linux due to cmake errors.
# The version of SDL from apt is old, so lets grab a newer one.
sudo add-apt-repository ppa:savoury1/multimedia -y
sudo apt install libsdl2-dev libsdl2-image-dev libsdl2-ttf-dev -y
sudo add-apt-repository ppa:savoury1/multimedia -y --remove