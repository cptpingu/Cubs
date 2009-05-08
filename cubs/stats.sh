#!/bin/sh

echo "== Stats for the cubs project =="
echo
echo -n "Files :      "
find src | grep -v ".svn" | grep -E "(*.hxx|*.hh|*.cc)" | wc -l

stat=`find src | grep -v ".svn" | grep -E "(*.hxx|*.hh|*.cc)" | xargs cat | wc`
echo -n "Lines :      "
echo $stat | cut -d " " -f 1
echo -n "Words :      "
echo $stat | cut -d " " -f 2
echo -n "Characters : "
echo $stat | cut -d " " -f 3
