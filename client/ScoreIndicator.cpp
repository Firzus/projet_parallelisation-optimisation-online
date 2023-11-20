#include "ScoreIndicator.h"

ScoreIndicator::ScoreIndicator(RenderWindow& window) : window(window)
{
	fontRegular.loadFromFile("assets/fonts/Roboto-Regular.ttf");

	textScoreP1.setFont(fontRegular);
	textScoreP2.setFont(fontRegular);

	textScoreP1.setCharacterSize(40);
	textScoreP2.setCharacterSize(40);

	textScoreP1.setPosition(Vector2f(64, 14));
	textScoreP2.setPosition(Vector2f(461, 14));

	textScoreP1.setFillColor(Color(254, 254, 223));
	textScoreP2.setFillColor(Color(0, 201, 168));

	textureO.loadFromFile("assets/icons/o.png");
	textureX.loadFromFile("assets/icons/x.png");

	spriteO.setTexture(textureO);
	spriteX.setTexture(textureX);

	spriteO.setScale(Vector2f(0.625, 0.625));
	spriteX.setScale(Vector2f(0.625, 0.625));

	spriteO.setPosition(Vector2f(16, 19.5));
	spriteX.setPosition(Vector2f(413, 19.5));
}

ScoreIndicator::~ScoreIndicator() {}

void ScoreIndicator::Draw()
{
	window.draw(spriteO);
	window.draw(spriteX);

	window.draw(textScoreP1);
	window.draw(textScoreP2);
}

void ScoreIndicator::Update(int scoreP1, int scoreP2)
{
	textScoreP1.setString(to_string(scoreP1));
	textScoreP2.setString(to_string(scoreP2));
}
