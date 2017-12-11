#!/bin/sh
#Bash script to start the client. To modify start values, modify the following values:
port=1111
keyfiles="keys/"
interface=gui
server=127.0.0.1

mkdir $keyfiles
encrypto -k $keyfiles -p $port -c $interface -s $server