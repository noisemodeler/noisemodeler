#!/usr/bin/bash
while true; do
  change=$(inotifywait -r -e close_write,moved_to,create,move .)
  changeFilename=${change#./ * }
  fileExtension=${changeFilename##*.}
  if [ "$fileExtension" = "hpp" ]; then 
    echo "Detected change in $changeFilename. Recompiling..."
    doxygen
  fi
done
