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

//TileMap::TileMap(string _name) : name(_name) {}
TileMap::~TileMap(){ for(auto it : tiles) delete it; }

// ----------------- METHODS ----------------- //


void TileMap::Init(int mWidth, int mHeight ,int textureWidth, int textureHeight,const string &fileName )
{
    width = mWidth;
    height = mHeight;
    name= fileName;
    /* width = 10;
    height = 10; */
    printf("Init");
    // ---------- LOCAL VARIABLES ------------ //
    int state_tmp(1), type_tmp(0), id_tmp(0);

    // ------ TEXTURES INITIALIZATION -------- //
    for (int i = 0; i < 7; i++)
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
void TileMap::Update(int toolState, float zoom, float camX, float camY, int RClick, int LClick)
{
    // cout<<"camX ="<<camX<<"camY ="<<camY<<endl;
    // cout << (GetMousePosition().x )/zoom << endl;
    // if (camX <=0 )
    // {
    //     camX = -1;
    // }
    //  if (camY <=0 )
    // {
    //     camY = -1;
    // }
    
    if (toolState == 1)
    {
        if(!IsMouseButtonUp(MOUSE_LEFT_BUTTON)){
            for (int i = 0; i < width*height; i++)
            {
                if(CheckCollisionPointRec({(GetMousePosition().x -camX)/zoom,(GetMousePosition().y-camY)/zoom },tiles[i]->rec)){
                    //DrawCircle(tiles[i]->rec.x,tiles[i]->rec.y,5,RED);
                    //DrawRectanglePro(tiles[i]->rec,{0,0},0,RED);
                    tiles[i]->type = (TileType)LClick;
                    tiles[i]->tex = terrain[LClick];
                    tiles[i]->Update();
                    //tiles[i].

                }
            }
        }else if(!IsMouseButtonUp(MOUSE_RIGHT_BUTTON)){
            for (int i = 0; i < width*height; i++)
            {
                if(CheckCollisionPointRec({(GetMousePosition().x -camX)/zoom,(GetMousePosition().y-camY)/zoom},tiles[i]->rec)){
                    //DrawCircle(tiles[i]->rec.x,tiles[i]->rec.y,5,RED);
                    //DrawRectanglePro(tiles[i]->rec,{0,0},0,BLUE);
                    tiles[i]->type = (TileType)RClick;
                    tiles[i]->tex = terrain[RClick];
                    tiles[i]->Update();
                }
            }
        }
    }
    if (toolState == 2)
    {
        if(!IsMouseButtonUp(MOUSE_LEFT_BUTTON)){
            for (int i = 0; i < width*height; i++)
            {
                if(CheckCollisionPointRec({(GetMousePosition().x -camX)/zoom,(GetMousePosition().y-camY)/zoom},tiles[i]->rec)){
                    //DrawCircle(tiles[i]->rec.x,tiles[i]->rec.y,5,RED);
                    //DrawRectanglePro(tiles[i]->rec,{0,0},0,RED);
                    tiles[i]->type = (TileType)0;
                    tiles[i]->tex = terrain[0];
                    tiles[i]->Update();
                    //tiles[i].

                }
            }
        }else if(!IsMouseButtonUp(MOUSE_RIGHT_BUTTON)){
            for (int i = 0; i < width*height; i++)
            {
                if(CheckCollisionPointRec({(GetMousePosition().x -camX)/zoom,(GetMousePosition().y-camY)/zoom},tiles[i]->rec)){
                    //DrawCircle(tiles[i]->rec.x,tiles[i]->rec.y,5,RED);
                    //DrawRectanglePro(tiles[i]->rec,{0,0},0,BLUE);
                    tiles[i]->type = (TileType)RClick;
                    tiles[i]->tex = terrain[RClick];
                    tiles[i]->Update();
                }
            }
        }
    }
    if (toolState == 3)
    {
        if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
            for (int i = 0; i < width*height; i++)
            {
                if(CheckCollisionPointRec({(GetMousePosition().x -camX)/zoom,(GetMousePosition().y-camY)/zoom},tiles[i]->rec)){
                    if (tiles[i]->state == (TileState)3)
                    {
                        tiles[i]->state = (TileState) 4;
                        for (int k = 0; k < height*width; k++)
                        {
                            if (k != i && tiles[k]->state == (TileState) 4)
                            {
                               tiles[k]->state = (TileState) 3;
                            }
                            
                        }
                        
                    }

                }
            }
        }else if(IsMouseButtonPressed(MOUSE_RIGHT_BUTTON)){
            for (int i = 0; i < width*height; i++)
            {
                if(CheckCollisionPointRec({(GetMousePosition().x -camX)/zoom,(GetMousePosition().y-camY)/zoom},tiles[i]->rec)){
                    if (tiles[i]->state == (TileState)3)
                    {
                        tiles[i]->state = (TileState) 5;
                        for (int k = 0; k < height*width; k++)
                        {
                            if (k != i && tiles[k]->state == (TileState) 5)
                            {
                               tiles[k]->state = (TileState) 3;
                            }
                            
                        }
                    }
                }
            }
        }
    }
}
void Tile::Update(){
    switch (type)
    {
    case (TileType)1:
        state = (TileState)3;
        break;
    case (TileType)2:
        state = (TileState)3;
        break;
    case (TileType)3:
        state = (TileState)3;
        break;
    case (TileType)4:
        state = (TileState)3;
        break;
    case (TileType)5:
        state = (TileState)3;
        break;
    case (TileType)6:
        state = (TileState)3;
        break;
    case (TileType)7:
        state = (TileState)3;
        break;
    case (TileType)11:
        state = (TileState)3;
        break;
    case (TileType)15:
        state = (TileState)3;
        break;
    case (TileType)19:
        state = (TileState)3;
        break;
    case (TileType)22:
        state = (TileState)3;
        break;
    case (TileType)23:
        state = (TileState)3;
        break;
    case (TileType)26:
        state = (TileState)3;
        break;
    case (TileType)27:
        state = (TileState)3;
        break;
    
    
    default:
        state = (TileState)1;
        break;
    }
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
            if (tiles[id_tmp]->state == (TileState)4)
            {
                DrawRectanglePro({(float)(origin.x + j * TILE_SIZE), (float)(origin.y + i * TILE_SIZE), TILE_SIZE, TILE_SIZE},
                          {0,0}, 0, {0,0,255,50});
            }
            if (tiles[id_tmp]->state == (TileState)5)
            {
                DrawRectanglePro({(float)(origin.x + j * TILE_SIZE), (float)(origin.y + i * TILE_SIZE), TILE_SIZE, TILE_SIZE},
                          {0,0}, 0, {255,0,0,50});
            }
            
            DrawRectangleLinesEx({origin.x + j *32,origin.y + i *32,32,32},0.5,GRAY);
            id_tmp++;
        }

}

void TileMap::Save()
{
    string imageName = {"./levels/"+name+".png"};
    TakeScreenshot(imageName.c_str());
    //name = "TEST";
    int state_tmp(0), type_tmp(0), id_tmp(0);
    // Load the map file acccording to map name.
    string path = {"./levels/" + name + ".map"};
    ofstream fs{path.c_str()};
    
    if(fs.is_open())
    {
        fs << width;
        fs<<" ";
        fs << height;
        fs<<std::endl;
        for (int i = 0; i < height; i++){
        for (int j = 0; j < width; j++)
        {

            state_tmp = (int)tiles[id_tmp]->state;
            type_tmp = (int)tiles[id_tmp]->type;

            fs << state_tmp; fs<<":";
            fs << type_tmp;
            if (j+1 < width)
            {
                  fs<<",";
            }
            
            id_tmp++;
        }
        fs<<std::endl;
    }
    
    }
    else{
        cout<<("ERROR")<<endl;
    }
    fs.close();
    // Parse tiles data.
    

    

    id_tmp = 0; // Reset for another usage.

}