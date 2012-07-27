#!/bin/sh
i=1
while [ $i -le 500 ]
do
  ./RandomContraction
  ((i=$i+1))
done
