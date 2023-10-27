#!/bin/bash

PINS=(3 5 7 11 13 15 19 21 23 27 29 31 33 35 37 40 38 36 32 28 24 22 18 16 12)

for PIN in ${PINS[@]}; do
    mraa-gpio set $PIN out
done

while true; do
    for PIN in ${PINS[@]}; do
        mraa-gpio set $PIN 1
    done
    sleep 1
    for PIN in ${PINS[@]}; do
        mraa-gpio set $PIN 0
    done
    sleep 1
done
