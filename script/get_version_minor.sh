#!/bin/bash

(cat VERSION 2>/dev/null || echo 0) | sed 's/^\([0-9][0-9]*\)\.\([0-9][0-9]*\)-\([0-9][0-9]*\)-.*/\2/g' || echo 0
