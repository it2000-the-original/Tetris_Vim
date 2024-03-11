#include <array>

struct Block;

// Scoring system constants

const int COMBO = 50; // Combo count score

const int SINGLE = 100; // Single line
const int DOUBLE = 300; // Double line
const int TRIPLE = 500; // Triple line
const int TETRIS = 800; // Quadruple line

const int T_SPIN = 400;
const int TSINGLE = 800;  // T-Spin Single
const int TDOUBLE = 1200; // T-Spin Double
const int TTRIPLE = 1600; // T-Spin Triple

const int MT_SPIN = 100;  // Mini T-Spin
const int MTSINGLE = 200; // Mini T-Spin Single
const int MTDOUBLE = 400; // Mini T-SPin Doubel


class Matrix {

private:

	int comboCount;

	void _checkLinesScore(int rLines);
	void _checkComboScore(int rLines);
	void _checkTSpinScore(int rLines);
	void _playLinesSounds(int rLines);

	bool _isLineFull(int line);

	int _checkNormalTSpin(int rLines);
	int _checkMiniTSpin(int rLines);

public:

	static const int W = 10; // Width
	static const int H = 20; // Height

	std::array<std::array<int, H>, W> matrix;

	void init();
	void draw();

	void checkLines();

	void remove(int line);

	int get(Block block);
	bool empty(Block block);
	bool exist(Block block);
	bool set(Block block, int value);
};