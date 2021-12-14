#pragma once

#include <vector>
#include <string>

#include "raylib.h"

#define TILE_SIZE 32
#define MAX_TILE 28

using namespace std;

class Ui;

enum class TileState
{
    VOID,    // 0: Void tile
    FREE,    // 1: Free
    OCPD,    // 2: Occupied
    ENMY,    // 3: Enemy path
    S_ENMY,  // 4: Enemy starting tile
    E_ENMY   // 5: Enemy ending tile
};

enum class TileType
{
    PLAINS_GRASS,       // 0:  Plains grass                  
    PLAINS_V_PATH,      // 1:  Plains vertical path       
    PLAINS_H_PATH,      // 2:  Plains horizontal path    
    PLAINS_C_ROAD,      // 3:  Plains crossroad              
    PLAINS_TR_CORNER,   // 4:  Plains right-down path        
    PLAINS_TL_CORNER,   // 5:  Plains left-down path         
    PLAINS_BR_CORNER,   // 6:  Plains left-up path          
    PLAINS_BL_CORNER,   // 7:  Plains right-up path     
    COBBLE_TL_CORNER,   // 8:  Cobble top-left corner
    COBBLE_T_CORNER,    // 9:  Cobble top corner
    COBBLE_TR_CORNER,   // 10: Cobble top-right corner
    DUNGEON_V_PATH,     // 11: Dungeon vertical path
    COBBLE_L_CORNER,    // 12: Cobble left corner
    COBBLE_PATH,        // 13: Cobble path
    COBBLE_R_CORNER,    // 14: Cobble right corner
    DUNGEON_H_PATH,     // 15: Dungeon horizontal path
    COBBLE_BL_CORNER,   // 16: Cobble bottom-left corner
    COBBLE_B_CORNER,    // 17: Cobble bottom corner
    COBBLE_BR_CORNER,   // 18: Cobble bottom-right corner
    DUNGEON_C_ROAD,     // 19: Dungeon crossroad
    COBBLE_TL_INNER,    // 20: Cobble top-left inner
    COBBLE_TR_INNER,    // 21: Cobble top-right inner
    DUNGEON_TL_CORNER,  // 22: Dungeon top-left corner
    DUNGEON_TR_CORNER,  // 23: Dungeon top-right corner
    COBBLE_BL_INNER,    // 24: Cobble left inner
    COBBLE_BR_INNER,    // 25: Cobble right inner
    DUNGEON_BL_CORNER,  // 26: Dungeon top-left corner
    DUNGEON_BR_CORNER,  // 27: Dungeon top-right corner
    VOID                // Void tile
};

class Tile
{
public:
    // Attributes.
    int       mId;
    TileState mState;
    TileType  mType;
    Vector2   mPos;
    Texture2D mTex;
    Rectangle mRec;

    // Constructors / Destructors.
    Tile() {}
    Tile(int _id, int _state, int _type, Vector2 _pos, Texture2D _tex);
    ~Tile() {}

    // Methods.
    void Init();
    void Update();
    void Draw();
};

class TileMapEditor
{
public:
    // Attributes.
    bool            mStart;
    bool            mEnd;
    int             mWidth;
    int             mHeight;
    int             mErrorCounter;
    string          mName;
    Texture2D       mTerrain[MAX_TILE];
    vector<Tile*>   mTiles;
    vector<Vector2> mEnemyPath;
   

    // Constructors / Destructors.
    TileMapEditor();
    ~TileMapEditor();

    // Methods.
    void Init(int mWidth, int mHeight,int textureWidth, int textureHeight, const string &fileName);
    void Update(int toolState, int RClick, int LClick, Camera2D& cam);
    void Draw();
    void Save();         
};