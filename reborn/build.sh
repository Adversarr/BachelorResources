#!/bin/bash


if ! type "xmake" > /dev/null; then
  echo "reborn relies on XMake build system. Check the existance of xmake first."
fi

xmake f -y -m release
xmake b

