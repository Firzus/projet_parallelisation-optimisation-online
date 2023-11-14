#include <SFML/Graphics.hpp>

#include <string>

using namespace sf;
using namespace std;

class TurnMessage
{
public:
	TurnMessage(RenderWindow& window);
	~TurnMessage();

	void Draw();
	void Update(const string& playerName);

private:
	RenderWindow& window;

	Text textWhoPlay;
	Font fontBold;
};