NOTE: This Project is forked to BlackVyperStudios [(here)](https://github.com/BlackVyperStudios/snek) and will continue there. For an more advanced version of this Project, please take a look at [snek-ultimate](https://github.com/MCWertGaming/snek-utimate) wich is an complete reimplemntation of snek with more advanced and developed features.

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
