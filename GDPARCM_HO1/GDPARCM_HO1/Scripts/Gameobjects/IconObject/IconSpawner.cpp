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
	start();
}

void IconSpawner::Update(sf::Time deltaTime)
{
	AGameObject::Update(deltaTime);
	
}

void IconSpawner::run()
{
	while (index <= size)
	{
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
		// 1 second delay
		sleep(1000);
	}
}

