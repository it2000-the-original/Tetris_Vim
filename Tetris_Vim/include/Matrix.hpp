#include <array>

using namespace std;

// Scoring system constants
const int COMBO = 50;
const int SINGLE = 100;
const int DOUBLE = 300;
const int TRIPLE = 500;
const int TETRIS = 800;
const int T_SPIN = 400;
const int MT_SPIN = 100;
const int TSINGLE = 800;
const int TDOUBLE = 1200;
const int TTRIPLE = 1600;
const int MTSINGLE = 200;
const int MTDOUBLE = 400;


class Matrix {

private:

	int comboCount;

public:

	static const int W = 10; // Width
	static const int H = 20; // Height

	array<array<int, H>, W> matrix;

	void init();
	void draw();
	void check();    // Check full lines
	void del(int l); // Clear a full line
	bool empty(int x, int y);

	void checkLinesScore(int rLines);
	void checkComboScore(int rLines);
	void checkTSpinScore(int rLines);
};