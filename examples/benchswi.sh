#!/bin/sh

cd Prolog
echo -en "[$1].\ntest($2).\n" | exec pl -T0 -G0 -L0
