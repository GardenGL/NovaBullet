#ifndef WINDOW_EVENTS_H_
#define WINDOW_EVENTS_H_

#include "Window.hpp"

namespace Inputs
{

    inline bool *_keys;
    inline unsigned int *_frames;
    inline unsigned int _current = 1;

    inline float x = 0.0f;
    inline float y = 0.0f;
    
    inline float deltaX = 0.0f;
    inline float deltaY = 0.0f;

    inline bool _cursor_locked = false;
    inline bool _cursor_started = false;

    int initialize();
    void terminate();
    void pullEvents();
    
    bool IsKeyDown(int keycode);
    bool IsKeyPressed(int keycode);
    bool IsKeyReleased(int keycode);

    void toggleCursor();
    void SetCursorMode(bool mode);
    void setCursorPos(float width, float height);
};

namespace Inputs
{
    inline int KEY_NULL = 0;
    // Alphanumeric keys
    inline int KEY_APOSTROPHE = 39;
    inline int KEY_COMMA = 44;
    inline int KEY_MINUS = 45;
    inline int KEY_PERIOD = 46;
    inline int KEY_SLASH = 47;
    inline int KEY_ZERO = 48;
    inline int KEY_ONE = 49;
    inline int KEY_TWO = 50;
    inline int KEY_THREE = 51;
    inline int KEY_FOUR = 52;
    inline int KEY_FIVE = 53;
    inline int KEY_SIX = 54;
    inline int KEY_SEVEN = 55;
    inline int KEY_EIGHT = 56;
    inline int KEY_NINE = 57;
    inline int KEY_SEMICOLON = 59;
    inline int KEY_EQUAL = 61;
    inline int KEY_A = 65;
    inline int KEY_B = 66;
    inline int KEY_C = 67;
    inline int KEY_D = 68;
    inline int KEY_E = 69;
    inline int KEY_F = 70;
    inline int KEY_G = 71;
    inline int KEY_H = 72;
    inline int KEY_I = 73;
    inline int KEY_J = 74;
    inline int KEY_K = 75;
    inline int KEY_L = 76;
    inline int KEY_M = 77;
    inline int KEY_N = 78;
    inline int KEY_O = 79;
    inline int KEY_P = 80;
    inline int KEY_Q = 81;
    inline int KEY_R = 82;
    inline int KEY_S = 83;
    inline int KEY_T = 84;
    inline int KEY_U = 85;
    inline int KEY_V = 86;
    inline int KEY_W = 87;
    inline int KEY_X = 88;
    inline int KEY_Y = 89;
    inline int KEY_Z = 90;

    // Function keys
    inline int KEY_SPACE = 32;
    inline int KEY_ESCAPE = 256;
    inline int KEY_ENTER = 257;
    inline int KEY_TAB = 258;
    inline int KEY_BACKSPACE = 259;
    inline int KEY_INSERT = 260;
    inline int KEY_DELETE = 261;
    inline int KEY_RIGHT = 262;
    inline int KEY_LEFT = 263;
    inline int KEY_DOWN = 264;
    inline int KEY_UP = 265;
    inline int KEY_PAGE_UP = 266;
    inline int KEY_PAGE_DOWN = 267;
    inline int KEY_HOME = 268;
    inline int KEY_END = 269;
    inline int KEY_CAPS_LOCK = 280;
    inline int KEY_SCROLL_LOCK = 281;
    inline int KEY_NUM_LOCK = 282;
    inline int KEY_PRINT_SCREEN = 283;
    inline int KEY_PAUSE = 284;
    inline int KEY_F1 = 290;
    inline int KEY_F2 = 291;
    inline int KEY_F3 = 292;
    inline int KEY_F4 = 293;
    inline int KEY_F5 = 294;
    inline int KEY_F6 = 295;
    inline int KEY_F7 = 296;
    inline int KEY_F8 = 297;
    inline int KEY_F9 = 298;
    inline int KEY_F10 = 299;
    inline int KEY_F11 = 300;
    inline int KEY_F12 = 301;
    inline int KEY_LEFT_SHIFT = 340;
    inline int KEY_LEFT_CONTROL = 341;
    inline int KEY_LEFT_ALT = 342;
    inline int KEY_LEFT_SUPER = 343;
    inline int KEY_RIGHT_SHIFT = 344;
    inline int KEY_RIGHT_CONTROL = 345;
    inline int KEY_RIGHT_ALT = 346;
    inline int KEY_RIGHT_SUPER = 347;
    inline int KEY_KB_MENU = 348;
    inline int KEY_LEFT_BRACKET = 91;
    inline int KEY_BACKSLASH = 92;
    inline int KEY_RIGHT_BRACKET = 93;
    inline int KEY_GRAVE = 96;

    // Keypad keys
    inline int KEY_KP_0 = 320;
    inline int KEY_KP_1 = 321;
    inline int KEY_KP_2 = 322;
    inline int KEY_KP_3 = 323;
    inline int KEY_KP_4 = 324;
    inline int KEY_KP_5 = 325;
    inline int KEY_KP_6 = 326;
    inline int KEY_KP_7 = 327;
    inline int KEY_KP_8 = 328;
    inline int KEY_KP_9 = 329;
    inline int KEY_KP_DECIMAL = 330;
    inline int KEY_KP_DIVIDE = 331;
    inline int KEY_KP_MULTIPLY = 332;
    inline int KEY_KP_SUBTRACT = 333;
    inline int KEY_KP_ADD = 334;
    inline int KEY_KP_ENTER = 335;
    inline int KEY_KP_EQUAL = 336;
    // Android key buttons
    inline int KEY_BACK = 4;
    inline int KEY_MENU = 82;
    inline int KEY_VOLUME_UP = 24;
    inline int KEY_VOLUME_DOWN = 25;

    // Mouse buttons
    inline int MOUSE_BUTTON_LEFT = 1024;
    inline int MOUSE_BUTTON_RIGHT = 1025;
    inline int MOUSE_BUTTON_MIDDLE = 1026;
    inline int MOUSE_BUTTON_SIDE = 1027;
    inline int MOUSE_BUTTON_EXTRA = 1028;
    inline int MOUSE_BUTTON_FORWARD = 1029;
    inline int MOUSE_BUTTON_BACK = 1030;
    inline int MOUSE_BUTTON_MAX = 1031;
}

#endif /* WINDOW_EVENTS_H_ */