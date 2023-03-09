#include <fstream>
#include <iostream>
#include <filesystem>
#include "TextureManager.h"

#include "Threads/StreamAssetLoader.h"
#include "Threads/ThreadPool.h"
#include "Utilities/Utils/StringUtils.h"

//a singleton class
TextureManager* TextureManager::sharedInstance = nullptr;

TextureManager* TextureManager::GetInstance() {
	if (sharedInstance == nullptr) {
		//initialize
		sharedInstance = new TextureManager();
	}

	return sharedInstance;
}

TextureManager::TextureManager()
{
	threadPool = new ThreadPool("threadPool", 60);
	threadPool->StartScheduler();

	this->CountStreamingAssets();
}

void TextureManager::LoadFromAssetList()
{
	std::cout << "[TextureManager] Reading from asset list" << std::endl;
	std::ifstream stream("Media/assets.txt");
	String path;

	while(std::getline(stream, path))
	{
		std::vector<String> tokens = StringUtils::split(path, '/');
		String assetName = StringUtils::split(tokens[tokens.size() - 1], '.')[0];
		this->InstantiateAsTexture(path, assetName, false);
		std::cout << "[TextureManager] Loaded texture: " << assetName << std::endl;
	}
}

void TextureManager::LoadStreamingAssets(IExecutionEvent* executionEvent)
{
	int i = 0;
	for (const auto& entry : std::filesystem::directory_iterator(STREAMING_PATH)) {
		//IETThread::sleep(200);
		String path = entry.path().generic_string();
		StreamAssetLoader* assetLoader = new StreamAssetLoader(path, executionEvent);
		threadPool->ScheduleTask(assetLoader);
	}
}

void TextureManager::LoadSingleStreamAsset(int index, IExecutionEvent* executionEvent)
{
	int fileNum = 0;

	for (const auto& entry : std::filesystem::directory_iterator(STREAMING_PATH)) {
		if (index == fileNum)
		{
			//simulate loading of very large file
			//<code here for thread sleeping. Fill this up only when instructor told so.>
			//IETThread::sleep(200);

			String path = entry.path().generic_string();
			StreamAssetLoader* assetLoader = new StreamAssetLoader(path, executionEvent);
			
			threadPool->ScheduleTask(assetLoader);
			break;
		}

		fileNum++;
	}
}

sf::Texture* TextureManager::GetFromTextureMap(const String assetName, int frameIndex)
{
	if (!this->textureMap[assetName].empty()) {
		return this->textureMap[assetName][frameIndex];
	}
	else {
		std::cout << "[TextureManager] No texture found for " << assetName << std::endl;
		return NULL;
	}
}

int TextureManager::GetNumFrames(const String assetName)
{
	if (!this->textureMap[assetName].empty()) {
		return this->textureMap[assetName].size();
	}
	else {
		std::cout << "[TextureManager] No texture found for " << assetName << std::endl;
		return 0;
	}
}

sf::Texture* TextureManager::GetStreamTextureFromList(const int index)
{
	return this->streamTextureList[index];
}

int TextureManager::GetNumLoadedStreamTextures() const
{
	return this->streamTextureList.size();
}

int TextureManager::GetStreamingAssetCount() const
{
	return streamingAssetCount;
}

int TextureManager::GetAssetLoadedCount() const
{
	return this->currentAssetsLoaded;
}

void TextureManager::SetAssetLoadedCount(int count)
{
	this->currentAssetsLoaded = count;
}

void TextureManager::CountStreamingAssets()
{
	streamingAssetCount = 0;
	streamingAssetCount = std::distance(std::filesystem::directory_iterator(STREAMING_PATH),
		std::filesystem::directory_iterator{});
	std::cout << "[TextureManager] Number of streaming assets: " << this->streamingAssetCount << std::endl;
}

void TextureManager::InstantiateAsTexture(String path, String assetName, bool isStreaming)
{
	sf::Texture* texture = new sf::Texture();
	texture->loadFromFile(path);
	this->textureMap[assetName].push_back(texture);

	if(isStreaming)
	{
		this->streamTextureList.push_back(texture);
	}
	else
	{
		this->baseTextureList.push_back(texture);
	}
}
