#!/bin/bash

find -name "*.cpp" -o -name "*.h" -o -name "*.txt" -o -name "*.sh" -exec sed -i "s/\t/    /g" "{}" \;
DIR="$(pwd)"
DIRNAME="${DIR##*/}"
cd ..
if [ -f "$DIRNAME.zip" ]; then
    rm "$DIRNAME.zip"
fi
zip -r -9 "$DIRNAME.zip" "$DIRNAME" 
