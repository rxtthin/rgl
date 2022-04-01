#!/bin/bash

echo "==========================="
echo "Compiling RGL shaders to shaders_out..."

rm -rf shaders_out
mkdir shaders_out

FILES="./shaders/*.glsl"

for f in $FILES
do
	if [ -f "$f" ]
	then
		BASENAME=$(basename -- $f)
		OUTFILE="./shaders_out/$BASENAME"

		echo "Compiling file $BASENAME to $OUTFILE" 

		while read -r line
		do
			echo "\"$line\n\"" >> $OUTFILE
		done < "$f"
	else
		echo "File $f doesn't exist!"
	fi
done
