#!/bin/bash
for i in $(seq -f "%02g" 1 32)
do
  make compile_module ID=$i
  sleep 2
done