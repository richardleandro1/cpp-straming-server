export PKG_CONFIG_PATH=/usr/local/lib/pkgconfig:$PKG_CONFIG_PATH
rm -rf CMakeFiles CMakeCache.txt Server.xcodeproj
cmake -G "Xcode" -DCMAKE_C_COMPILER=/usr/bin/clang -DCMAKE_CXX_COMPILER=/usr/bin/clang++ .
open Server.xcodeproj
