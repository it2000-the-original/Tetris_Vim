#include <array>

using namespace std;

// Scoring system constants
const int COMBO = 50;
const int SINGLE = 100;
const int DOUBLE = 300;
const int TRIPLE = 500;
const int TETRIS = 800;


class Matrix {

private:

	int comboCount;
	static const int W = 10; // Width
	static const int H = 20; // Height

public:

	array<array<int, H>, W> matrix;

	void init();
	void draw();
	void check();    // Check full lines
	void del(int l); // Clear a full line

	void checkLinesScore(int rLines);
	void checkComboScore(int rLines);
};