#!/bin/bash

odd_out="blah_odd.txt"
even_out="blah_even.txt"

nums_get() 
{
    grep -oE '[+-]?[0-9]+(\.[0-9]+)?(e[-+]?[0-9]+)?' | tr '\n' ' '
    echo ""
}

sizes_even="1000 1100"
sizes_odd=""

> $even_out
> $odd_out

for size in $sizes_even; do
    touch $even_out
    echo -n "$size: " >> $even_out
    echo "$size" | python3 data/gen.py > data/"$size".txt
    ./lab_01 < data/"$size".txt | nums_get >> $even_out
done

for size in $sizes_odd; do
    touch $odd_out
    echo -n "$size: " >> $odd_out
    echo "$size" | python3 data/gen.py > data/"$size".txt
    ./lab_01 < data/"$size".txt | nums_get >> $odd_out
done
