#!/bin/bash
# Script to mount network drive

echo "Mounting drive...."
sudo mount -t cifs -o username=dferguson,password=dougf1! //192.168.255.3/"ABT Server"/"Project Management"/DSC_aging_study /mnt/temp_humidity_data

