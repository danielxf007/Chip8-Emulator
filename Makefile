
main: main
	g++ -o main emulator.cpp processor.cpp input.cpp  graphics.cpp main.cpp `sdl2-config --cflags --libs`
