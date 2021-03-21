# White Noise Generator
A program, with which you can generate white-noise in a window and set the probability at which noise should appear and the rate at which the noise should be changed (so: framerate and generations).


# Build
## Prerequisites
If you want to build this project you need to have some dependencies installed:
- (_Qt_)[https://www.qt.io/]
- _make_
- (SDL2)[https://www.libsdl.org/]

## Compiling
### GUI
1. Open the `white-noise-generator.pro` file in the `src/` folder within QtCreator.
2. Then build the project (it's recommended, to build into a `build` folder on the same level as the `src` folder).

### Console
Make sure `qmake` and `make` are installed and in your path.

Run following:
```
git clone https://github.com/mobergmann/white-noise-generator.git
cd white-noise-generator/
mkdir build
cd build/
qmake -makefile -recursive src/white-noise-generator.pro
make
```
This will clone the repo, create a folder called _build_, and compile the project in that folder.


# Using the Application
If you build the Project yourself, then you can proceed to _Selfbuild_.

## Launching

### Release
1. Prerequisites
  1. Make sure (_Qt_)[https://www.qt.io/] is installed on your system and part of your Path
  2. Make sure (SDL2)[https://www.libsdl.org/] is installed on your system and part of your Path
2. Download the Release
3. Extract the Release
4. (Linux:) Make the extracted file executable: `chmod u+x`
5. Execute the program

### Selfbuild
1. Download the Release
2. Extract the Release
3. (Linux:) Make the extracted file executable: `chmod u+x`
4. Execute the program

## Usage
Each input has a tooltip, which shows up if you hover over it.

The Rates are in Update/ Generation _per millisecond_. To get a good conversion you may have to grab a calculator and convert _per second_ into _per millisecond_.
```
x = desired fps => form input = 1 / x * 1000
```

When you press _Start_, then a Window will appear and show the White Noise as a stream/ video.
To stop the Video press the _Stop_ button.

You can pause the video by pressing the _Pause_ button and continue by pressing the _Play_ button.

If you set the _Frame Rate_ to low (or rather too high), then the window may seem to be bugged, but this is normal because no updates to the frame are made. 30 fps would be ~33 and 60 fps would be ~17.

A Generation value too high may be challenging for your pc.

<img src="https://i.imgur.com/3vXiH1O.png"/>
