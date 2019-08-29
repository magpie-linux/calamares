#!/usr/bin/env python3
# -*- coding: utf-8 -*-
#

import os
import subprocess

import libcalamares
from libcalamares.utils import *


def run():
    """ Calls routine to create kernel initramfs image.

    :return:
    """
    root_mount_point = libcalamares.globalstorage.value("rootMountPoint")
    try:
        subprocess.check_call(
            ["cp", "/run/archiso/bootmnt/arch/boot/x86_64/vmlinuz", root_mount_point + "/boot/vmlinuz-linux"])
    except Exception as e:
        print(e)  # printing exception
    try:
        subprocess.check_call(
            ["cp", "/run/archiso/bootmnt/arch/boot/x86_64/vmlinuz-lts", root_mount_point + "/boot/vmlinuz-linux-lts"])
    except Exception as e:
        print(e)  # printing exception

    try:
        os.system("lspci > vbox.txt")
    except Exception as e:
        print(e)  # printing exception

    if 'VirtualBox' not in open('vbox.txt').read():
        try:
            subprocess.check_call(
                ["pacman", "-Rns", "virtualbox-guest-utils", "virtualbox-guest-modules-arch", "--noconfirm", "--root",
                 root_mount_point])
        except Exception as e:
            print(e)  # printing exception

    return None
