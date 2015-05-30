# Noise Modeler

An in-game procedural terrain and content generation framework.

Noise Modeler is a tool for designing noise-based functions through a flow-graph interface. The GUI application specializes in designing noise-based procedural heightmap terrains, but can be used to model other content as well, such as terrain for 2D games. A high-resolution real-time preview of the terrain is updated instantly as the terrain is edited.

Generated terrain models can be stored as procedural models consuming only a few kB of storage. Through the nmlib library library, models can be expanded by a game engine during run-time.

## Author

Johan Klokkhammer Helsing (johanhelsing@gmail.com)

## Download

You can get the current development version from the git repository (https://github.com/noisemodeler/noisemodeler).

## Documentation

There are several places to find documentation about Noise Modeler:

 * [Project web site](http://www.noisemodeler.org)
 * [The Noise Modeler Library documentation](http://docs.noisemodeler.org)
 * [The Noise Modeler user's guide](http://www.noisemodeler.org/usersguide/noisemodeler-usersguide-0.1.5.pdf)
 * Master's thesis about Noise Modeler (will include link once it's available)
 * This readme (contains brief build instructions and project overview)
 * Commented example usage of the library may also be found in the `test_nmlib` and `nmcli` directories.

## Folder structure

 * `nmlib` a C++ library, which allows creation, editing and evaluation of flow-graphs. Used by `nmgui`.
 * `nmgui` a graphical flow-graph editor and terrain previewer.
 * `nmcli` a command line tool to generate GLSL functions from `nm.json` files.
 * `test_nmlib` unit tests for `nmlib`.
 * `test_nmgui` unit tests for `nmgui`.
 * `dependencies` header-only dependencies as git submodules.

## Dependencies

### nmlib

 * boost::signals2
 * c++11 (tested with gcc 4.8)
 * rapidjson (included as git submodule)

### nmgui

 * nmlib
 * boost::signals2
 * Qt 5.2+
   * qtquick
   * qtquick-controls
   * svg
 * c++11 (tested with gcc 4.8)

### Unit tests

 * googletest (only required for unit tests)

## Build instructions

This is a brief guide for experienced developers. In-depth build instructions from Windows, Ubuntu 14.04+ and Arch Linux can be found in the user's guide.

First, make sure you have all of the following dependencies installed:

 * Qt 5.2+ (including base, declarative, qtquick-controls and svg modules)
 * Boost
 * gcc with C++11 support
 * googletest (if building unit tests)

```bash
# 1. Clone the repository.
git clone --recursive git@github.com:acelster/noise-terrain-gen.git 

# 2. Create a build directory
mkdir build-noisemodeler
cd build-noisemodeler

# 3. Build
qmake ../noisemodeler
make

# 4a. Run
nmgui/nmgui

# 4b. Install and run (unix only, this will install noisemodeler in /usr/)
sudo make install
nmgui
```

## Contribute

Noise Modeler is an open source project and needs your help growing and improving. Don't hesitate to contact us with suggestions or bug reports (https://github.com/noisemodeler/noisemodeler/issues).

If you have made any improvements, we will happily accept any pull requests submitted through GitHub.

Even if you are perfectly happy with the project and don't have any issues with it, we would appreciate to hear about it.

## License

Noise Modeler is released under the zlib license, see LICENSE.md for more information.
