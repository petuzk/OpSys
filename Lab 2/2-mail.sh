#!/bin/bash

# Wymagane pliki w bieżącym katalogu:
#   * adresy.txt -- zawiera listę adresatów
#   * tresc.txt  -- zawiera treść wiadomości (body)
#   * spec*.pdf  -- pliki specyfikacji

if [ ! -f adresy.txt ]; then echo "Nie znaleziono pliku 'adresy.txt'"; exit 1; fi
if [ ! -f tresc.txt ];  then echo "Nie znaleziono pliku 'tresc.txt'"; exit 2; fi
if [ ! -f spec*.pdf ];  then echo "Nie znaleziono żadnego pliku specyfikacji"; exit 3; fi

for adresat in $(cat adresy.txt)
do
	echo "Wysyłam zapytanie do $adresat"
	mutt -i tresc.txt -s "Zapytanie ofertowe" -a spec*.pdf -- $adresat
done
