#include "BGObject.h"
#include <string>
#include "BGMovement.h"
#include "BGMPlaylist.h"
#include "BaseRunner/BaseRunner.h"
#include "Components/Renderer/Renderer.h"
#include "Gameobjects/Utilities/GameObjectManager.h"
#include "Utilities/Manager/TextureManager.h"

BGObject::BGObject(String name, String bgName, String scenePlaylist) : ::AGameObject(name), bgName(bgName), scenePlaylist(scenePlaylist) {}

BGObject::~BGObject()
{
	std::cout << "BGM DELETED!!!" << std::endl;
	DetachComponent(playlist);
	//delete playlist;
}

void BGObject::Initialize()
{
	AGameObject::Initialize();

	std::cout << "Declared as " << this->GetName() << "\n";
	
	// assign texture
	this->sprite = new sf::Sprite();
	sf::Texture* texture = TextureManager::GetInstance()->GetFromTextureMap(bgName, 0);
	sprite->setTexture(*texture);

	SetScale(1920 / GetLocalBounds().width,
		1080 / GetLocalBounds().height);
	SetPosition(BaseRunner::WINDOW_WIDTH / 2, BaseRunner::WINDOW_HEIGHT / 2);

	//BGMovement* movement = new BGMovement("BG_Movement");
	//AttachComponent(movement);

	playlist = new BGMPlaylist("BGM_Playlist", scenePlaylist);
	AttachComponent(playlist);

	Renderer* renderer = new Renderer("BG");
	renderer->AssignDrawable(sprite);
	AttachComponent(renderer);

}
