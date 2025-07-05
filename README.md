Need MSYS2 UCRT64 to build

Run ``pacman -Syuu`` *might need restart after executing that command on launch*, and install ``pacman -S mingw-w64-ucrt-x86_64-toolchain mingw-w64-ucrt-x86_64-ninja``

Install these ``pacman -S mingw-w64-ucrt-x86_64-freeglut mingw-w64-ucrt-x86_64-mesa``

Toolchain is important, since it contains the most essential tools like gcc, clang, etc.

Just run 'make' and you should be good.

Run 'make clean' to clean.