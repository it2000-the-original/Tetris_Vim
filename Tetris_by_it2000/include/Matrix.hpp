#include <array>

using namespace std;

class Matrix {

private:

	static const int W = 10; // Width
	static const int H = 20; // Height

public:

	array<array<int, H>, W> matrix;

	void init();
	void draw();
	void check();    // Check full lines
	void del(int l); // Clear a full line
};