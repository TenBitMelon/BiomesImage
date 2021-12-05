# BiomesImage

This is a small Program that uses the [cubiomes](http://github.com/Cubitect/cubiomes) library to generate a biome map around worldspawn for usage in other programs.

Precompiled Binaries are available under the [releases](http://github.com/melonboy10/BiomesImage/releases) page.

#### Usage

Simply call the executable with the seed as the first argument.
```
./generateMapPreview -1717765983328882033
```
To generate with large biomes, include the `--largeBiomes` flag.
```
./generateMapPreview -1717765983328882033 --largeBiomes
```
The program then outputs the rgb values of each pixel of a 128x128 image of biomes centered around the worldspawn.

#### Compilation

To compile, do the following:
```
git clone --recursive https://github.com/melonboy10/BiomesImage.git
make
```
Note: MinGW-64 is necessary to compile on Windows. Additionally, you must run `mingw32-make` instead of `make` on Windows. A MinGW-64 installer is located [here](http://mingw-w64.org/doku.php/download/mingw-builds). (Note: you need to have the MinGW-64 bin folder in your path temporarily or permanently before compiling)

Note: XCode must be installed to compile on MacOS
