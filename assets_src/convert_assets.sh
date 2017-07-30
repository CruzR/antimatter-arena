#!/bin/bash

set -euo pipefail
IFS=$'\n\t'

for svgfile in *.svg; do
	inkscape -e "../assets/${svgfile%.svg}.png" "${svgfile}"
done
