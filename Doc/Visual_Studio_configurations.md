# Project configurations

## Header files
- If the header is not in the project directory (.h file), you must use a relative path in #include command in code, e.g.
#include "..\..\SomeOtherDir\myheader.hpp"

- Another solution may be to add ..\..\SomeOtherDir (Note "PATH", not file name or extension.) to the
C++ -> General -> Additional Include Directories
properties for the project. In this case,
when writing #include inside code, there is no need to 
write relative or absolute path, just name of header file

- for this project, for both Debug and Release, use these paths:
1. $(ProjectDir)
2. $(ProjectDir)..\..\Third_party\tinXML files\Include
3. $(ProjectDir)..\..\Third_party\SDL2-devel-2.0.18-VC\SDL2-2.0.18\include

## Libraries (.dll files and folders)
- go to:
Configuration Properties->Linker->General->Additional Library Directories
and set the *path* for the .lib files

- for this project, for both Debug and Release, use these paths:
1. $(ProjectDir)..\..\Third_party\SDL2-devel-2.0.18-VC\SDL2-2.0.18\lib\x64
2. $(ProjectDir)
3. $(ProjectDir)..\..\Third_party\tinXML files\Source
4. $(ProjectDir)..\..\Third_party\tinXML files\Include

- go to:
Configuration Properties->Linker->Input->Additional Dependencies
and set the .lib *file name*

- for this project, for both Debug and Release, use these paths:
1. SDL2.lib
2. SDL2main.lib
3. SDL2_ttf.lib
4. SDL2_image.lib

- Header files don't get "added" automatically. They become part of a build via #include statements.

# ERROR LIST
- Error 0xc00007b “Application was unable to start correctly”
    - FIX: this error occurs if something is wrong with .dll files, e.g. if path to .dll files is wrong setup, or .dll file is corrupted or for different platform (x64 and not for x86)

- Error "This application has failed to start because xxx.dll was not found."
    - FIX:
        1. Go to project properties (Alt+F7)
        2. Under "Debugging" card, look to the right
        3. There's an Environment field.
        4. Add your relative path there (relative to vcproj folder) i.e. ..\some-framework\lib by appending PATH=%PATH%;$(ProjectDir)\some-framework\lib or prepending to the path PATH=C:\some-framework\lib;%PATH%
        5. Hit F5 (debug) again and it should work.
    - configuring "Debugging" card, inside Visual Studio, Project is able to run inside IDE without putting .dll files inside folder where .exe file is