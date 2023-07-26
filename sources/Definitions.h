#pragma once
#include <SFML/Graphics.hpp>

enum boardTypes { empty, x, o };
enum widgetTypes { gameTotals, turnP1, turnP2 };
enum GameTypes { inProgress, p1Wins, p2Wins, draw };

constexpr const int WIDTH = 800;
constexpr const int HEIGHT = 800;

constexpr const int TEXT_BOX_SIZE_X = 300;
constexpr const int TEXT_BOX_SIZE_Y = 75;

constexpr const int ENTER_BOX_OFFSET = 75;
constexpr const int ENTER_BOX_2_X = WIDTH / 2 + WIDTH / 4;
constexpr const int ACCEPT_OFFSET = 200;

constexpr const int SCORE_Y_POSITION = 112;
constexpr const int PLAYER_Y_POSITION = 200;

constexpr const int xColor_r = 225;
constexpr const int xColor_g = 10;
constexpr const int xColor_b = 90;

constexpr const int oColor_r = 50;
constexpr const int oColor_g = 150;
constexpr const int oColor_b = 225;

constexpr const char* TITLE = "Tic Tac Toe";

constexpr const char* defaultFont = "defaultFont";
constexpr const char* defaultFont_path = "resources/fonts/MilkyNice.ttf";

constexpr const char* icon = "icon";
constexpr const char* icon_path = "resources/Icon.png";

constexpr const char* xPreviewImage = "x_preview_image";
constexpr const char* xPreviewImage_path = "resources/xo/x_preview_image.png";
constexpr const char* oPreviewImage = "o_preview_image";
constexpr const char* oPreviewImage_path = "resources/xo/o_preview_image.png";

constexpr const char* xImage = "x_image";
constexpr const char* xImage_path = "resources/xo/x_image.png";
constexpr const char* oImage = "o_image";
constexpr const char* oImage_path = "resources/xo/o_image.png";