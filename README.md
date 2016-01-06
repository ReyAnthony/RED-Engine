# RED-Engine
C++ Game Engine based on Allegro5 and java map editor
Currently I tested and got it to work on : 
- OSX
- Trisquel GNU/Linux (Debian / Ubuntu based)

I'm looking for people to : 
- Create unit tests and do tests in general (and report bugs in the tracker)
- Ehance the graphics 
- Tidy up the C++ code 
- Write an engine to manage translated strings (we could use a .hpp file tho and #if's)
- Test the game on other OSes and different configurations 

<b> NOTE : All source code is licenced under GPLv3.
All tiles but hilda.png are from David E. Gervais
and are released under CC-BY 3.0.
Hilda.png is from me and is licenced
under CC BY-NC-ND. </b>

Other copyrights :
<b>
<br>
"The isle"
<br>
"Curious Wanderer"
<br>
"One of Many"
<br>
by Jasmine Cooper
<br>
www.jasminecoopermusic.net
<br><br>
prince_valiant.tff
<br>
from Dieter Steffman
<br>
http://www.steffmann.de/
<br>
</b>

THe engine folders contains the engine and the .hpp files to be used by a game using this engine. 
Please build using the bash files (make.sh and make_lib.sh), the CMake file don't work and is just here to contempt CLion.
I need to make a real makefile, but I'm not good at it, any help is welcome. 

Tested compiling and working on OSX 10.10.14. 

Current state (Things I will likely do in short time)

- Need to do the int tests (lots of things not checked so lots of hidden bugs) 
- Ehance the laggy camera movement (and hide allegro references from the game part)
- Create a makefile ...

+![alt tag](http://anthonyrey.fr/wp-content/uploads/2015/12/Capture-d%E2%80%99e%CC%81cran-2015-12-29-a%CC%80-01.22.38.png)

The map editor is not finished (no export functions for the moment, but will come in a short time)

+![alt tag](http://anthonyrey.fr/wp-content/uploads/2015/12/Capture-d%E2%80%99e%CC%81cran-2016-01-02-a%CC%80-23.49.54.png)
