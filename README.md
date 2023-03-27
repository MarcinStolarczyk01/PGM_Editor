PGM_Editor is a simple, .pgm images editor. Images contains information about picture's dimensions, it's grey scale and pixels.
They can be loaded into dynamic library, edited by deditated class called 'Editor' and saved under users name.
Files can contain comments which begins with '#' sign and are deleted during loading.

I've made this to develop my bash and Git skills as it's my first one made by using these technologies.
My priority was security and high performence so if have found some bugs please notact me.
PGM_Editor includes 3 Classes(UML diagram will be uploaded soon)
* Repository
  Main class which is storage for pictures. It has permission to Editor and basic exception controll. Repository has 'Menu' method which has implemented CUI.
* Editor
  Name says it all - it contains methods like Reverse, 
*Image
  It has attributes describing .pgm file like it's name, dimensions, grey scale array of pixels.  


Future Features:
- comments to every function
- ability to load and edit not only PGM files
- file types converter 
