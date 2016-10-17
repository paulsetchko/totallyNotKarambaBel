#!/bin/bash
while IFS= read -r -d $'\0' file; do
    a[i++]="$file"        # or however you want to process each file
done < <(find $1 -type f -print0)
echo $a
