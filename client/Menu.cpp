#include "Menu.h"

Menu::Menu(sf::RenderWindow& window) : window(window)
{
    fontRegular.loadFromFile("assets/fonts/Roboto-Regular.ttf");
    fontSemiBold.loadFromFile("assets/fonts/Roboto-Medium.ttf");
    fontBold.loadFromFile("assets/fonts/Roboto-Bold.ttf");

    textTitle.setFont(fontBold);
    textTitle.setString("Tic Tac Toe");
    textTitle.setCharacterSize(36);
    textTitle.setFillColor(Color(133, 94, 194));
    textTitle.setPosition(Vector2f(158, 80));

    textSubtitle.setFont(fontRegular);
    textSubtitle.setString("Create by Firzus");
    textSubtitle.setCharacterSize(12);
    textSubtitle.setFillColor(Color(133, 94, 194));
    textSubtitle.setPosition(Vector2f(207, 122));

    textInput.setFont(fontSemiBold);
    textInput.setString("Your name");
    textInput.setCharacterSize(14);
    textInput.setFillColor(Color(133, 94, 194));
    textInput.setPosition(Vector2f(125, 250));

    rectInput.setFillColor(Color(133, 94, 194));
    rectInput.setSize(Vector2f(250, 2));
    rectInput.setPosition(Vector2f(125, 270));

    rectStartButton.setSize(Vector2f(250, 40));
    rectStartButton.setPosition(Vector2f(125, 288));
    rectStartButton.setFillColor(Color(133, 94, 194));

    textStartButton.setFont(fontRegular);
    textStartButton.setString("START");
    textStartButton.setCharacterSize(16);
    textStartButton.setFillColor(Color(243, 197, 255));

    FloatRect textRect = textStartButton.getLocalBounds();
    textStartButton.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
    textStartButton.setPosition(rectStartButton.getPosition() + Vector2f(rectStartButton.getSize() / 2.0f));

    playClicked = false;
}

Menu::~Menu() {}

void Menu::Draw()
{
    window.draw(textTitle);
    window.draw(textSubtitle);
    window.draw(rectInput);
    window.draw(textInput);
    window.draw(rectStartButton);
    window.draw(textStartButton);
}

void Menu::HandleInput(Event& event)
{
    if (event.type == Event::TextEntered) {

        if (event.text.unicode == 8 && !userInput.empty()) {
            userInput.pop_back();
        }

        else if (event.text.unicode < 128 && event.text.unicode > 31) {
            userInput += static_cast<char>(event.text.unicode);
        }

        textInput.setString(userInput.empty() ? "Your name" : userInput);
    }

    if (event.mouseButton.button == Mouse::Left) {
        Vector2f mousePos = window.mapPixelToCoords(Mouse::getPosition(window));
        if (rectStartButton.getGlobalBounds().contains(mousePos)) {
            GameManager::GetInstance().SetPlayerName(userInput);
            playClicked = true;
        }
    }
    else if (event.type == Event::KeyPressed && event.key.code == Keyboard::Enter) {
        GameManager::GetInstance().SetPlayerName(userInput);
        playClicked = true;
    }
}

string Menu::GetName() const
{
    return userInput;
}

bool Menu::IsStartClicked() const
{
    return playClicked;
}