#include "TurnMessage.h"

TurnMessage::TurnMessage(RenderWindow& window) : window(window)
{
    fontBold.loadFromFile("assets/fonts/Roboto-Bold.ttf");

    textWhoPlay.setFont(fontBold);
    textWhoPlay.setCharacterSize(24);

    textLabelLeft.setFont(fontBold);
    textLabelLeft.setCharacterSize(24);
    textLabelLeft.setFillColor(Color(133, 94, 194));
    textLabelLeft.setString("C'est a");

    textLabelRight.setFont(fontBold);
    textLabelRight.setCharacterSize(24);
    textLabelRight.setFillColor(Color(133, 94, 194));
    textLabelRight.setString("de jouer");
}

TurnMessage::~TurnMessage() {}

void TurnMessage::Draw()
{
    window.draw(textWhoPlay);
    window.draw(textLabelLeft);
    window.draw(textLabelRight);
}

void TurnMessage::Update(const string& playerName)
{
    if (playerName != "Ordinateur")
    {
        textWhoPlay.setFillColor(Color(254, 254, 223));
    }
    else
    {
        textWhoPlay.setFillColor(Color(0, 201, 168));
    }

    textWhoPlay.setString(playerName);

    FloatRect rectTextWhoWin = textWhoPlay.getGlobalBounds();
    FloatRect rectTextLabelLeft = textLabelLeft.getGlobalBounds();
    FloatRect rectTextLabelRight = textLabelRight.getGlobalBounds();

    const float globalWidth = spacing*2 + rectTextWhoWin.width + rectTextLabelLeft.width + rectTextLabelRight.width;

    textLabelLeft.setPosition(Vector2f(250 - globalWidth / 2, 456));
    textWhoPlay.setPosition(Vector2f(250 - globalWidth / 2 + rectTextLabelLeft.width + spacing, 456));
    textLabelRight.setPosition(Vector2f(250 - globalWidth / 2 + rectTextLabelLeft.width + 2*spacing + rectTextWhoWin.width, 456));
}