#include "ToolTip.h"
#include <iostream>
//#include "IETThread.h"
#include "BaseRunner/BaseRunner.h"
#include "Gameobjects/UI/UIText.h"
#include "Gameobjects/Utilities/GameObjectManager.h"


ToolTip::ToolTip(String name, std::vector<String> toolTipLines) : ::AGameObject(name), toolTipLines(toolTipLines)
{
	// ui text
	button_1Text = new UIText("toolTip");
	GameObjectManager::GetInstance()->AddObject(button_1Text);
	button_1Text->SetPosition(BaseRunner::WINDOW_WIDTH / 2,
		BaseRunner::WINDOW_HEIGHT - 50);
	button_1Text->SetSize(25);
}

void ToolTip::Initialize()
{
	AGameObject::Initialize();

}

void ToolTip::Update(sf::Time deltaTime)
{
	AGameObject::Update(deltaTime);

	ticks += deltaTime.asSeconds();
	std::cout << "Timer: " << ticks << "<<" << currentToolTipLine << std::endl;
	if (ticks >= ticks_threshold)
	{
		this->ChangeToolTipLine(deltaTime);
		// reset timer
		ticks = 0.0f;
	}
}

void ToolTip::ChangeToolTipLine(sf::Time elapsedTime)
{
	if (currentToolTipLine >= toolTipLines.size())
	{
		currentToolTipLine = 0;
	}
	else
	{
		button_1Text->SetText(toolTipLines[currentToolTipLine++]);
	}
}
