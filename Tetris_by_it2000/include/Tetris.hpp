#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

class Controls;
class Preview;
class Status;
class Matrix;
class Ghost;
class Piece;

const std::string WPath = "textures/background.png";
const std::string BPath = "textures/pieces.png";

const int PB = 32; // Size in pixels of a single block
const int MX = 64; // The x position in pixels where the matrix starts
const int MY = 64; // The same thing of before but in y

class Tetris {

private:

	sf::Sprite background;

public:

	static sf::RenderWindow* window;
	static sf::Sprite blocks;
	static sf::Event event;
	static sf::Time sTime; // Step time

	static Controls controls;
	static Preview preview;
	static Status status;
	static Matrix matrix;
	static Ghost ghost;
	static Piece piece;

	Tetris();

	void init(const int FPS, std::string title);
	void echeck();
	void update();
	void render();

	void step();

	void loadTextures();
	bool isRunning();
	void restart();
};