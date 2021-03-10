#!/bin/sh

nitrogen --restore & # wallpaper restored
picom --experimental-backends --xrender-sync-fence & # compositor
/home/ankit/dwm-bar/dwm_bar.sh & #dwm bar
volumeicon & #volumeicon

