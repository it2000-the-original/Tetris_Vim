#include "Tetris.hpp"
#include "Config.h"

#ifdef HIDE_CONSOLE

// If you are on windows and HIDE_CONSOLE 
// option is anabled, the console will be hidden
#include <Windows.h>

#endif

const int FPS = 60;
const std::string title = "Tetris by it2000";

#ifdef HIDE_CONSOLE

int APIENTRY WinMain(HINSTANCE hInst, HINSTANCE hInstPrev, PSTR cmdline, int cmdshow)

#else

int main(int argc, char** argv)

#endif

{
	std::cout << "Tetris by it2000 version " << VERSION_MAJOR << "." << VERSION_MINOR << std::endl;

	Tetris tetris;

	srand(unsigned(time(NULL)));

	tetris.init(FPS, title);

	while (tetris.isRunning()) {

		tetris.update();
		tetris.echeck();
		tetris.render();
	}

	return 0;
}
