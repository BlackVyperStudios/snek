# snek
snek - A simple snake in the console

# build dependencies
## Linux
- a C++ compiler (gcc and clang are supported)
- ncurses
## Windows
- Msys2 with gcc and ncurses installed
```bash
pacman -Syu gcc ncurses
```

# compiling
## Linux
```bash
cmake
make
```
## Windows
```powershell
g++ /src/main.cpp -o snek.exe -static -lncurses
```
