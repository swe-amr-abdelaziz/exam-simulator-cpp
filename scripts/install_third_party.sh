#!/bin/bash

set -e

# [Boost::ext].DI
BOOST_DI_PATH=/usr/include/boost
mkdir -p $BOOST_DI_PATH
(cd $BOOST_DI_PATH && curl -O https://raw.githubusercontent.com/boost-ext/di/cpp14/include/boost/di.hpp)

echo -en "\e[32m✅ All third party libraries are installed successfully.\e[0m\n"

exit 0
