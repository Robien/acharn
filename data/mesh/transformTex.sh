#!/bin/bash
for f in $@
do
	echo "$f ..."
	cp $f $f.back && ./nePasLancer.sh $f > $f.new  && mv $f.new $f && echo "réussi ! \o/" && rm $f.back
done
