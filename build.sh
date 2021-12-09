sudo apt install tree
rm -rf build
mkdir build
cd build
sudo rm -rf /opt/installed/util-cpp
sudo mkdir /opt/installed/util-cpp -p
cmake .. -DCMAKE_INSTALL_PREFIX=/opt/installed/util-cpp/
make
sudo make install
cd ..
tree /opt/installed/util-cpp

