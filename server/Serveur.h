#include <SFML/Graphics.hpp>

using namespace sf;

class Serveur
{
public:
	Serveur();
	virtual ~Serveur();
	void Run();

private:
	void ProcessEvents();
	void Render();
	void Update(float deltaTime);

	RenderWindow window;

	Clock clock;

};