#!/bin/bash

files=$(find . -type f \( -name "*.cpp" -o -name "*.h" \))
invalid_naming_convention=false

# Regex for valid file names (lowercase letters, digits, dot '.', underscore '_', forward slash '/')
regex='^[a-z0-9_/\.]*$'

while IFS= read -r file; do
  if [[ ! $file =~ $regex ]]; then
    if [ "$invalid_naming_convention" = false ]; then
      echo -en "\e[31m❌ Invalid File(s):\e[0m\n"
      invalid_naming_convention=true
    fi
    output=""
    for (( i=2; i<${#file}; i++ )); do
      char="${file:i:1}"
      if [[ ! $char =~ $regex ]]; then
        output+="\e[9;31m$char\e[0m"
      else
        output+="$char"
      fi
    done
    # Print filename with its relative path, marking invalid characters
    echo -en "$output\n"
  fi
done <<< "$files"

if [ $invalid_naming_convention = true ]; then
  echo
  echo "All *.cpp & *.h files and their paths must follow this naming convention:"
  echo "- Lowercase letters"
  echo "- Digits"
  echo "- Only (dot '.', underscore '_', forward slash '/') for special characters"
  exit 1
else
  echo -en "\e[32m✅ All files and folders are following naming convention.\e[0m\n"
  exit 0
fi
