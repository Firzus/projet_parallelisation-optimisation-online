class Serveur
{
public:
	Serveur();
	virtual ~Serveur();
	void Run();
	void ProcessEvents();
	virtual void Update(float deltaTime);

private:

};