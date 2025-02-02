#!/bin/bash

lcov --capture --directory . --output-file coverage.info
lcov --remove coverage.info '/usr/*' --output-file coverage.info
genhtml coverage.info --output-directory coverage

RESULT=$?
if [ $RESULT -eq 0 ]; then
    echo -en "\n\e[32m✅ Generated coverage report successfully.\e[0m\n"
else
    echo -en "\n\e[31m❌ Failed to generate coverage report.\e[0m\n"
fi

exit $RESULT
