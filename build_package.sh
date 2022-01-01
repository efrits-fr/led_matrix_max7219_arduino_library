#!/usr/bin/sh

mkdir -p .tmp && \
    cp `find . -name "*.c*" -or -name "*.h*"` .tmp/ && \
    (cd .tmp/ && zip ../led_matrix_max7219_arduino_library.zip *.c* *.h* >& /dev/null)
rm -rf .tmp

