# SkyHub SDK v2.9.0

[![Build Status](https://github.com/ugcs/skyhub-sdk/workflows/Build/badge.svg)](https://github.com/ugcs/skyhub-sdk/actions?query=workflow%3ABuild)
[![Publish Status](https://github.com/ugcs/skyhub-sdk/workflows/Publish/badge.svg)](https://github.com/ugcs/skyhub-sdk/actions?query=workflow%3APublish)

The SkyHub SDK allows to extend SkyHub solution capabilities by adding custom payloads.

The SDK consists of source code required to add a custom payload plugin to the SkyHub firmware as well as instructions how to do it.

# Prerequisites

* Latest UgCS v3: https://www.ugcs.com/download
* Latest UgCS-CPM v3: https://industrial.ugcs.com/dl/s/ugcs-cpm-windows
* SkyHub firmware v2.9.0: https://industrial.ugcs.com/dl/release/skyhub-armhf-2.9.0.1562.tar.gz
* Host PC with Ubuntu OS (Ubuntu 20.04 is recommended) or Windows Subsystem for Linux (WSL) with pre-installed Docker software

# Building

Run in Ubuntu (note that `sudo` access will be requested to run Docker commands by default):

    make prepare
    make

Find `libpayload-example.so` file in a `build-arm` directory.

# Using

* Download SkyHub firmware in `.tar.gz` format
* Unpack it and copy the `libpayload-example.so` file to `usr/local/lib/plugins/payloads` directory inside the SkyHub firmware directory.
* Pack the firmware back and update the SkyHub device using UgCS-CPM.
* Check for data in UgCS-CPM Payload Example widget.

# Getting Help

* SkyHub user manual: https://industrial.ugcs.com/dl/s/skyhub-user-manual
* support@ugcs.com

# Reporting Bugs

Please refer to the [Issues](https://github.com/ugcs/skyhub-sdk/issues) section, try to find a similar report, and feel free to add your own if no any resembling issue found.

# License

Source code is licensed under the [3-Clause BSD License](LICENSE).
