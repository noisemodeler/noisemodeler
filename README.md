# noise-terrain-gen

Tool for designing noise-based functions, though a flow-graph interface. Specialized for terrain generation.

## Folder structure

 * `nmlib` a C++ library, which allows creation, editing and evaluation of flow-graphs. Used `nmgui`.
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

1. Make sure you have all of the following dependencies installed:

 * Qt 5.2+
 * Qt-svg
 * QtQuick Controls
 * Boost
 * gcc with C++11 support
 * googletest (for unit tests)

2. Clone the repository.

    git clone --recursive git@github.com:acelster/noise-terrain-gen.git 

3. Create a build directory

    mkdir build-noise-terrain-gen
    cd build-noise-terrain-gen

4. Build

    qmake ../noise-terrain-gen
    make

5. Run

    nmgui/nmgui

