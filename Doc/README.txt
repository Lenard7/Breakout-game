Links:

GIT:
https://docs.github.com/en/authentication/connecting-to-github-with-ssh/generating-a-new-ssh-key-and-adding-it-to-the-ssh-agent
https://docs.github.com/en/authentication/connecting-to-github-with-ssh/adding-a-new-ssh-key-to-your-github-account
https://docs.github.com/en/authentication/connecting-to-github-with-ssh
https://github.com/settings/keys


Example of game:
https://www.youtube.com/watch?v=QIs3UOTdsJM&t=46s


tinyXML:
https://www.youtube.com/watch?v=BuqHPQWRLvQ
https://github.com/leethomason/tinyxml2
https://www.codingpanel.com/a-complete-guide-to-tinyxml-using-cpp/


Simple DirectiveMedia Layer (SDL):
https://www.libsdl.org/
http://wiki.libsdl.org/wiki/index
https://www.youtube.com/watch?v=QM4WW8hcsPU&list=PLvv0ScY6vfd-p1gSnbQhY7vMe2rng0IL0&index=1
https://gigi.nullneuron.net/gigilabs/displaying-text-in-sdl2-with-sdl_ttf/

TODO:
- handle control of keyboard: decrease delay when any key is pressed
- use all variables inside class (load unique sound file (.wav file) and image (instead of making path inside program) for every type of brick
- make .xml files to have only brick types that are used inside each level
- implement throwing errors with commented THROW_FAILURE function
- test which libraries are not needed here
- variable LEVELNUM should be dynamic variable depending on number of "Level" files
- handle bug when ball stucks between Impenetrable brick and upper screen grid
- implement function that will check levelnum variable
- make display screen when level is loaded - on loading screen should be ordinal number of level - loading screen should be displayed for 3 seconds
- implement function for loading audio files
- move SDL_Init and SetupWindowSettings before main for loop, at the beginning of main function so window wont load when level is loaded
- SDL_OpenAudioDevice(NULL, 0, &wavSpec, NULL, 0) function after some time returns error, i.e 0
- display lives, score and level as multiline string
- in Level.cpp, instead hardcoded 4, there should be dynamic number, not const
- in HandleGraphics.cpp inside RelativePositionBallBrick function, checking boundaries should be implemented as unique function
- whole game lags when there are more bricks -> optimize drawing brciks and setting bricks (optimize those for loops used)