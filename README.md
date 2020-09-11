# Ray
2D Platformer made with [TimGameLib](https://github.com/sizlo/TimGameLib)

Complete levels in total darkness with only a torch to guide your way

## Building
### Mac
1. Download cmake
    
    `brew install cmake`

2. Download SFML 2.3.2

3. Copy SFML frameworks to `/Library/Frameworks`
    
    `sudo cp -r /path/to/SFML/Frameworks/* /Library/Frameworks`
    
    `sudo cp -r /path/to/SFML/extlibs/* /Library/Frameworks`

4. Download [TimGameLib](https://github.com/sizlo/TimGameLib)

5. Expose TimGameLib location
    
    `export TIM_GAME_LIB_ROOT="/path/to/TimGameLib"`

6. Disable Gatekeeper (optional, but you will have to deal with loads of popups and restarting the first time you launch)
    
    `sudo spctl --master-disable`

7. Generate build files

    `cmake .`

8. Build
    
    `cmake --build .`

Note: Although the frameworks do get bundled into the app, the game does not load them from there, but from `/Library/Frameworks` instead. So the app bundle is not portable.