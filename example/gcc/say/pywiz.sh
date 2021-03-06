#!/bin/sh

export WAV=`pwd`/sample.wav

if [ ! -d $PYWIZ_DIR ]; then
  echo "$PYWIZ_DIR not found - export set to checkout of https://github.com/ptwz/python_wizard.git"
  exit 0
fi

cd $PYWIZ_DIR

if [ "${1:-}" = "-h" ]; then
  python3 ./python_wizard -h
else
  python3 ./python_wizard \
    -w 2 \
    -u 0.3 \
    -F 25 -V -S \
    -p -a -0.9373 \
    -m 0.9 \
    -r 50,1000 \
    -T tms5200 \
    -f hex \
    -p $WAV | fold -s -w 24
fi
