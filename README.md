# LinCity-NG: A city simulation game

https://github.com/lincity-ng/lincity-ng

## Introduction
LinCity-NG is a city simulation game. It is a polished and improved
version of the classic LinCity game. In the game, you are required
to build and maintain a city. You can win the game either by
building a sustainable economy or by evacuating all citizens with
spaceships.

## Building and Installation

These are generic instructions, please see the wiki for more specific instructions

### Prerequisites

To build the game, you will need a C++ compiler (such as gcc) and CMake.

The game depends on some libraries to be present before you can build/run it.

If you use `vcpkg` (see the [Building](#building) section) dependencies are
automatically downloaded for you.

If you use packages from your distribution, pay attention that you need the
header files in addition to the libraries in order to build from source. They
are often in separate `*-dev` packages. E.g. for `physfs` you need `libphysfs`
and `libphysfs-dev`.

#### Run Dependencies

* SDL2 2.0.0 or later

  http://www.libsdl.org

* SDL2_mixer 2.0.0 or later (with ogg-support enabled)

  http://www.libsdl.org/projects/SDL_mixer/

* SDL2_image 2.0.0 or later (with png support)

  http://www.libsdl.org/projects/SDL_image/

* SDL2_ttf 2.0.12 or later

  http://www.libsdl.org/projects/SDL_ttf/

* SDL2_gfx 1.0.0 or later

  http://www.ferzkopp.net/~aschiffler/Software/SDL_gfx-2.0

* PhysicsFS 2.1.0 or later (use stable, not development branch)

  http://www.icculus.org/physfs/

* zlib 1.0 or later

  http://www.gzip.org/zlib/

* libxml 2.6.11 or later

  http://xmlsoft.org/

#### Build Dependencies

* LibXslt (with xsltproc)

  https://gitlab.gnome.org/GNOME/libxslt

* gettext

  https://www.gnu.org/software/gettext/

### Building

To configure the build:
```
$ cmake -B build
```
To use vcpkg to automatically manage dependencies, add
`-DCMAKE_TOOLCHAIN_FILE=<path to vcpkg>/scripts/buildsystems/vcpkg.cmake`
to the configure command, where `<path to vcpkg>` is the path to your vcpkg
installation.

To specify a different install prefix, add `--install-prefix <prefix>` to the
configure command.

To build the game:
```
$ cmake --build build --parallel
```

To install the game:
```
# cmake --install build
```
(Installing likely requires super-user privileges.)

To create a package (currently tar.gz and zip are generated):
```
$ cmake -B build -DCMAKE_BUILD_TYPE=Release
$ cmake --build build --parallel --target package
```

Run `cmake --help` to see all the available options.

### Running

To run the game without installing:
```
$ build/bin/lincity-ng
```

When the game is installed, you may run it with:
```
$ lincity-ng
```

From the main menu, you can quit the program by pressing ESC or ^C. This can be
useful to terminate the program even if the selected video mode is not working
properly.

## Gameplay

See the ingame help [F1] for more details.

### Objective

You can win Lincity-NG either by building a sustainable economy or
by evacuating all citizens with spaceships.

### Controls

#### Mouse

any click:
 * Click on Minimap shows the selected Area on mainscreen.

right click:
 * right click on mainscreen to show info on building under cursor.
<!-- * select tool from menu root -->
 * show help on tool

middle click:
 * pan map on mainscreen.

left click:
 * Perform action depending on selected tool. Bulldoze, show Information, construct building.
 * open Tool-Selection-Menus
 * select tool from menus

scroll wheel:
 * up: zoom in
 * down: zoom out

motion:
 * move cursor near the screen edge to scroll main screen


#### Keyboard

 * KP_PLUS: zoom in
 * KP_MINUS: zoom out
 * KP_ENTER: zoom 100%

 * KP5: center screen on map

 * KP9: scroll main screen north
 * KP1: scroll main screen south
 * KP7: scroll main screen west
 * KP3: scroll main screen east

 * KP2: scroll main screen SE
 * KP4: scroll main screen SW
 * KP6: scroll main screen NE
 * KP8: scroll main screen NW

 * arrow keys and WASD: more ways to scroll the main screen

 * SHIFT: scroll main screen faster


 * ESCAPE: switch to query tool
 * h: hide high buildings. Press h again to show them.
 * v: cycle through MiniMap-overlay modes
 * b: toggle between current tool and bulldoze mode
 * g: toggle between right click showing building or tile info
 * F1: Help

 * F12: quick save
 * F9:  quick load

 * \` (backtick): minimap outline
 * 1: minimap nourishments
 * 2: minimap unemployment
 * 3: minimap power
 * 4: minimap fire cover
 * 5: mimimap cricket cover
 * 6: minimap health cover
 * 7: minimap traffic
 * 8: minimap pollution
 * 9: minimap coal
 * 0: minimap commodity inventory

## Contact

Please report bugs and suggest features to
    https://github.com/lincity-ng/lincity-ng/issues.

Visit our homepage: https://github.com/lincity-ng/lincity-ng.
