#!/bin/sh
$EXTRACTRC `find . -name \*.rc -o -name \*.ui` >> rc.cpp
$XGETTEXT `find . -name \*.cpp` -o $podir/kdeverlang.pot
rm -f rc.cpp
