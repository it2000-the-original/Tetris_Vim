#include "Tetris.hpp"
#include "Matrix.hpp"
#include "Status.hpp"
#include "Ghost.hpp"
#include "Piece.hpp"
#include "Preview.hpp"
#include "Controls.hpp"
#include "Hold.hpp"

using namespace sf;

RenderWindow* Tetris::window;
Sprite Tetris::blocks;
Event Tetris::event;
Time Tetris::sTime;
Font Tetris::font;

Controls Tetris::controls;
Preview Tetris::preview;
Status Tetris::status;
Matrix Tetris::matrix;
Ghost Tetris::ghost;
Piece Tetris::piece;
Hold Tetris::hold;

Tetris::Tetris() {}

void Tetris::init(const int FPS, std::string title) {

	window = new RenderWindow(VideoMode(WW, WH), title, Style::Default);
	WView = window->getDefaultView();
	window->setFramerateLimit(FPS);
	window->setActive(true);
	loadTextures();

	sTime = seconds(1.f);

	matrix.init();
	status.init();
	preview.init();
	hold.init();

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
	hold.update();

	controls.checkInputs();
}

void Tetris::echeck() {
	
	while (window->pollEvent(event)) {

		switch (event.type) {

		case Event::Closed:
			window->close();
			break;

		case Event::Resized:
			checkWindowSize(event.size.width, event.size.height);
			break;
		}
	}
}

void Tetris::render() {
	
	window->clear(WColor);
	window->draw(background);

	matrix.draw();
	ghost.draw();
	piece.draw();
	preview.draw();
	status.draw();
	hold.draw();

	window->display();
}

void Tetris::step() {

	if (!piece.move(0, 1)) {

		if (piece.depose()) {

			matrix.check();
			preview.generate();
			controls.enableHold();
			piece.set(preview.get());
		}

		else restart(); // Game Over
	}
}

void Tetris::checkWindowSize(int _w, int _h) {

	int w = 0;
	int h = 0;

	if (_w >= MWW) w = _w;

	else w = MWW;

	if (_h >= MWH) h = _h;

	else h = MWH;

	window->setSize(Vector2u(w, h));

	resetView(w, h);
}

void Tetris::resetView(int w, int h) {

	float WHF = float(WW) / float(WH); // Window Height Fraction
	float _WHF= float(w) / float(h);   // Window Height Fraction of the resized window

	if (_WHF > WHF) {

		WView.setViewport(FloatRect((1.f - 1.f / _WHF) / 2.f, 0.f, 1.f / _WHF, 1.f));
	}

	else {

		WView.setViewport(FloatRect(0.f, (1.f - _WHF) / 2.f, 1.f, _WHF));
	}
	
	window->setView(WView);
}

void Tetris::loadTextures() {

	// Defining the textures
	Texture* wTexture = new Texture();
	Texture* bTexture = new Texture();

	if (!wTexture->loadFromFile(WPath) or
		!bTexture->loadFromFile(BPath) or
		!font.loadFromFile(FPath)) {

		window->close();
		return;
	}

	#ifdef SMOTH_TEXT 
	font.setSmooth(false);
	#endif

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
