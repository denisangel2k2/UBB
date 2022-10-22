#!/bin/bash
gasit=0
declare -A cuvinte
declare -A frecventa
index=0
nrarg=$#
while [ ! $# -eq 0 ]; do
    cuvant=$1
    cuvinte[$index]=$cuvant
    echo ${cuvinte[$index]}
    index=$((index+1))
    shift
done
conditie=1
gasit=0
while [ $conditie -eq 1 ]; do
    read -p "Nume fisier: " fisier
    i=0
    if [ -f $fisier  ]; then

        while [ ! $i -eq $nrarg ]; do
            if grep -E -q "${cuvinte[$i]}" $fisier; then
                frecventa[$i]=1
            fi  
            i=$((i+1))
        done
        i2=0
        gasit=0
        while [ ! $i2 -eq $nrarg ]; do
            if [ "${frecventa[$i2]}" = "1" ]; then
                gasit=$((gasit+1))
            fi
            i2=$((i2+1))
        done
        if test $gasit -eq $nrarg; then
            conditie=0
        fi
    fi
done




