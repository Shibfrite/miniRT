#!/bin/bash

FOLDER="./sources"
MAKEFILE="./Makefile"
TARGET_LINE="^SRC_FILES[[:space:]]*:="

monitor() {
  for file in "$FOLDER"/*.{c,cpp}; do
	[ -e "$file" ] || continue
	fname=$(basename "$file")
    if ! grep -q "$fname" "$MAKEFILE"; then
      sed -i "/$TARGET_LINE/ s|$| $fname|" "$MAKEFILE"
    fi
  done
}

monitor;
