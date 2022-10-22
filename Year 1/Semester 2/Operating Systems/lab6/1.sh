#!/bin/bash

suma=0
if [ $# -eq 0 ]; then
    echo "Nu ati introdus niciun paramteru!"
else
    
    if [ -d $1 ]; then
        for f in $(find "$1" -type f);
        do
            
            sum=$(du $f | awk '{print $1}')
            suma=$((suma+sum))
        done
    fi
    echo $suma
fi
