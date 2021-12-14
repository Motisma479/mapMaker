#pragma once

#include <initializer_list>
#include <unordered_map>
#include <vector>

#include "tilemap_editor.hpp"

#define MAX_UI_TEX  20

#define MAX_UI_SFX  2

// Forwards declaration.
class Game;

// Structures and enumeration.
struct Animation
{ int key; int end; };

enum class SceneId
{ INTRO, MAIN_MENU, SELECT_MENU, LOADING, IN_GAME };

class Button
{
public:
    // Attributes.
    bool      isClickable;
    bool      isActive;
    bool      displayTexture;
    int       fontSize;
    string    text;
    Color     textColor;
    Rectangle rec;
    Texture2D tex;
    Font      font;

    // Constructors / destructors.
    Button();
    Button(Rectangle _rec, Texture2D _tex);
    Button(int _fs, string _text, Color _tc, Rectangle _rec, Texture2D _tex, Font _font);
    ~Button() {}

    // Methods.
    bool IsHovered();
    bool IsClicked();
    void Draw();
};


class FileData
{
public:
    Rectangle textBox = {0, 0, 225, 50};
    bool canWriteInBox = false;
    char name[9 + 1] = "\0"; // NOTE: One extra space required for null terminator char '\0'
    int letterCount = 0;

    int width = 14;
    int height = 12;
    bool saveTryEmpty = false;
    bool saveTryIncorect = false;
};

class TilePaint
{
public:
  // Attributes.
  bool      isClickable;
  bool      displayTexture;
  int       tilesize;
  Rectangle rec;
  Texture2D tileTexture;
  vector<Rectangle> tileList;
  vector<Vector2> originalPostion;

  // Constructors / destructors.
  TilePaint();
  TilePaint(Rectangle _rec, Texture2D _tex, int sizeOfTile);
  ~TilePaint() {}

  // Methods.
  bool IsHovered();
  bool IsRClicked();

  bool IsLClicked();
  void Draw();
};

class Ui
{
public:
    // Main attributes.
    bool hasPutInformation = false;
    FileData fileData;

    int  selectedTool = 0; // 0 = nothing, 1 = pencil, 2 = eraser, 3 = flag;
    int  onRightClick = 0;
    int  onLeftClick  = 0;

    bool             mIsCameraOut;
    bool             mHudIsActive;
    bool             mUiHovered;
    SceneId          mSId;
    struct Animation aIntro;
    Camera2D         mInGameCamera;
    Texture2D        mUiTexture[MAX_UI_TEX];
    Sound            mUiSfx[MAX_UI_SFX];
    Font             mUiFont;
    Game&            mGameRef;
    Vector2          mouseWorldPosition;

    // Constructors / destructors.
    Ui(Game& game);

    // Intro attributes and methods.
    void DrawIntro();

    // Menu.
    void DrawMainMenu();
    void DrawEditorMenu();

    // In game.
    void DrawHUD();
    void DrawInGame();

    // Global methods.
    void Init();
    void LoadLevel();
    void DrawCursor();
    void DrawOverlay();
    void DrawRender();
    void IsCameraOut();
    void Update();
};