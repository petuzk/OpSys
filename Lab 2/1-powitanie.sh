#!/bin/bash
if [ `date +%u` -le 5 ]
then
	echo Witaj w dzien roboczy!
else
	echo Witaj w weekend!
fi
