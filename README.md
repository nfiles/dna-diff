# dna-diff
Find the differences in two DNA sequences

### About
I created the first version of this project for a friend in 2013. The current iteration does not really do any more than the original, but has been a sandbox for refactoring and learning some new things about Sublime Text and MinGW.

## Setup
### Windows
The Sublime Text build action has been configured using [MinGW](http://mingw.org/). Installing MinGW will provide you with the MinGW Installation Manager. Using this tool, install the following packages:

 - mingw32-base (make)
 - mingw32-gcc-g++ (g++)
 - msys-base ("rm" and other tools so the Linux makefile will work)

### Linux
requires make and the gcc compiler collection, but has not been tested and is probably broken.

If you would prefer to write your own makefile/build/compilation scripts, go right ahead. :)
