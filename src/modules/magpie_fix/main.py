#!/usr/bin/env python3
# -*- coding: utf-8 -*-
#

import libcalamares.utils


def run():
    """ Calls routine to create kernel initramfs image.

    :return:
    """
    try:
    	# Fixing Permission
        libcalamares.utils.check_target_env_call(["chown", "root:root", "/"])
        libcalamares.utils.check_target_env_call(["chmod", "755", "/"])
        # # Removing Calamares
        # libcalamares.utils.check_target_env_call(["pacman", "-R", "calamares", "--noconfirm"])
    except:
        pass  # doing nothing on exception

    return None
