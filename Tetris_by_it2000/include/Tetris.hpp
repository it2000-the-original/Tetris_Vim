#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

class Preview;
class Status;
class Matrix;
class Ghost;
class Piece;

using namespace sf;

const std::string WPath = "textures/background.png";
const std::string BPath = "textures/pieces.png";

const int PB = 32; // Size in pixels of a single block
const int MX = 64; // The x position in pixels where the matrix starts
const int MY = 64; // The same thing of before but in y

class Tetris {

private:

	Sprite background;

	Time sTime; // Time between steps

	// Time between a movement to another

	const Time dTime = seconds(0.03f);
	const Time rTime = seconds(0.05f);
	const Time lTime = seconds(0.05f);
	const Time prTime = seconds(0.2f);
	const Time plTime = seconds(0.2f);
	const Time fTime = seconds(3.0f);

	// Clocks for various actions

	Clock sclock;  // Step
	Clock dclock;  // Move down
	Clock rclock;  // Move right
	Clock lclock;  // Move left
	Clock prclock; // Pre-move right
	Clock plclock; // Pre-move left
	Clock fclock;  // Final time

	// To prevent the repetition of the same specific
	// action while the key is pressed

	bool rotated = false;
	bool rotating = false;
	bool fallen = false;
	bool falling = false;

	// Check if the piece has moved to the right or
	// to the left in previous frames

	bool rmoved = false;
	bool lmoved = false;
	bool rmoving = false;
	bool lmoving = false;

	// Do a step without wait sTime, because is not necessary
	// after a fall or other

	bool jumpStep = false;

	bool last = false;   // Last step
	bool lasted = false;

public:

	static RenderWindow window;
	static Preview preview;
	static Status status;
	static Matrix matrix;
	static Sprite blocks;
	static Ghost ghost;
	static Piece piece;
	static Event event;

	Tetris();

	void init(const int FPS, std::string title);
	void echeck(); // check events
	void icheck(); // check inputs
	void update();
	void render();

	void step();

	void moveLeft();
	void moveRight();
	void moveDown();
	void rotate();
	void fall();

	bool isRunning();
	void checkLast();
	void restart();
};