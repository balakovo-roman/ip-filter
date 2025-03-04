#!/bin/bash

if ! command -v clang-format &> /dev/null; then
    echo "Error: clang-format not found!"
    exit 1
fi

find ./source -type f \( -name '*.cpp' -o -name '*.hpp' -o -name '*.h' -o -name '*.c' \) \
    -exec echo "Formatting file: {}" \; \
    -exec clang-format -i {} +

echo "Formatting is complete"