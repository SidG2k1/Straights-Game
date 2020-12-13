#include "board.h"

int main(int argc, char** argv) {
	int seed = 0;
	bool enableBonus = false;

	if (argc > 1) {
		try {
			std::string bonusFlag = "--enablebonus";
			if (argv[1] != bonusFlag) {
				seed = std::stoi(argv[1]);
			}

			for (int i = 0; i < argc; ++i) {
				if (argv[i] == bonusFlag) {
					enableBonus = true;
					break;
				}
			}
		} catch (...) {
			std::cout << "Incorrect command line options. Please try again." << std::endl;
			// exit main:
			return 0;
		}
	}
	// Bonuses Implemented:
	//	 smart computers
	//	 Ctrl-D quits + Robust command handling + better printing
	//	 end this round using "imtired" command
	//	 Done without explicit memory management

	try {
		// players are initialized from within Board
		Board game{enableBonus};

		// The game start method acts as a controller for the game.
		game.start(seed);
	} catch (QuitSignal) {
		// Since this program is RAII compliant, the memory will free itself
		//	and there is nothing else to do.
	}
}
