#!/bin/sh

picom --experimental-backends --xrender-sync-fence & # compositor
#.~/.config/polybar/launch.sh &
/usr/bin/dunst & # dunst
/home/ankit/.local/share/dwm-bar/dwm_bar.sh & #dwm bar
wal -R # wallpaper restorer


