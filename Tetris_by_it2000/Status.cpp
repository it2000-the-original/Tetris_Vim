#include "Status.hpp"
#include "Tetris.hpp"
#include <iostream>

using namespace sf;

void Status::init() {

	Font* font = new Font();

	if (!font->loadFromFile(FPath)) {

		return;
	}

	// This doesn't work on Linux
	//font->setSmooth(false);

	scoreText.setFont(*font);
	levelText.setFont(*font);
	linesText.setFont(*font);
	numScoreText.setFont(*font);
	numLevelText.setFont(*font);
	numLinesText.setFont(*font);

	scoreText.setString("score");
	levelText.setString("level");
	linesText.setString("lines");

	scoreText.setCharacterSize(S);
	levelText.setCharacterSize(S);
	linesText.setCharacterSize(S);
	numScoreText.setCharacterSize(NS);
	numLevelText.setCharacterSize(NS);
	numLinesText.setCharacterSize(NS);

	scoreText.setFillColor(Color::Yellow);
	levelText.setFillColor(Color::Yellow);
	linesText.setFillColor(Color::Yellow);
	numScoreText.setFillColor(Color::Yellow);
	numLevelText.setFillColor(Color::Yellow);
	numLinesText.setFillColor(Color::Yellow);

	scoreText.setPosition(Vector2f(float(CX + (CS - scoreText.getLocalBounds().width) / 2), float(CY + TPADDING)));
	levelText.setPosition(Vector2f(float(CX + (CS - levelText.getLocalBounds().width) / 2), float(CY + CS + TPADDING)));
	linesText.setPosition(Vector2f(float(CX + (CS - linesText.getLocalBounds().width) / 2), float(CY + CS * 2 + TPADDING)));
}

void Status::update() {

	numScoreText.setString(std::to_string(score));
	numLevelText.setString(std::to_string(level));
	numLinesText.setString(std::to_string(lines));

	numScoreText.setPosition(Vector2f(float(CX + (CS - numScoreText.getLocalBounds().width) / 2), float(CY + NPADDING)));
	numLevelText.setPosition(Vector2f(float(CX + (CS - numLevelText.getLocalBounds().width) / 2), float(CY + CS + NPADDING)));
	numLinesText.setPosition(Vector2f(float(CX + (CS - numLinesText.getLocalBounds().width) / 2), float(CY + CS * 2 + NPADDING)));

	level = lines / LEVEL_LINES + 1;
}

void Status::draw() {

	Tetris::window.draw(scoreText);
	Tetris::window.draw(levelText);
	Tetris::window.draw(linesText);
	Tetris::window.draw(numScoreText);
	Tetris::window.draw(numLevelText);
	Tetris::window.draw(numLinesText);
}

void Status::reset() {

	score = 0;
	level = 0;
	lines = 0;
}