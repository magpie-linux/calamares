### Calamares: MagpieOS Installer
---------

### Dependencies

Main:
* Compiler with C++11 support: GCC >= 4.9.0 or Clang >= 3.5.1
* CMake >= 3.2
* Qt >= 5.7
* yaml-cpp >= 0.5.1
* Python >= 3.3 (required for some modules)
* Boost.Python >= 1.55.0 (recommended, or PythonQt; one is required for some modules)
* PythonQt (recommended, or Boost.Python; one is required for some modules)
* extra-cmake-modules >= 5.18 (recommended; required for some modules)

Modules:
* welcome:
  * NetworkManager
  * UPower (optional, runtime)
* partition:
  * extra-cmake-modules
  * KF5: KCoreAddons, KConfig, KI18n, KService, KWidgetsAddons
  * KPMcore >= 3.3
* bootloader:
  * systemd-boot or GRUB
* unpackfs:
  * squashfs-tools
  * rsync

### Building

See [wiki](https://github.com/calamares/calamares/wiki) for up to date
[building](https://github.com/calamares/calamares/wiki/Develop-Guide)
and [deployment](https://github.com/calamares/calamares/wiki/Deploy-Guide)
instructions.
