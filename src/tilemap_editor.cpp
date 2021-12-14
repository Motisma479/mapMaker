#include <cassert>
#include <iostream>
#include <fstream>

#include "ui.hpp"
#include "resources.hpp"

#include "tilemap_editor.hpp"

using namespace std;

//* TILE CLASS ==================================

// ------- CONSTRUCTORS / DESTRUCTORS --------- //
Tile::Tile(int id, int state, int type, Vector2 pos, Texture2D tex)
{
    mId    = id;
    mState = (TileState) state;
    mType  = (TileType)  type;
    mPos   = pos;
    mTex   = tex;
    mRec   = {pos.x, pos.y, TILE_SIZE, TILE_SIZE};
}

// ----------------- METHODS ----------------- //
void Tile::Update(){
    switch (mType)
    {
    case TileType::PLAINS_V_PATH:
    case TileType::PLAINS_H_PATH:
    case TileType::PLAINS_C_ROAD:
    case TileType::PLAINS_TR_CORNER:
    case TileType::PLAINS_TL_CORNER:
    case TileType::PLAINS_BR_CORNER:
    case TileType::PLAINS_BL_CORNER:
    case TileType::DUNGEON_V_PATH:
    case TileType::DUNGEON_H_PATH:
    case TileType::DUNGEON_C_ROAD:
    case TileType::DUNGEON_TL_CORNER:
    case TileType::DUNGEON_TR_CORNER:
    case TileType::DUNGEON_BL_CORNER:
    case TileType::DUNGEON_BR_CORNER:
        mState = TileState::ENMY;
        break;

    default:
        mState = TileState::FREE;
        break;
    }
}

//* TILE MAP CLASS ==============================

// -------- CONSTRUCTORS / DSETRUCTORS ------- //
TileMapEditor::TileMapEditor()
{
    mStart = mEnd = false;
}

TileMapEditor::~TileMapEditor()
{
    for(auto it : mTiles) delete it;
}

// ----------------- METHODS ----------------- //
void TileMapEditor::Init(int width, int height ,int textureWidth, int textureHeight, const string &fileName)
{
    mWidth  = width;
    mHeight = height;
    mName   = fileName;

    // ---------- LOCAL VARIABLES ------------ //
    int state_tmp = 1, type_tmp = 0, id_tmp = 0;

    // ------ TEXTURES INITIALIZATION -------- //
    for (int i = 0; i < 7; i++)
        for (int j = 0; j < 4; j++)
        {
            // Load the whole tilemap into a temporary image.
            Image tmp = LoadImageFromTexture(Resource::GetTexture("./assets/tilemaps/tiles.png"));

            // Crop the image to the desizired size then load it as texture in ground texture array.
            ImageCrop(&tmp, {(float)(j * TILE_SIZE), (float)(i * TILE_SIZE), TILE_SIZE, TILE_SIZE});
            mTerrain[id_tmp] = LoadTextureFromImage(tmp);

            // Unload temporary image and increment the id iterator.
            UnloadImage(tmp);
            id_tmp++;
        }
    
    id_tmp = 0; // Reset for another usage
    
    // ---------- CREATING MAP DATA ---------- //
   
    // Blank map.
    for (int i = 0; i < height; i++)
        for (int j = 0; j < width; j++)
        {
            // Add a new tile to the list.
            mTiles.emplace_back(new Tile(id_tmp,
                                        state_tmp,
                                        type_tmp, 
                                        {(float)(j * TILE_SIZE), (float)(i * TILE_SIZE)},
                                        mTerrain[type_tmp]));
            id_tmp++;
        }    
}

