#!/bin/sh

cd $MESON_SOURCE_ROOT
git log --pretty=format:'* %aN <%aE>' | sort -u
