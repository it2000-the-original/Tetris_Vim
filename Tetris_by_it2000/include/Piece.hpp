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

class Piece {

private:

	int x, y;

	int piece;

	std::array<Block, 4> blocks;

public:

	void set(int p);

	bool move(int _x, int _y);
	bool rotate();
	void fall();

	// Check if the piece is in a correct position
	bool check(std::array<Block, 4> _blocks, int _x, int _y);
	bool check(std::array<Block, 4> _blocks);
	bool check(int _x, int _y);

	void depose(); // Put the piece inside the matrix

	void draw();

	std::array<Block, 4> getBlocks();
	int getPiece();
};