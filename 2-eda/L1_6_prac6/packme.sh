#!/bin/bash

# Borrar ejecutables de Linux
find ! -name "*.*" ! -name "Makefile" -exec rm "{}" \;

# Borrar ejecutables de Windows
find -iname "*.exe" -exec rm "{}" \;

# Borrar objetos intermedios
find -iname "*.so" -o -iname "*.o" -o -iname "*.a" -exec rm "{}" \;

# Borrar temporales
find -iname "*.stackdump" -exec rm "{}" \;

# Reemplazar tabuladores por espacios en archivos de codigo
find -name "*.cpp" -o -name "*.h" -o -name "*.txt" -o -name "*.sh" -exec sed -i "s/\t/    /g" "{}" \;

# Empaquetar con ZIP
DIR="$(pwd)"
DIRNAME="${DIR##*/}"
pushd ..
if [ -f "$DIRNAME.zip" ]; then
    rm "$DIRNAME.zip"
fi
zip -r -9 "$DIRNAME.zip" "$DIRNAME" 
popd
