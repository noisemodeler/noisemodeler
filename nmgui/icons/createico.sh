#!/bin/bash
mkdir temp
declare -a res=(16 24 32 48 64 128 256)
for f in $@; do
    for r in "${res[@]}"; do
        inkscape -z -e temp/${f}${r}.png -w $r -h $r $f
    done 
    resm=( "${res[@]/#/temp/$f}" )
    resm=( "${resm[@]/%/.png}" )
    convert -bordercolor transparent -border 0 "${resm[@]}" ${f%%.*}.ico
done
rm -rf temp
