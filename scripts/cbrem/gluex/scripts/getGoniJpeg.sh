#!/bin/sh
#grab the jpeg from the goni camera every second.
while [ 1 ]
do
    wget -O goni.jpg http://goni-cam/axis-cgi/jpg/image.cgi >& /dev/null & 
    sleep 1
done

