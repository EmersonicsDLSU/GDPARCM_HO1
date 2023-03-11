#include "StreamAssetLoader.h"

#include "IExecutionEvent.h"
#include "Utilities/Manager/TextureManager.h"
#include "Utilities/Utils/StringUtils.h"

StreamAssetLoader::StreamAssetLoader(String path, IExecutionEvent* executionEvent)
{
	this->path = path;
	execEvent = executionEvent;
}

StreamAssetLoader::~StreamAssetLoader()
{
	//std::cout << "Destroying stream asset loader. " << std::endl;
}

void StreamAssetLoader::OnStartTask()
{
	//std::cout << "Running stream asset loader " << std::endl;
	// simulate loading of very large file
	//IETThread::sleep(1000);

	std::vector<String> tokens = StringUtils::split(path, '/');
	String assetName = StringUtils::split(tokens[tokens.size() - 1], '.')[0];
	TextureManager::GetInstance()->InstantiateAsTexture(path, assetName, true);

	//std::cout << "[TextureManager] Loaded streaming texture: " << assetName << std::endl;
	if (execEvent != nullptr)
		execEvent->onFinishedExecution();

	// delete after being done
	delete this;
}

