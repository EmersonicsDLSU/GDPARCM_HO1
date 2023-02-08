#include "StreamAssetLoader.h"

#include "IExecutionEvent.h"
#include "StringUtils.h"
#include "TextureManager.h"

StreamAssetLoader::StreamAssetLoader(String path, IExecutionEvent* executionEvent)
{
	this->path = path;
	execEvent = executionEvent;
}

StreamAssetLoader::~StreamAssetLoader()
{
	std::cout << "Destroying stream asset loader. " << std::endl;
}

void StreamAssetLoader::run()
{
	std::cout << "Running stream asset loader " << std::endl;
	// simulate loading of very large file
	IETThread::sleep(200);

	std::vector<String> tokens = StringUtils::split(path, '/');
	String assetName = StringUtils::split(tokens[tokens.size() - 1], '.')[0];
	TextureManager::getInstance()->instantiateAsTexture(path, assetName, true);

	std::cout << "[TextureManager] Loaded streaming texture: " << assetName << std::endl;

	execEvent->onFinishedExecution();
	// delete after being done
	delete this;
}
