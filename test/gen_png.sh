#!/bin/bash

d="${0%/*}"
d="${d%/*}"
sd="$d/test"
td="$d/txt"
pd="$d/png"
if [[ -z $1 ]]; then
    fdf="$(find "$d"/test_maps/*.fdf)"
else
    fdf="$1"
fi
echo $fdf
mkdir -p $td $pd

for f in $fdf
do
    name=${f##*/}
    name=${name%.*}
    t="$td/$name.txt"
    p="$pd/$name.png"
    echo "Process: $f, $name"
    if ./fdf "$f" > "$t"; then
        echo "Plot to: $t"
    else
        echo "Failed to plot: $f" >&2
        continue
    fi
    if python "$sd/draw_points.py" "$t" "$p"; then
        echo "Draw to $p"
    else
        echo "Failed to draw: $t" >&2
        continue
    fi
    open "$p"
done
