cd /project
yes | sh ./tests/scripts/install_lcov.sh
make fclean
make test
./test
