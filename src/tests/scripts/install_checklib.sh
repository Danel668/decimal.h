wget 'https://github.com/libcheck/check/releases/download/0.15.2/check-0.15.2.tar.gz'
tar -xvf 'check-0.15.2.tar.gz'
cd 'check-0.15.2'
./configure
make
make check
make install
cd ..
