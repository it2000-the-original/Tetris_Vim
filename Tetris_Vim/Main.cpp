#include <filesystem>
#include "Tetris.hpp"
#include "Config.h"

const int FPS = 60;
const std::string title = "Tetris Vim";

void setWinExeDir();
void setExeDir(char** argv);

#ifdef HIDE_CONSOLE

// If you are on windows and HIDE_CONSOLE 
// option is anabled, the console will be hidden

#include <Windows.h>

int APIENTRY WinMain(HINSTANCE hInst, HINSTANCE hInstPrev, PSTR cmdline, int cmdshow) {
	
	setWinExeDir();

#else

int main(int argc, char** argv) {

	setExeDir(argv);

#endif

	std::cout << "Tetris Vim version " << VERSION_MAJOR << "." << VERSION_MINOR << std::endl;

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

// These functions will set the executable dircetory
// as working directories, this is to make the executable
// indipendent to the directory where is launched

namespace fs = std::filesystem;

#ifdef HIDE_CONSOLE

void setWinExeDir() {

	char path[MAX_PATH];
	GetModuleFileName(NULL, path, MAX_PATH);
	fs::path exe_path = path;
	fs::current_path(exe_path.parent_path());
}

#else

void setExeDir(char** argv) {

	fs::path exe_path = fs::canonical(fs::path(argv[0]));
	fs::current_path(exe_path.parent_path());
}

#endif
