#include "board.h"

int main(int argc, char** argv) {
	int seed = 0;

	if (argc > 1) {
		seed = std::stoi(argv[1]);
	}

	// players are initialized from within Board
	Board game;

	try {
		game.start(seed);
	} catch (QuitSignal) {
		// Since this program is RAII compliant, the memory will free itself
		//	and there is nothing else to do.
	}
}
