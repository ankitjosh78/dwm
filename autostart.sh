#!/bin/sh

nitrogen --restore & # wallpaper restored
picom --experimental-backends --xrender-sync-fence & # compositor
#.~/.config/polybar/launch.sh &
/usr/bin/dunst & # dunst
/home/ankit/dwm-bar/dwm_bar.sh & #dwm bar


