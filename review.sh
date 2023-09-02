#!/bin/bash

# Get the list of files checked into Git
git_files=$(git ls-files)

echo "I have the following C project, could you please review and give feedback"

# Loop through the files and print their contents to the output file
for file in $git_files; do
  echo "File: $file"
  echo "------------------------------------"
  cat "$file"
  echo "" # Empty line
done



