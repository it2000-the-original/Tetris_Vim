#include <array>

namespace t {

	const int tetrominos[7][4] = {
		4, 5, 6, 7, // I
		0, 4, 5, 6, // J
		2, 4, 5, 6, // L
		1, 2, 5, 6, // O
		1, 2, 4, 5, // S
		1, 4, 5, 6, // T
		0, 1, 5, 6  // Z
	};
};

struct Block {
	int x;
	int y;
};

using Blocks = std::array<Block, 4>;
using Test = std::array<Block, 5>;
using Tests = std::array<Test, 4>;

const Tests WKTests {{

	// Wall Kicks tests for: J L S T Z
	{{{0, 0}, {-1, 0}, {-1, -1}, {0,  2}, {-1,  2}}},
	{{{0, 0}, { 1, 0}, { 1,  1}, {0, -2}, { 1, -2}}},
	{{{0, 0}, { 1, 0}, { 1, -1}, {0,  2}, { 1,  2}}},
	{{{0, 0}, {-1, 0}, {-1,  1}, {0, -2}, {-1, -2}}},
}};

const Tests IWKTests {{

	// Wall Kicks tests for: I
	{{{0, 0}, {-2, 0}, { 1, 0}, {-2,  1}, { 1, -2}}},
	{{{0, 0}, {-1, 0}, { 2, 0}, {-1, -2}, { 2,  1}}},
	{{{0, 0}, { 2, 0}, {-1, 0}, { 2, -1}, {-1,  2}}},
	{{{0, 0}, { 1, 0}, {-2, 0}, { 1,  2}, {-1 - 2}}},
}};

class Tetromino {

private:

	int tetromino;
	int x, y;

	int rstatus = 0; // Rotation status of the tetromino. Ex: 0, 1, 2 or 3
	int wkick = 0;   // The wall kick test executed in the last rotations

	Blocks blocks;

	bool _checkWkicks(Blocks _blocks);
	void _confirmRotation(Blocks _blocks, Block _move);

	int _TSpinABlocks();
	int _TSpinPBlocks();

	Tests _getWKTests();

public:

	void draw();

	int get();
	void set(int _tetromino);

	bool move(int _x, int _y);

	bool rotate();

	// Check if the tetromino is in a correct position

	bool check(Blocks _blocks, int _x, int _y);
	bool check(Blocks _blocks);
	bool check(int _x, int _y);

	// Put the tetromino inside the matrix

	bool depose(); 

	// Check the T-Spin

	bool checkTSpin();
	bool checkMiniTSpin();

	Blocks getBlocks();

	static int getWidth(int _tetromino);
	static int getHeight(int _tetromino);
};