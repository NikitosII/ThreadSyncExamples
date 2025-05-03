#!/bin/bash

SOURCE_FILE="file2_1.c"
EXECUTABLE="file2_1"

gcc -o $EXECUTABLE $SOURCE_FILE -pthread

if [ $? -ne 0 ]; then
    echo "Ошибка компиляции."
    exit 1
fi
./$EXECUTABLE
