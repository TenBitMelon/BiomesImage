# BiomesImage

This is a small Program that uses the [cubiomes](http://github.com/Cubitect/cubiomes) library to generate a biome map around worldspawn for usage in other programs.

Precompiled Binaries are available under the [releases](http://github.com/melonboy10/BiomesImage/releases) page.

#### Usage

Simply call the executable with the seed as the first argument.
```
./generateMapPreview -1717765983328882033
```
The program then outputs the rgb values of each pixel of a 128x128 image of biomes centered around the worldspawn.

#### Compilation

To compile on Linux, run the following command in the root folder:
```
gcc src/main.c lib/libcubiomes.a -o generateMapPreview -fwrapv -lm -lpthread -Wall
```

On Windows, use MinGW-64. A MinGW-64 installer is located [here](http://mingw-w64.org/doku.php/download/mingw-builds). (Note: you need to have the MinGW-64 bin folder in your path temporarily or permanently before compiling)
Once you have MinGW-64 installed, you can use this command in the root folder to compile:
```
gcc src/main.c winlib/libcubiomes.a -o generateMapPreview -fwrapv -lm -lpthread -Wall -m64
```

On MacOS, download XCode, then run the following command in the root folder:
```
gcc src/main.c maclib/libcubiomes.a -o generateMapPreview -fwrapv -lm -lpthread -Wall
```
