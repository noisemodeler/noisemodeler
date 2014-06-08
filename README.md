# Noise Modeler

Tool for designing noise-based functions, though a flow-graph interface. Specialized for heightmap terrain generation.

Generated terrain models can be stored as a procedural models consuming only a few kB of storage. Through the library a model can be  expanded by a game engine during run-time.

## Folder structure

 * `nmlib` a C++ library, which allows creation, editing and evaluation of flow-graphs. Used by `nmgui`.
 * `nmgui` a graphical flow-graph editor and terrain previewer.
 * `test_nmlib` unit tests for `nmlib`.
 * `test_nmgui` unit tests for `nmgui`.
 * `dependencies` header-only dependencies as git submodules.

## Dependencies

### nmlib

 * boost::signals2
 * c++11 (tested with gcc 4.8)
 * rapidjson

### nmgui

 * boost::signals2
 * Qt 5.2+
   * qtquick
   * qtquick-controls
   * svg
 * c++11 (tested with gcc 4.8)
 * rapidjson

### Unit tests

 * googletest (only required for unit tests)


## Building

First, make sure you have all of the following dependencies installed:

 * Qt 5.2+
 * Qt-svg
 * QtQuick Controls
 * Boost
 * gcc with C++11 support
 * googletest (for unit tests)

```bash
# Clone the repository.
git clone --recursive git@github.com:acelster/noise-terrain-gen.git 

# Create a build directory
mkdir build-noise-terrain-gen
cd build-noise-terrain-gen

# Build
qmake ../noise-terrain-gen
make

# Run
nmgui/nmgui
```

