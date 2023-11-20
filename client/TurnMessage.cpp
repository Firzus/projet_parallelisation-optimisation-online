#include "TurnMessage.h"

TurnMessage::TurnMessage(RenderWindow& window) : window(window)
{
    fontBold.loadFromFile("assets/fonts/Roboto-Bold.ttf");

    textWhoPlay.setFont(fontBold);
    textWhoPlay.setCharacterSize(24);

    textLabelLeft.setFont(fontBold);
    textLabelLeft.setCharacterSize(24);
    textLabelLeft.setFillColor(Color(133, 94, 194));
    textLabelLeft.setString("C'est à");

    textLabelRight.setFont(fontBold);
    textLabelRight.setCharacterSize(24);
    textLabelRight.setFillColor(Color(133, 94, 194));
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

    //string message = "C'est à " + playerName + " de jouer";
    //textWhoPlay.setString(message);

    //FloatRect textRect = textWhoPlay.getGlobalBounds();
    //textWhoPlay.setPosition(Vector2f(500 / 2 - textRect.width / 2, 456));

    //

    textWhoPlay.setString(playerName);

    FloatRect rectTextWhoWin = textWhoPlay.getGlobalBounds();
    FloatRect rectTextLabelLeft = textLabelLeft.getGlobalBounds();
    FloatRect rectTextLabelRight = textLabelRight.getGlobalBounds();

    textLabelLeft.setPosition(Vector2f(0, 0));
    textWhoPlay.setPosition(Vector2f(0, 0));
    textLabelRight.setPosition(Vector2f(0, 0));

    //textWhoPlay.setPosition(Vector2f(250 - (rectTextWhoWin.width + rectTextLabel.width + spacing) / 2, 236));
    //textLabelLeft.setPosition(Vector2f(textWhoPlay.getPosition().x + rectTextWhoWin.width + 8, 236));
}