#!/usr/bin/env bash
gcc -I ./libs -o testing testing.c ./libs/cwalk.c && testing .