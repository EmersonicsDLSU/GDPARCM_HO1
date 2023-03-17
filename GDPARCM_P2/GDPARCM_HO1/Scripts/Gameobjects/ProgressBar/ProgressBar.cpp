#include "ProgressBar.h"
#include <string>
#include "BaseRunner/BaseRunner.h"
#include "Components/Renderer/Renderer.h"
#include "Gameobjects/Utilities/GameObjectManager.h"
#include "Utilities/Manager/SceneManager.h"
#include "Utilities/Manager/TextureManager.h"

ProgressBar::ProgressBar(String name, String pbName, String fillerName, AGameObject* icon) : ::AGameObject(name), pbName(pbName), fillerName(fillerName)
{
	this->icon = icon;
}

void ProgressBar::Initialize()
{
	AGameObject::Initialize();

	std::cout << "Declared as " << this->GetName() << "\n";

	// assign texture
	this->sprite = new sf::Sprite();
	sf::Texture* texture = TextureManager::GetInstance()->GetFromTextureMap(pbName, 0);
	this->sprite->setTexture(*texture);
	Renderer* renderer = new Renderer("Progress Bar");
	renderer->AssignDrawable(this->sprite);
	AttachComponent(renderer);

	// create filler obj
	fillerObj = new AGameObject("Filler");
	fillerObj->SetSprite(new sf::Sprite());
	sf::Texture *filerTexture = TextureManager::GetInstance()->GetFromTextureMap(fillerName, 0);
	fillerObj->GetSprite()->setTexture(*filerTexture);
	Renderer* fillerRenderer = new Renderer("FillerRenderer");
	fillerRenderer->AssignDrawable(fillerObj->GetSprite());
	fillerObj->AttachComponent(fillerRenderer);
	GameObjectManager::GetInstance()->AddObject(fillerObj);

	SetScale((BaseRunner::WINDOW_WIDTH - 200) / GetLocalBounds().width,
		1);
	SetPosition(BaseRunner::WINDOW_WIDTH / 2,
		BaseRunner::WINDOW_HEIGHT - 100);
	fillerObj->SetScale((BaseRunner::WINDOW_WIDTH - 200) / fillerObj->GetLocalBounds().width,
		1);
	fillerObj->SetPosition(BaseRunner::WINDOW_WIDTH / 2,
		BaseRunner::WINDOW_HEIGHT - 100);

	maxFillerWidth = fillerObj->GetLocalBounds().width;
}

void ProgressBar::Update(sf::Time deltaTime)
{
	AGameObject::Update(deltaTime);
	
	if (TextureManager::GetInstance()->GetAssetLoadedCount() < TextureManager::GetInstance()->GetStreamingAssetCount())
	{
		currentProgress = (float)TextureManager::GetInstance()->GetAssetLoadedCount() / (float)TextureManager::GetInstance()->GetStreamingAssetCount();
		
		double progressPosition = (double)maxFillerWidth * (double)currentProgress * 0.3109322848405417;
		//std::cout << "Progress: " << currentProgress << std::endl;
		//std::cout << "ProgressBar: " << progressPosition << std::endl;
		sf::IntRect cropRect(0, 0, progressPosition, fillerObj->GetLocalBounds().height); // Crop rectangle based on percentage
		fillerObj->GetSprite()->setTextureRect(cropRect); // Apply crop rectangle to sprite
		//std::cout << "ProgressWidth: " << fillerObj->GetLocalBounds().width << std::endl;

		icon->SetPosition(fillerObj->GetLocalBounds().width + 100,BaseRunner::WINDOW_HEIGHT - 200);
	}
	else
	{
		// load first scene
		SceneManager::getInstance()->loadScene(SceneManager::MAINMENU_SCENE);
	}

	//std::cout << "Progress: " << currentProgress << std::endl;
}
