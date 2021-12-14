#pragma once

#include <unordered_map>
#include <string>

#include "raylib.h"

using namespace std;

class Resource
{
    private:
        static unordered_map<string, Texture2D> mSourceTexture;
        static unordered_map<string, Font>      mSourceFont;
        static unordered_map<string, Sound>     mSourceSound;
        static unordered_map<string, Music>     mSourceMusic;
        static unordered_map<string, Texture2D> mLevelsMetadata;

    public:

        static const Texture2D&                 GetTexture(const string& name);
        static const Font&                      GetFont(const string& name, int fontSize);
        static const Sound&                     GetSound(const string& name);
        static const Music&                     GetMusic(const string& name);
        static unordered_map<string, Texture2D> GetAvailableLevels();
        static void                             UnloadResource();
};