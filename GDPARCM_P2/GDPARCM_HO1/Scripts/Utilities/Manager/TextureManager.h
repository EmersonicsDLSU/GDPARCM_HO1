#pragma once
#include <unordered_map>

#include "SFML/Graphics.hpp"

class ThreadPool;
class IExecutionEvent;

class TextureManager
{
public:
	typedef std::string String;
	typedef std::vector<sf::Texture*> TextureList;
	typedef std::unordered_map<String, TextureList> HashTable;
	
public:
	static TextureManager* GetInstance();
	void LoadFromAssetList(); //loading of all assets needed for startup
	void LoadStreamingAssets(IExecutionEvent* executionEvent); //loading of assets during runtime
	void LoadSingleStreamAsset(int index, IExecutionEvent* executionEvent);
	sf::Texture* GetFromTextureMap(const String assetName, int frameIndex);
	int GetNumFrames(const String assetName);

	sf::Texture* GetStreamTextureFromList(const int index);
	int GetNumLoadedStreamTextures() const;
	int GetStreamingAssetCount() const;
	int GetAssetLoadedCount() const;
	void SetAssetLoadedCount(int count);
	void InstantiateAsTexture(String path, String assetName, bool isStreaming);

private:
	TextureManager();
	TextureManager(TextureManager const&) {};             // copy constructor is private
	TextureManager& operator=(TextureManager const&) {};  // assignment operator is private
	static TextureManager* sharedInstance;

	HashTable textureMap;
	TextureList baseTextureList;
	TextureList streamTextureList;

	const std::string STREAMING_PATH = "Media/Streaming/";
	int currentAssetsLoaded = 0, streamingAssetCount = 0;

	void CountStreamingAssets();

	ThreadPool* threadPool;

};
