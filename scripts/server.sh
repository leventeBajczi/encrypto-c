#!/bin/sh
#Bash script to start the server. To modify start values, modify the following values:
port=1111
log="log/"

mkdir $log
encrypto -m server -d $log -p $port