#include <iostream>
#include <cstring>
#include "resources.hpp"

// Resource maps.
unordered_map<string, Texture2D> Resource::mSourceTexture;
unordered_map<string, Font>      Resource::mSourceFont;
unordered_map<string, Sound>     Resource::mSourceSound;
unordered_map<string, Music>     Resource::mSourceMusic;
unordered_map<string, Texture2D> Resource::mLevelsMetadata;

// Resource texture getter method.
const Texture2D& Resource::GetTexture(const string& name)
{
    auto iter = mSourceTexture.find(name);

    if(iter == mSourceTexture.end())
    {
        Resource::mSourceTexture[name] = LoadTexture(name.c_str());
        return mSourceTexture[name];
    }
    
    return iter->second;
}

// Resource font getter method.
const Font& Resource::GetFont(const string& name, int fontSize)
{
    auto iter = mSourceFont.find(name);

    if(iter == mSourceFont.end())
    {
        Resource::mSourceFont[name] = LoadFontEx(name.c_str(), fontSize, 0, 0);
        return mSourceFont[name];
    }
    
    return iter->second;
}

// Resource sound getter method.
const Sound& Resource::GetSound(const string& name)
{
    auto iter = mSourceSound.find(name);

    if(iter == mSourceSound.end())
    {
        Resource::mSourceSound[name] = LoadSound(name.c_str());
        return mSourceSound[name];
    }
    
    return iter->second;
}

// Resource music getter method.
const Music& Resource::GetMusic(const string& name)
{
    auto iter = mSourceMusic.find(name);

    if(iter == mSourceMusic.end())
    {
        Resource::mSourceMusic[name] = LoadMusicStream(name.c_str());
        return mSourceMusic[name];
    }
    
    return iter->second;
}

// Return all the level files names in the levels folder.
unordered_map<string, Texture2D> Resource::GetAvailableLevels()
{
    // We erase and unload all the element from previous list.
    for (auto iter : mLevelsMetadata) UnloadTexture(iter.second);
    mLevelsMetadata.erase(mLevelsMetadata.begin(), mLevelsMetadata.end());

    // We push back all the available.
    unordered_map<string, Texture2D> tmp;
    int count = 0;
    char** paths = GetDirectoryFiles("./levels/", &count);

    for (int i = 0; i < count; i++)
    {
        string fileName(paths[i]);
        string fullPath("./levels/");
        fullPath += fileName;
        string cmp(GetFileExtension(fullPath.c_str()));
        if (cmp.compare(".map") == 0)
        {
            // Set thumbnail name and path.
            fileName.erase(fileName.length() - 4, 4);
            string thumbnailFullPath("./levels/");
            thumbnailFullPath += fileName;
            thumbnailFullPath += ".png";

            // Set tilemap file name from thumbnail name.
            tmp.emplace(fileName, LoadTexture(thumbnailFullPath.c_str()));
        }
    }

    ClearDirectoryFiles();
    return tmp;
}

// Resource unload method.
void Resource::UnloadResource()
{
    // Unload textures.
    for (auto i = mSourceTexture.begin(); i != mSourceTexture.end(); i++) UnloadTexture(i->second);
    for (auto i = mSourceFont.begin();    i != mSourceFont.end();    i++) UnloadFont(i->second);
    for (auto i = mSourceSound.begin();   i != mSourceSound.end();   i++) UnloadSound(i->second);
    for (auto i = mSourceMusic.begin();   i != mSourceMusic.end();   i++) UnloadMusicStream(i->second);
    for (auto iter : mLevelsMetadata)                                     UnloadTexture(iter.second);

    // Clear all the elements of all the containers.
    mSourceTexture.clear();
    mSourceFont.clear();
    mSourceSound.clear();
    mSourceMusic.clear();
    mLevelsMetadata.clear();
}