#pragma once
#include <memory>

class OWindow;
class OGame
{
public:
	OGame();
	~OGame();

	//Function to make the application run.
	void run();

	//Function to quit
	void quit();

protected:
	bool m_isRunning = true;

	//using these kind of pointers help in avoiding momeory leaks.
	std::unique_ptr<OWindow> m_display;
};

