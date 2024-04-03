#!/bin/bash

for i in {1..1000}
do
   ./client bob$i &
   sleep 0.2
   echo $i
done