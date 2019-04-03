#!/bin/bash

port=2000
input="user toto
user Anonymous
quit"

make re -s
./myftp $port &
pid=$!

echo "$input" | nc 127.0.0.1 $port -w 5
kill $pid
