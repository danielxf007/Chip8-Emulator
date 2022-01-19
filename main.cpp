#include "emulator.h"

int main(){
	Emulator *emulator = new Emulator;
	emulator->emulate();
	delete emulator;
    return 0;
}