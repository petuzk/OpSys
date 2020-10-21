#!/bin/bash

# Nie odczytuję wartości zmiennych środowiskowych, ponieważ
# domyślnie są one dostępne pod odpowiednimi nazwami. Przykład:
#   $ NUM_DAYS=5 ./4-find-and-tar.sh -m '*.c'
#   Nazwa archiwum: archiwum.tar

while getopts "n:m:a:" c
do
	case $c in
		n) NUM_DAYS=$OPTARG ;;
		m) FILENAME_MASK=$OPTARG ;;
		a) ARCH_FILENAME=$OPTARG ;;
	esac
done

[ -z $NUM_DAYS ] && echo -n "Liczba dni od momentu ostatniej modyfikacji: " && read NUM_DAYS
[ -z $FILENAME_MASK ] && echo -n "Maska nazw plików: " && read FILENAME_MASK
[ -z $ARCH_FILENAME ] && echo -n "Nazwa archiwum: " && read ARCH_FILENAME

test $NUM_DAYS -lt 0 2>/dev/null
case $? in
	0) echo "Podana liczba dni $NUM_DAYS jest mniejsza niż 0" && exit 1 ;;
	2) echo "Podana liczba dni '$NUM_DAYS' nie jest liczbą całkowitą" && exit 1 ;;
esac

find . -name "$FILENAME_MASK" -mtime "-$NUM_DAYS" | tar cvf "$ARCH_FILENAME" -T -
