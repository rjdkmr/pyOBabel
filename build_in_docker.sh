#!/bin/bash
set -e -x

gcc --version
MWD=`pwd`


yum -y install epel-release
yum -y install cairo
yum -y install cairo-devel
yum -y install libxml2-devel
yum -y remove cmake28

mkdir external
cd external

# Install slightly newer version of cmake to compile openbabel
curl -O https://cmake.org/files/v3.0/cmake-3.0.2.tar.gz
tar -zxvf cmake-3.0.2.tar.gz
cd cmake-3.0.2
./bootstrap
make -j2
make install
cd ..

# Install eigen3 required by openbabel
wget http://bitbucket.org/eigen/eigen/get/3.2.10.tar.gz
mv 3.2.10.tar.gz eigen-3.2.10.tar.gz
mkdir eigen-3.2.10
tar --directory=eigen-3.2.10 --strip-components=1 -zxvf eigen-3.2.10.tar.gz
cd eigen-3.2.10
mkdir build
cd build
cmake ..
make -j2 && make install
cd ..
cd ..

# Install openbabel
git clone https://github.com/openbabel/openbabel
cd openbabel
mkdir build
cd build
cmake -DBUILD_SHARED=OFF -DCMAKE_POSITION_INDEPENDENT_CODE=ON -DWITH_INCHI=ON -DWITH_STATIC_INCHI=ON ..
make -j2
make install
cd ..
cd ..

# Out of external
cd ..

# Compile wheels
for PYBIN in /opt/python/*/bin; do
    "${PYBIN}/pip" install -r /io/dev-requirements.txt
    "${PYBIN}/pip" wheel -w /io/wheelhouse/ --no-deps --no-cache-dir /io/
done

# Bundle external shared libraries into the wheels
for whl in /io/wheelhouse/*.whl; do
    auditwheel show "$whl" 
    auditwheel repair "$whl" -w /io/wheelhouse/
done

# Install packages and test
for PYBIN in /opt/python/*/bin/; do
    "${PYBIN}/pip" install pyOBabel --no-index -f /io/wheelhouse
    "${PYBIN}/python" -c "import pyOBabel; print('=====\nTEST -- pyOBabel.openbabel version: ', pyOBabel.version_OB(), '\n=====')"
done
