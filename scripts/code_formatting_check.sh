#!/bin/bash

files=$(find . -type f \( -name "*.cpp" -o -name "*.h" \))
unformatted=false

for file in $files; do
  if ! diff -q "$file" <(clang-format "$file") > /dev/null 2>&1; then
      echo -en "\e[31m❌ File $file is not formatted correctly.\e[0m\n"
      unformatted=true
  fi
done

if [ "$unformatted" = true ]; then
    exit 1
fi

echo -en "\e[32m✅ All files are formatted correctly.\e[0m\n"

exit 0
