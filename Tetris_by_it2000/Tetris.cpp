#include "Tetris.hpp"
#include "Matrix.hpp"
#include "Status.hpp"
#include "Ghost.hpp"
#include "Piece.hpp"
#include "Preview.hpp"
#include "Controls.hpp"

using namespace sf;

RenderWindow* Tetris::window;
Sprite Tetris::blocks;
Event Tetris::event;
Time Tetris::sTime;

Controls Tetris::controls;
Preview Tetris::preview;
Status Tetris::status;
Matrix Tetris::matrix;
Ghost Tetris::ghost;
Piece Tetris::piece;

Tetris::Tetris() {}

void Tetris::init(const int FPS, std::string title) {

	window = new RenderWindow(VideoMode(619, 768), title, Style::Default);
	window->setFramerateLimit(FPS);
	window->setActive(true);

	loadTextures();

	sTime = seconds(1.f);

	matrix.init();
	status.init();
	preview.init();

	piece.set(preview.get());

	std::cout << "Window has been created" << std::endl;
}

void Tetris::update() {

	if (controls.isStepReady()) {

		controls.resetStep();
		step();
	}

	ghost.update();
	preview.update();
	status.update();

	controls.checkInputs();
}

void Tetris::echeck() {
	
	while (window->pollEvent(event)) {

		switch (event.type) {

		case Event::Closed:
			window->close();
			break;
		}
	}
}

void Tetris::render() {
	
	window->clear();
	window->draw(background);

	matrix.draw();
	ghost.draw();
	piece.draw();
	preview.draw();
	status.draw();

	window->display();
}

void Tetris::step() {

	if (!piece.move(0, 1)) {

		if (piece.depose()) {

			matrix.check();
			preview.generate();
			piece.set(preview.get());
		}

		else restart(); // Game Over
	}
}

void Tetris::loadTextures() {

	// Defining the textures

	Texture* wTexture = new Texture();
	Texture* bTexture = new Texture();

	if (!wTexture->loadFromFile(WPath) or
		!bTexture->loadFromFile(BPath)) {

		window->close();
		return;
	}

	background.setTexture(*wTexture);
	blocks.setTexture(*bTexture);
}

bool Tetris::isRunning() {

	return window->isOpen();
}

void Tetris::restart() {

	matrix.init();
	preview.init();
	status.reset();
	controls.resetStep();
	piece.set(preview.get());
}
