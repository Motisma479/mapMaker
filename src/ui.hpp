#pragma once

#include <initializer_list>
#include <unordered_map>
#include <vector>

#include "tilemap.hpp"

#define MAX_UI_TEX  20

#define MAX_UI_SFX  2
#define MAX_UI_FONT 1

// Forwards declaration.
class Player;
class Game;

// Structures and enumeration.
struct Animation
{ int key; int end; };

enum class SceneId
{ INTRO, MAIN_MENU, SELECT_MENU, LOADING, IN_GAME };

enum class CursorState
{ NORMAL, POINTING, GRABBING };

// Classes.
class LevelContainer
{
public:
    // Attributes.
    string      txt;
    Rectangle   rec;
    Texture2D   tex;
    Font        fnt;

    // Constructors / destructors.
    LevelContainer() {}
    LevelContainer(string _txt, Rectangle _rec, Texture2D _tex, Font _fnt);
    ~LevelContainer() {}

    // Methods.
    bool IsHovered(CursorState& state);
    bool IsClicked(CursorState& state);
    void Update();
    void Display(CursorState& state, float scroller);
};

class Button
{
public:
    // Attributes.
    bool      isClickable;
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
    bool IsHovered(CursorState& state);
    bool IsClicked(CursorState& state);
    void Draw(CursorState& state);
};


class FileData
  {
  public:
    Rectangle textBox = {0, 0, 225, 50};
    bool canWriteInBox = false;
    char name[9 + 1] = "\0"; // NOTE: One extra space required for null terminator char '\0'
    int letterCount = 0;

    int width = 10;
    int height = 10;
    bool saveTryEmpty = false;
    bool saveTryIncorect = false;
  };

class TexturedButton
  {
public:
  // Attributes.
    bool      isClickable;
    bool      displayTexture;
    bool isActive = false;
    Rectangle rec;

    Texture2D buttonTexture;


    // Constructors / destructors.
    TexturedButton();
    TexturedButton(Rectangle _rec, Texture2D _tex);
    ~TexturedButton() {}

    // Methods.
    bool IsHovered(CursorState& state);
    bool IsClicked(CursorState& state);
    void Draw(CursorState& state);
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
  bool IsHovered(CursorState& state);
  bool IsRClicked(CursorState& state);

  bool IsLClicked(CursorState& state);
  void Draw(CursorState& state);
};

class Ui //TODO: Fix multi res
{
public:
    // Main attributes.
    bool hasPutInformation = false;
    FileData fileData;

    int selectedTool = 0; // 0 = nothing, 1 = pencil, 2 = eraser, 3 = flag;
    bool      uiHovered = false;
    int       onRightClick =0;
    int       onLeftClick =0;
    bool      hudIsActive = true;


    float                            scroller               = 0.0f;
    float                            renderScale            = 1.0f;
    SceneId                          sId                    = SceneId::INTRO;
    struct Animation                 aIntro                 = {0, 450};
    CursorState                      cState                 = CursorState::NORMAL;
    RenderTexture2D                  gameRenderTexture;
    Camera2D                         inGameCamera           = {{0,0}, {0,0}, 0, 1};
    Texture2D                        uiTexture[MAX_UI_TEX];
    Sound                            uiSfx[MAX_UI_SFX];
    Font                             uiFont[MAX_UI_FONT];
    vector<LevelContainer>           levelsContainers;
    unordered_map<string, Texture2D> levelsMetadata;
    Game&                            gameRef;
    Vector2 mouseWorldPosition;

    // Constructors / destructors.
    Ui(Game& game);

    // Intro attributes and methods.
    void DrawIntro();

    // Menu.
    void DrawMainMenu();
    void DrawSelectMenu();

    // In game.
    //TODO: BUILD MODE (Colored filter according to tiles state)
    void DrawHUD(Player player);
    void DrawInGame();

    // Global methods.
    void Init();
    void LoadLevel();
    void Update();
    void DrawCursor();
    void DrawOverlay(Player player);
    void DrawRender(Player player);
};