#include <SFML/Graphics.hpp>
#include <string>

using namespace sf;
using namespace std;

class Menu
{
public:
	Menu(RenderWindow& window);
	~Menu();

	void Draw();
	void HandleInput(Event& event);
	string GetName() const;
	bool IsStartClicked() const;

private:
    RenderWindow& window;

    Text textTitle;
    Text textSubtitle;
    Text textInput;
    Text textStartButton;

    Font fontRegular;
    Font fontSemiBold;
    Font fontBold;

    RectangleShape rectInput;
    RectangleShape rectStartButton;

    string userInput;
    bool playClicked;
};