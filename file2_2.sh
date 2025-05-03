#!/bin/bash

SOURCE_FILE="file2_2.c"
EXECUTABLE="file2_2"

gcc -o $EXECUTABLE $SOURCE_FILE -pthread

if [ $? -ne 0 ]; then
    echo "Ошибка компиляции."
    exit 1
fi
./$EXECUTABLE
