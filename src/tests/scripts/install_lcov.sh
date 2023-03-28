#!/bin/bash

command -v 'lcov'
if [ $? -ne 0 ]
then
	echo 'To create an html report on code coverage by tests,'
	echo 'you need to install the lcov utility'
	echo 'Install lcov (yes/no)?'
	read ans
	if [[ "$ans" == "y" || "$ans" == "yes" ]]
	then
		wget 'https://github.com/linux-test-project/lcov/archive/refs/tags/v1.16.tar.gz'
		tar -xvf 'v1.16.tar.gz'
		cd 'lcov-1.16'
		make install
	fi
fi
