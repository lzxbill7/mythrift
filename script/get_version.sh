#!/bin/bash

tagregex="v[0-9]*.[0-9]*"
ver="$(git describe --tags --dirty --always --long --match=${tagregex} 2>/dev/null)"

if [ -z "$ver" ]; then
    ver="$(cat VERSION)"
else
    ver="${ver#v}"
    echo "$ver" > VERSION
fi

if [ -z "$ver" ]; then
    ver="0.0-0-unknown-unknown"
    echo "$ver" > VERSION
fi

echo "$ver"
