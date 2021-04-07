# dwm
 My build of dwm (dynamic window manager from suckless)
 ## How to use?
 Clone the repo and cd into it and run "sudo make clean install".
 (note: this requires the JetBrains font which can be downloaded using "sudo pacman -S ttf-jetbrains-mono" on arch)
 ## Keybindings:
 Check out the keybindings.txt file.
 ## Screenshots:
 ### Desktop
 ![Screenshots](https://github.com/ankitjosh78/dwm/blob/main/screenshots/rice.png?raw=true)
 ### Vim
 ![Screenshots](https://github.com/ankitjosh78/dwm/blob/main/screenshots/vim.png?raw=true)
 ### Master and Stack Layout:
 ![Screenshots](https://github.com/ankitjosh78/dwm/blob/main/screenshots/master_stack.png?raw=true)
 
 ## NOTE:
 #### In this build I'm changing all my colors on the fly with [pywal](https://github.com/dylanaraps/pywal)
 #### To get it working just install pywal.
 #### For arch, install it from the AUR: "paru -S python-pywal" , I use the paru AUR helper.
 #### Then generate a colorscheme using pywal (eg: wal -i "path\ to\ wallpapers\ directory\")
 #### Now open the 'config.h' in dwm folder and change the username in the 26th line from "ankit" to yourUserName.
 #### Now you can build it and it should be perfectly ready for you. When changing wallpapers go to the dwm folder and build it again (sudo make install)

 
 
