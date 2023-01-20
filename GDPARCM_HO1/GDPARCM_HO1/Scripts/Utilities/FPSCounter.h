#pragma once
class UIText;

class FPSCounter
{
public:
	static FPSCounter* GetInstance();
	FPSCounter();
	void UpdateFPS(float fps);
	float GetFPS();
private:
	static FPSCounter* sharedInstance;
	UIText* button_1Text;
	float fps = 0;
};

