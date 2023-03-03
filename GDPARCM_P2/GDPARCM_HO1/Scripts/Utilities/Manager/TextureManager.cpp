#include <fstream>
#include <iostream>
#include <filesystem>
#include "TextureManager.h"

#include "Threads/StreamAssetLoader.h"
#include "Threads/ThreadPool.h"
#include "Utilities/Utils/StringUtils.h"

//a singleton class
TextureManager* TextureManager::sharedInstance = NULL;

TextureManager* TextureManager::GetInstance() {
	if (sharedInstance == NULL) {
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

void TextureManager::LoadStreamingAssets()
{
	for (const auto& entry : std::filesystem::directory_iterator(STREAMING_PATH)) {
		// simulate loading of very large file
		//IETThread::sleep(1000);

		String path = entry.path().generic_string();
		std::vector<String> tokens = StringUtils::split(path, '/');
		String assetName = StringUtils::split(tokens[tokens.size() - 1], '.')[0];
		InstantiateAsTexture(path, assetName, true);

		//std::cout << "[TextureManager] Loaded streaming texture: " << assetName << std::endl;
	}

}

void TextureManager::LoadStreamingAssets(IExecutionEvent* executionEvent)
{
	int i = 0;
	for (const auto& entry : std::filesystem::directory_iterator(STREAMING_PATH)) {
		//IETThread::sleep(200);
		String path = entry.path().generic_string();
		StreamAssetLoader* assetLoader = new StreamAssetLoader(path, executionEvent);
		std::cout << "Schedule Task!: " << i++ << std::endl;
		threadPool->ScheduleTask(assetLoader);
	}
}

void TextureManager::LoadSingleStreamAsset(int index)
{
	int fileNum = 0;
	
	for (const auto& entry : std::filesystem::directory_iterator(STREAMING_PATH)) {
		if(index == fileNum)
		{
			//simulate loading of very large file
			//<code here for thread sleeping. Fill this up only when instructor told so.>
			//IETThread::sleep(200);

			String path = entry.path().generic_string();
			std::vector <String > tokens = StringUtils::split(path, '/');
			
			//<code here for loading asset>
			String assetName = StringUtils::split(tokens[tokens.size() - 1], '.')[0];
			InstantiateAsTexture(path, assetName, true);
	
			std::cout << "[TextureManager] Loaded streaming texture: " << assetName << std::endl;
			break;
		}

		fileNum++;
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

void TextureManager::CountStreamingAssets()
{
	this->streamingAssetCount = 0;
	for (const auto& entry : std::filesystem::directory_iterator(STREAMING_PATH)) {
		this->streamingAssetCount++;
	}
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
