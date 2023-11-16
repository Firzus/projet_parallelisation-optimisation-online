#include "ScoreIndicator.h"


ScoreIndicator::ScoreIndicator(RenderWindow& window) : window(window)
{
	fontRegular.loadFromFile("assets/fonts/Roboto-Regular.ttf");

	textureX.loadFromFile("assets/icons/x.png");
	textureO.loadFromFile("assets/icons/o.png");

	spriteX.setTexture(textureX);
	spriteO.setTexture(textureO);
}

ScoreIndicator::~ScoreIndicator()
{

}

void ScoreIndicator::Draw()
{

}

void ScoreIndicator::HandleEvent(Event& event)
{

}
