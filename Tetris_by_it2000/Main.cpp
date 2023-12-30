#include "Tetris.hpp"

const int FPS = 60;
const std::string title = "Tetris by it2000";

int main()
{
	std::cout << "Tetris by it2000 version 1.0" << std::endl;

	Tetris tetris;

	tetris.init(FPS, title);

	while (tetris.isRunning()) {

		tetris.update();
		tetris.echeck();
		tetris.render();
	}

	return 0;
}
