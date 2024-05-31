# Pico Explorer Graphics Tester

This project is a quick demonstration of a few things I'm still learning.

First, as the title suggests, this project demonstrates how to use
[the pimoroni graphics library](https://github.com/pimoroni/pimoroni-pico/tree/main/libraries/pico_graphics) to display
information on [a Pi Pico](https://www.raspberrypi.com/documentation/microcontrollers/raspberry-pi-pico.html) mounted on
[a Pico Explorer Base](https://shop.pimoroni.com/products/pico-explorer-base) (which includes a 240x240 st7789 display).

Second, this is the first project I've set up that can be built and debugged from VS Code.  Kudos to Pimoroni for
providing [a boilerplate project](https://github.com/pimoroni/pico-boilerplate/tree/main) as a useful starting point.

## Prerequisites

First, you need the right hardware, i.e. a Raspberry Pi Pico and a Pico Explorer Base. It should not matter whether you
have a Pico that supports wireless or not.

You also need a working development environment. First, you need to set up the basics, i.e. the tools to compile code
and the libraries you need.  The
[setup guide for the Pico is what I used](https://github.com/pimoroni/pimoroni-pico/blob/main/setting-up-the-pico-sdk.md).

To set things up to work better with VS Code, I went through 
[this guide from Digikey](https://www.digikey.be/en/maker/projects/raspberry-pi-pico-and-rp2040-cc-part-2-debugging-with-vs-code/470abc7efb07432b82c95f6f67f184c0),
which helpfully covers the non-obvious bits required to get openocd working.

If you're interested, the [first part in the DigiKey series](https://www.digikey.be/en/maker/projects/raspberry-pi-pico-and-rp2040-cc-part-1-blink-and-vs-code/7102fb8bca95452e9df6150f39ae8422)
is a nice alternative to the Pico guide.

## Building and Installing

### VS Code and a Picoprobe

If you have a picoprobe, you should be able to use the debugger configuration in this project to build, install (and
debug) the code here.

First, you should check the paths in `.vscode/launch.json`and `.vscode/settings.json` and update them as
needed to match your system.  Then, you should be able to just hit the debugger icon and choose the configuration
defined in `.vscode/launch.json`.

### With Just the Command Line Tools

To build the application from the command line, you can use commands like the following, starting at the root the
repository:

```
mkdir build
cd build
cmake ..
make -j4
```

The last command assumes you have four cores, adjust as needed. Once the build completes, there are two ways to install
the application.

If you don't have a PiProbe, reboot your Pico while holding the "Bootsel" button, then drag the generated UF2 file
onto the USB drive that appears.

If you have a PiProbe, you can install the program without resetting your Pico using a command like:

```
sudo openocd -f interface/cmsis-dap.cfg -f target/rp2040.cfg -c "adapter speed 5000" -c "program pico-explorer-clock.elf verify reset exit"
```
