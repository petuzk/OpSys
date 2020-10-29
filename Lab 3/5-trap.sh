#!/bin/bash

# Ten skrypt sprawdza użycie polecenia trap

function sighandler {
    echo "Signal $1 received"
}

for (( i = 1; i < 16; i++ )); do
	trap "sighandler $i" $i
done

echo "PID: $$"
echo "Waiting for signals..."

while :
do
	sleep 0.1
done
