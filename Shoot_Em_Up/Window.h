#pragma once

class WindowConfig
{
private:
	static WindowConfig* instance;

public:

	static WindowConfig* getInstance()
	{
		if (instance == nullptr) {
			instance = new WindowConfig();
		}
		return instance;
	}

	int SIZE_X = 1920;
	int SIZE_Y = 1080;
};