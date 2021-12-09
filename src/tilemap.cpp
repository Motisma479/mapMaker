#include <cassert>
#include <iostream>
#include <fstream>

#include "tilemap.hpp"
#include "resources.hpp"

using namespace std;

//* TILE CLASS ==================================

// ------- CONSTRUCTORS / DESTRUCTORS --------- //

Tile::Tile(int _id, int _state, int _type, Vector2 _pos, Texture2D _tex)
{
    id    = _id;
    state = (TileState) _state;
    type  = (TileType)  _type;
    pos   = _pos;
    tex   = _tex;
    rec   = {pos.x, pos.y, TILE_SIZE, TILE_SIZE};
}


//* TILE MAP CLASS ==============================

// -------- CONSTRUCTORS / DSETRUCTORS ------- //

TileMap::TileMap(string _name) : name(_name) {}
TileMap::~TileMap(){ for(auto it : tiles) delete it; }

// ----------------- METHODS ----------------- //


void TileMap::Init(int mWidth, int mHeight)
{
    width = mWidth;
    height = mHeight;
    /* width = 10;
    height = 10; */
    printf("Init");
    // ---------- LOCAL VARIABLES ------------ //
    int state_tmp(0), type_tmp(0), id_tmp(0);

    // ------ TEXTURES INITIALIZATION -------- //
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 4; j++)
        {
            // Load the whole tilemap into a temporary image.
            Image tmp = LoadImageFromTexture(Resource::GetTexture("./assets/tilemaps/tiles.png"));

            // Crop the image to the desizired size then load it as texture in ground texture array.
            ImageCrop(&tmp, {(float)(j * TILE_SIZE), (float)(i * TILE_SIZE), TILE_SIZE, TILE_SIZE});
            terrain[id_tmp] = LoadTextureFromImage(tmp);

            // Unload temporary image and increment the id iterator.
            UnloadImage(tmp);
            id_tmp++;
        }
    
    id_tmp = 0; // Reset for another usage
    
    // ---------- CREATING MAP DATA ---------- //

    // Load the map file acccording to map name.
    ifstream fs;
    
    
    // Extract the size and the origin for map.
    

    // Parse tiles data.
    for (int i = 0; i < height; i++)
        for (int j = 0; j < width; j++)
        {
            fs >> state_tmp; fs.ignore(1);
            fs >> type_tmp;  fs.ignore(1);

            // Add a new tile to the list.
            tiles.emplace_back(new Tile(id_tmp,
                                        state_tmp,
                                        type_tmp, 
                                        {(float)(origin.x + j * TILE_SIZE), (float)(origin.y + i * TILE_SIZE)},
                                        terrain[type_tmp]));
            id_tmp++;
        }

    fs.close();

    id_tmp = 0; // Reset for another usage.

    // -------- CREATING ENEMY PATH ---------- //

    // Creating a matrix of current tiles for path finding process.
    
}

void TileMap::Draw()
{
    ClearBackground((Color){255,255,255,255});
    // ---------- LOCAL VARIABLES ------------ //
    int id_tmp = 0;

    // --------- DRAW TILE MAP LOOP ---------- //

    for (int i = 0; i < height; i++)
        for (int j = 0; j < width; j++)
        {
            DrawTexturePro(tiles[id_tmp]->tex, 
                          {0,0,TILE_SIZE,TILE_SIZE},
                          {(float)(origin.x + j * TILE_SIZE), (float)(origin.y + i * TILE_SIZE), TILE_SIZE, TILE_SIZE},
                          {0,0}, 0, RAYWHITE);
            DrawRectangleLinesEx({origin.x + j *32,origin.y + i *32,32,32},0.5,GRAY
            
            
            );
            id_tmp++;
        }

    
    //! DEBUG: DRAW enemy PATH
    for (int i = 0; i < (int)enemyPath.size(); i++) DrawLineEx(enemyPath[i], enemyPath[i + 1], 2, RED); 
}