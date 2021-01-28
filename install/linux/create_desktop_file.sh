#!/bin/bash
# create progname.desktop
#param 1 is progname
#param 2 is where progname will be installed

rm -fv $1.desktop

echo >> $1.desktop "[Desktop Entry]"
echo >> $1.desktop "Encoding=UTF-8"
echo >> $1.desktop "Version=3.0"
echo >> $1.desktop "Name=$1"
echo >> $1.desktop "Comment=Creating Doxygen compatible comment"
echo >> $1.desktop "Exec=$2/$1"
echo >> $1.desktop "Icon=$1.png"
echo >> $1.desktop "Terminal=false"
echo >> $1.desktop "Type=Application"
echo >> $1.desktop "Categories=Development;Application"
echo >> $1.desktop "Name[en_US]=$1"


