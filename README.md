# Indy500

Classic racing game. The source were taken (more or less) from mikerr´s Car Sprint Game.

![](/assets/indy500.bmp)

For local build:
```
mkdir build
cd build
cmake -D32BLIT_DIR=/path/to/32blit-sdk/ ..
make
```

For 32Blit build:
```
mkdir build.stm32
cd build.stm32
cmake .. -D32BLIT_DIR="/path/to/32blit/repo" -DCMAKE_TOOLCHAIN_FILE=/path/to/32blit/repo/32blit.toolchain
make
```

For PicoSystem build:
```
mkdir build.pico
cd build.pico
cmake .. -DCMAKE_TOOLCHAIN_FILE=../../32blit-sdk/pico.toolchain -DPICO_BOARD=pimoroni_picosystem
make
```

Platform/Editor specific insctuctions [can be found in the main 32blit repo](https://github.com/32blit/32blit-sdk#you-will-need)
(For Visual Studio, you should follow the "Option 2" instructions, as the boilerplate does not contain a solution file)
