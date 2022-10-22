#!/bin/bash
if [ $# -lt 1 ]
then
    echo "Introduceti argumente"
else
    for a in $*; do
    if [ -f $a ] #verifica daca este fisier
    then
        echo "$a este fisier"
    elif [ -d $a ]
    then
        echo "$a este director"
    elif echo $a >> fisier | cat fisier | grep -E '^[0-9]*$'
    then
        echo "$a este un numar"
        rm fisier
    else
        echo "Nu stiu ce este $a"
    fi
done
fi
        
