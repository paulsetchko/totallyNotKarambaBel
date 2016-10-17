#!/bin/bash
FINDERPATH="./finder"
if [ ! -f $FINDERPATH ]
  then
    echo "$FINDERPATH doesn't exist"
    exit 1
fi
#get a root dir as the 1st argument
#validate the input
if [ -z "$1" ]
  then
    echo "No arguments have been passed"
    exit 1
fi
if [ ! -e $1 ]
  then
    echo "The directory you've entered does not exist"
    exit 1
elif [ ! -d $1 ]
  then
    echo "$1 already exists but is not a directory" 1>&2
    exit 1
fi
#concat a long string from the files in the root dir
ARGS=""
while IFS= read -r -d $'\0' file; do
  ARGS+=" $file"
done < <(find $1 -type f -print0)
#echo $ARGS
#launch the binary with the concatted string as a parameter
$FINDERPATH $ARGS 
#parse the output
#
#while IFS= read -r -d $'\0' file; do
#    a[i++]="$file"        # or however you want to process each file
#done < <(find $1 -type f -print0)
#echo $a

exit 0
