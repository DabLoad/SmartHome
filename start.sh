#!/bin/bash
echo "\e[31mSTARTED\e[0m"
sudo mount -t tmpfs -o size=64M tmpfs /home/caricardo/tmpfs

sudo mount -t tmpfs -o size=128M tmpfs /home/caricardo/SmartHome
sudo mkdir /home/caricardo/SmartHome/tmpfs -m 0775 -p
sudo mount -t tmpfs -o size=64M tmpfs /home/caricardo/SmartHome/tmpfs

sudo mkdir /var/log/apache2 -m 0775 -p
sudo mkdir /var/log/apa -m 0775 -p
sudo service apache2 restart
exit 0
