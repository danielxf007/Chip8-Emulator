#include "emulator.h"

int main(){
	Emulator *emulator = new Emulator;
	emulator->getRomPath();
	emulator->loadRom();
	emulator->emulate();
	delete emulator;
    return 0;
}