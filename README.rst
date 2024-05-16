Kerbal Simpit Arduino library
==============================

This is an Arduino_ library and example sketches for building hardware
intended to interface with `Kerbal Space Program`_ via the `Kerbal
Simpit Revamp`_ plugin.

Refer to the `full documentation`_ for getting started and API information.

.. _Arduino: https://www.arduino.cc/
.. _Kerbal Space Program: https://kerbalspaceprogram.com/
.. _Kerbal Simpit Revamp: https://github.com/Simpit-team
.. _full documentation: https://kerbalsimpitrevamped-arduino.readthedocs.io

### Local Debugging

When cloning be sure to also pull all submodules. git submodule update --init --recursive

To build the sketch I recommend ditching Arduino IDE and using some other editor. Im personally using Visual Studio Code with the [Arduino](https://marketplace.visualstudio.com/items?itemName=vsciot-vscode.vscode-arduino) extension.
If using the VS Code extension above, be sure to press F1 => Search for "Arduino" => Select relevent options to configure your board config, board type, serial port, ect.
This will create a new file at `.vscode/arduino.json` you can easily edit as needed later, as well as `c_cpp_properties.json`

Ensure the following exist within `configurations.includePath` in `.vscode/c_pp_properties.json`
```
    "${workspaceFolder}/libraries/AUnit/src",
    "${workspaceFolder}/libraries/MemStream",
    "${workspaceFolder}/src",
```