void TileMapEditor::Update(int toolState, int RClick, int LClick, Camera2D& camera)
{
    // Pencil tool update.
    if (toolState == 1)
    {
        if(IsMouseButtonDown(MOUSE_LEFT_BUTTON))
        {
            for (int i = 0; i < mWidth * mHeight; i++)
            {
                if(CheckCollisionPointRec(GetScreenToWorld2D(GetMousePosition(), camera),mTiles[i]->mRec))
                {
                    mTiles[i]->mType = (TileType)LClick;
                    mTiles[i]->mTex = mTerrain[LClick];
                    mTiles[i]->Update();
                }
            }
        }
        else if(IsMouseButtonDown(MOUSE_RIGHT_BUTTON))
        {
            for (int i = 0; i < mWidth * mHeight; i++)
            {
                if(CheckCollisionPointRec(GetScreenToWorld2D(GetMousePosition(), camera),mTiles[i]->mRec))
                {
                    mTiles[i]->mType = (TileType)RClick;
                    mTiles[i]->mTex = mTerrain[RClick];
                    mTiles[i]->Update();
                }
            }
        }
    }

    // Eraser tool update.
    if (toolState == 2)
    {
        if(IsMouseButtonDown(MOUSE_LEFT_BUTTON))
        {
            for (int i = 0; i < mWidth * mHeight; i++)
            {
                if(CheckCollisionPointRec(GetScreenToWorld2D(GetMousePosition(), camera),mTiles[i]->mRec))
                {
                    if (mTiles[i]->mState == TileState::S_ENMY) mStart = false;
                    if (mTiles[i]->mState == TileState::E_ENMY) mEnd   = false;
                    
                    mTiles[i]->mType = TileType::PLAINS_GRASS;
                    mTiles[i]->mTex = mTerrain[0];
                    mTiles[i]->Update();
                }
            }
        }
        else if(IsMouseButtonDown(MOUSE_RIGHT_BUTTON))
        {
            for (int i = 0; i < mWidth * mHeight; i++)
            {
                if(CheckCollisionPointRec(GetScreenToWorld2D(GetMousePosition(), camera),mTiles[i]->mRec))
                {
                    mTiles[i]->mType = (TileType)RClick;
                    mTiles[i]->mTex = mTerrain[RClick];
                    mTiles[i]->Update();
                }
            }
        }
    }

    // Flag tool update.
    if (toolState == 3)
    {
        if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && !mStart)
        {
            for (int i = 0; i < mWidth * mHeight; i++)
            {
                if(CheckCollisionPointRec(GetScreenToWorld2D(GetMousePosition(), camera),mTiles[i]->mRec))
                {
                    if (mTiles[i]->mState == TileState::ENMY)
                    {
                        mTiles[i]->mState = TileState::S_ENMY;
                        mStart = true;                        
                    }
                }
            }
        }
        else if(IsMouseButtonPressed(MOUSE_RIGHT_BUTTON) && !mEnd)
        {
            for (int i = 0; i < mWidth * mHeight; i++)
            {
                if(CheckCollisionPointRec(GetScreenToWorld2D(GetMousePosition(), camera),mTiles[i]->mRec))
                {
                    if (mTiles[i]->mState == TileState::ENMY)
                    {
                        mTiles[i]->mState = TileState::E_ENMY;
                        mEnd = true; 
                    }
                }
            }
        }
    }
}

void TileMapEditor::Draw()
{
    ClearBackground((Color){255, 255, 255, 255});

    // ---------- LOCAL VARIABLES ------------ //
    int id_tmp = 0;

    // --------- DRAW TILE MAP LOOP ---------- //
    for (int i = 0; i < mHeight; i++)
    {
        for (int j = 0; j < mWidth; j++)
        {
            DrawTexturePro(mTiles[id_tmp]->mTex, 
                          {0, 0, TILE_SIZE, TILE_SIZE},
                          {(float)(j * TILE_SIZE), (float)(i * TILE_SIZE), TILE_SIZE, TILE_SIZE},
                          {0, 0}, 0, RAYWHITE);
            if (mTiles[id_tmp]->mState == TileState::S_ENMY)
            {
                DrawRectanglePro({(float)(j * TILE_SIZE), (float)(i * TILE_SIZE), TILE_SIZE, TILE_SIZE},
                          {0, 0}, 0, {0, 0, 255, 50});
            }
            if (mTiles[id_tmp]->mState == TileState::E_ENMY)
            {
                DrawRectanglePro({(float)(j * TILE_SIZE), (float)(i * TILE_SIZE), TILE_SIZE, TILE_SIZE},
                          {0, 0}, 0, {255, 0, 0, 50});
            }
            
            DrawRectangleLinesEx({(float)j *32, (float)i * 32, 32, 32}, 0.5, GRAY);
            id_tmp++;
        }
    }

}

void TileMapEditor::Save()
{
    if (mStart && mEnd)
    {
        int state_tmp(0), type_tmp(0), id_tmp(0);

        string imageName = {"./levels/" + mName + ".png"};
        TakeScreenshot(imageName.c_str());

        // Load the map file acccording to map name.
        string path = {"./levels/" + mName + ".map"};
        ofstream fs{path.c_str()};       

        if(fs.is_open())
        {
            fs << mWidth << " " << mHeight << endl;

            for (int i = 0; i < mHeight; i++)
            {
                for (int j = 0; j < mWidth; j++)
                {

                    state_tmp = (int)mTiles[id_tmp]->mState;
                    type_tmp = (int)mTiles[id_tmp]->mType;

                    fs << state_tmp; fs << ":" << type_tmp;
                    if (j + 1 < mWidth) fs << ",";
                    
                    id_tmp++;
                }
                fs << endl;
            }
        
        }
        fs.close();
    }
    else
    {
        mErrorCounter = 120;
    }

}