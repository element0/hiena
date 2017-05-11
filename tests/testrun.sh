#!/bin/sh

OUTBIN=out/bin

if [ -e $OUTBIN ]
then
    ./$OUTBIN/insert-bytes README.md 100 20 LICENSE 15

fi