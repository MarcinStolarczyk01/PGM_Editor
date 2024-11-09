# PGM Editor
## Disclaimer
_This project was developed in the very first months of my programming journey in 2021._
## Introduction
PGM_Editor is a simple, `.pgm` images editor. Images contain information about the picture's dimensions, greyscale, and pixels.
They can be loaded into a dynamic library, edited by a dedicated class called `Editor`, and saved under the user's name.
Files can contain comments that begin with the `#` and are deleted during loading.

I've made this to develop my bash and Git skills as it's my first one made by using these technologies.
My priority was security and high performance, so please contact me if you have found some bugs.
## Architecture
PGM_Editor includes 3 Classes:
- Repository - main class which is storage for pictures. It has permission to `Editor` and basic exception control. `Repository` has the `Menu()` method which has implemented Command Window Interface.
- Editor - after giving a pointer to the chosen Image it can change dimensions or rewrite pixels to make visual changes.
- Image - it has attributes describing the `.pgm` file like its name, dimensions, and a greyscale array of pixels.  
