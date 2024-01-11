#include <array>

struct Block {
	int x;
	int y;
};

const int pieces[7][4] = {
	4, 5, 6, 7, // I
	0, 4, 5, 6, // J
	2, 4, 5, 6, // L
	1, 2, 5, 6, // O
	1, 2, 4, 5, // S
	1, 4, 5, 6, // T
	0, 1, 5, 6  // Z
};

const std::array<std::array<Block, 5>, 4> WKTests {{

	// Wall Kicks tests for: J L S T Z
	{{{0, 0}, {-1, 0}, {-1, -1}, {0,  2}, {-1,  2}}},
	{{{0, 0}, { 1, 0}, { 1,  1}, {0, -2}, { 1, -2}}},
	{{{0, 0}, { 1, 0}, { 1, -1}, {0,  2}, { 1,  2}}},
	{{{0, 0}, {-1, 0}, {-1,  1}, {0, -2}, {-1, -2}}},
}};

const std::array<std::array<Block, 5>, 4> IWKTests {{

	// Wall Kicks tests for: I
	{{{0, 0}, {-2, 0}, { 1, 0}, {-2,  1}, { 1, -2}}},
	{{{0, 0}, {-1, 0}, { 2, 0}, {-1, -2}, { 2,  1}}},
	{{{0, 0}, { 2, 0}, {-1, 0}, { 2, -1}, {-1,  2}}},
	{{{0, 0}, { 1, 0}, {-2, 0}, { 1,  2}, {-1 - 2}}},
}};

class Piece {

private:

	int x, y;

	int piece;
	int rstatus = 0;

	std::array<Block, 4> blocks;

public:

	void set(int p);

	bool move(int _x, int _y);
	bool rotate();
	int fall();

	// Check if the piece is in a correct position
	bool check(std::array<Block, 4> _blocks, int _x, int _y);
	bool check(std::array<Block, 4> _blocks);
	bool check(int _x, int _y);

	void depose(); // Put the piece inside the matrix

	void draw();

	bool wkicks(std::array<Block, 4> _blocks);
	std::array<Block, 4> getBlocks();
	int getPiece();
};