#! /bin/bash
for f in ./test/*.test
do
  echo "Running $f"
  ./$f | grep "Error"
done
