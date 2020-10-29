#!/bin/bash -e

# Ten skrypt wysyła procesowi o podanym PID podstawowe sygnały (1-15),
# przy czym sygnał 9 (SIGKILL) w ostatniej kolejności

if [[ ! $1 ]]; then
	echo "usage: $0 test_pid"
	exit 1
fi

if ! ps $1 >/dev/null ; then
	echo "no process with pid $1"
	exit 2
fi

for (( i = 1; i < 9; i++ )); do
	echo "Sending kill -s $i to PID $1"
	kill -s $i $1
	sleep 0.5
done

for (( i = 10; i < 16; i++ )); do
	echo "Sending kill -s $i to PID $1"
	kill -s $i $1
	sleep 0.5
done

echo "Sending kill -s 9 to PID $1"
kill -s 9 $1
