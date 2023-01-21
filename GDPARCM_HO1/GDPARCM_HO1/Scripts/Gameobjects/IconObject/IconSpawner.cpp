#include "IconSpawner.h"

#include <format>

#include "IconObject.h"
#include "BaseWindow/BaseWindow.h"
#include "Gameobjects/Utilities/GameObjectManager.h"

IconSpawner::IconSpawner(String name, String none) : ::AGameObject(name)
{
}

void IconSpawner::Initialize()
{
	AGameObject::Initialize();
}

void IconSpawner::Update(sf::Time deltaTime)
{
	AGameObject::Update(deltaTime);
	/*
	for (int index = 0;currentPosY < BaseWindow::WINDOW_HEIGHT || index > size;)
	{
		for (;currentPosX < BaseWindow::WINDOW_WIDTH || index > size; index++)
		{
			char str[40];
			sprintf(str, "tile%3f", index);
			string iconName = str;

			IconObject* iconObject = new IconObject("IconObject" + std::to_string(index), iconName);
			GameObjectManager::GetInstance()->AddObject(iconObject);

			currentPosX += increment;
		}
		currentPosY += increment;
		currentPosX = 0;
	}
	*/
	ticks += deltaTime.asSeconds();

	if (ticks >= spawn_interval && index <= size)
	{
		ticks = 0.0f;
		String iconName = std::format("tile{:03}", index++);
		std::cout << std::format("iconName: {}--rowIndex: {}\n", iconName, rowCount);
		
		IconObject* iconObject = new IconObject("IconObject" + std::to_string(index), iconName);
		GameObjectManager::GetInstance()->AddObject(iconObject);
		iconObject->SetPosition(currentPosX, currentPosY);
		currentPosX += increment;
		// back to first rowCount
		if (++rowCount > rowLimit)
		{
			rowCount = 0;
			currentPosX = 0;
			colCount++;
			currentPosY += increment;
		}
		// back to start position
		if (colCount > colLimit)
		{
			rowCount = 0;
			currentPosX = 0;
			colCount = 0;
			currentPosY = 0;
		}
		
	}
}

