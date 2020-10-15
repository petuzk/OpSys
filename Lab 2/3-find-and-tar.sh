#!/bin/bash
find . -name "$1" -mtime "-$2" | tar cvf "$3" -T -
