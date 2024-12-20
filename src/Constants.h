#pragma once

#define SCREEN_WIDTH 704
#define SCREEN_HEIGHT 416

constexpr const char* SBM1_PLAYER_TILESET_PATH = "../assets/tilesets/players-tileset.png";
constexpr const char* SMB1_TILESET_PATH = "../assets/tilesets/tiles-2.png";
constexpr const char* SMB1_ENEMIES_TILESET_PATH = "../assets/tilesets/enemies-tileset.png";
constexpr const char* SMB1_OBJECT_TILESET_PATH = "../assets/tilesets/objects-tileset.png";

constexpr const char* FONT_FILE_NAME = "../assets/fonts/SuperMario256.ttf";

constexpr const char* LOADING_SCREEN = "../assets/imgs/Loading_menu.png";
constexpr const char* MAIN_MENU = "../assets/imgs/menu-2.png";
constexpr const char* CLOUD = "../assets/imgs/Clouds.png";
constexpr const char* INSTRUCTION_PANEL = "../assets/imgs/InstructionPanel.png";
constexpr const char* MARIO_MENU = "../assets/imgs/Mario.png";
constexpr const char* RESUMEGAME_PANEL = "../assets/imgs/ResumeGamePanel.png";
constexpr const char* MENU_BACKGROUND = "../assets/imgs/Screen_background.png";
constexpr const char* FRIST_PLACE = "../assets/imgs/1st.png";
constexpr const char* SECOND_PLACE = "../assets/imgs/2nd.png";
constexpr const char* THIRD_PLACE = "../assets/imgs/3rd.png";
constexpr const char* FOURTH_PLACE = "../assets/imgs/4th.png";
constexpr const char* FIFTH_PLACE = "../assets/imgs/5th.png";
constexpr const char* SCOREBOARD_BACKGROUND = "../assets/imgs/BackgroundScoreboard.png";

//button
constexpr const char* BACK_BUTTON = "../assets/imgs/Buttons/BackButton.png";
constexpr const char* EASY_BUTTON = "../assets/imgs/Buttons/EasyButton.png";
constexpr const char* HARD_BUTTON = "../assets/imgs/Buttons/HardButton.png";
constexpr const char* MEDIUM_BUTTON = "../assets/imgs/Buttons/MediumButton.png";
constexpr const char* INSTRUCTION_BUTTON = "../assets/imgs/Buttons/InstructionButton.png";
constexpr const char* LUIGI_BUTTON = "../assets/imgs/Buttons/luigi.png";
constexpr const char* MARIO_BUTTON = "../assets/imgs/Buttons/mario.png";
constexpr const char* YES_BUTTON = "../assets/imgs/Buttons/YesButton.png";
constexpr const char* NO_BUTTON = "../assets/imgs/Buttons/NoButton.png";
constexpr const char* SCOREBOARD_BUTTON = "../assets/imgs/Buttons/ScoreboardButton.png";
constexpr const char* START_GAME_BUTTON = "../assets/imgs/Buttons/StartGameButton.png";
constexpr const char* PAUSE_BUTTON = "../assets/imgs/Buttons/PauseButton.png";
//constexpr const char* RESUME_BUTTON = "../assets/imgs/Buttons/ResumeButton.png";
constexpr const char* HOME_BUTTON = "../assets/imgs/Buttons/HomeButton.png";

//map
constexpr const char* HARD_MAP = "../assets/maps/map_1.tmx";
constexpr const char* MEDIUM_MAP = "../assets/maps/playground_world.tmx";
constexpr const char* EASY_MAP = "../assets/maps/playground_world.tmx";
//......
constexpr bool SECOND_PLAYER = false;

constexpr int GAME_TILE_SIZE = 32;
constexpr int TILE_SIZE = 16;
constexpr int TILE_ROUNDNESS = 4;

constexpr int FPS = 60;
constexpr float MS_PER_UPDATE = 0.01f;

constexpr float GRAVITY = .15f;
constexpr float FRICTION = .94;
constexpr float MAX_SPEED_X = 2.3;
constexpr float MAX_SPEED_Y = 2.75;

constexpr float MARIO_ACCELERATION_X = .08f;
constexpr float MARIO_JUMP_ACCELERATION = 7.0f;
constexpr float MARIO_BOUNCE = 10.0f;

constexpr float MUSHROOM_GROW_SPEED = .25f;
constexpr float MUSHROOM_MOVE_SPEED = 0.8f;