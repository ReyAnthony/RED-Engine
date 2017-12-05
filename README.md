#Some code found lying somewhere on my hard drive .. Some patterns might be a bit useful to study like MapFactory .. Otherwize it's pretty much shit :) 

Old description (For reference ! )

# RED-Engine
C++ Game Engine based on Allegro5 and java map editor.

Currently I tested and got it to work on : 
- OSX
- Trisquel GNU/Linux (Debian / Ubuntu based)
- Windows 7 (via mingw)

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
under CC BY-NC-ND. More details in main.cpp</b>

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

Current state (Things I will likely do in short time)

- Need to do the int tests (lots of things not checked so lots of hidden bugs) 
- Ehance the laggy camera movement (and hide allegro references from the game part)
- Create a makefile ...

+![alt tag](http://anthonyrey.fr/wp-content/uploads/2016/01/Capture-d%E2%80%99e%CC%81cran-2016-01-08-a%CC%80-02.47.25-1024x594.png)

The map editor is not finished (no export functions for the moment, but will come in a short time)

+![alt tag](http://anthonyrey.fr/wp-content/uploads/2015/12/Capture-d%E2%80%99e%CC%81cran-2016-01-02-a%CC%80-23.49.54.png)
