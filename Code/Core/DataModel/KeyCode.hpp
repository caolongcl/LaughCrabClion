#pragma once

#include "SDL_keycode.h"

namespace LaughCrab
{
    typedef enum KeyCode
    {
        eKeyUnknown = SDLK_UNKNOWN,
        eKeyEscape = SDLK_ESCAPE,
        eKeySpace = SDLK_SPACE,
        eKey_0 = SDLK_0,
        eKey_1 = SDLK_1,
        eKey_2 = SDLK_2,
        eKey_3 = SDLK_3,
        eKey_4 = SDLK_4,
        eKey_5 = SDLK_5,
        eKey_6 = SDLK_6,
        eKey_7 = SDLK_7,
        eKey_8 = SDLK_8,
        eKey_9 = SDLK_9,
        eKey_a = SDLK_a,
        eKey_b = SDLK_b,
        eKey_c = SDLK_c,
        eKey_d = SDLK_d,
        eKey_e = SDLK_e,
        eKey_f = SDLK_f,
        eKey_g = SDLK_g,
        eKey_h = SDLK_h,
        eKey_i = SDLK_i,
        eKey_j = SDLK_j,
        eKey_k = SDLK_k,
        eKey_l = SDLK_l,
        eKey_m = SDLK_m,
        eKey_n = SDLK_n,
        eKey_o = SDLK_o,
        eKey_p = SDLK_p,
        eKey_q = SDLK_q,
        eKey_r = SDLK_r,
        eKey_s = SDLK_s,
        eKey_t = SDLK_t,
        eKey_u = SDLK_u,
        eKey_v = SDLK_v,
        eKey_w = SDLK_w,
        eKey_x = SDLK_x,
        eKey_y = SDLK_y,
        eKey_z = SDLK_z,
        eKeyRight = SDLK_RIGHT,
        eKeyLeft = SDLK_LEFT,
        eKeyDownArrow = SDLK_DOWN,
        eKeyUpArrow = SDLK_UP,
    } KeyCode;
}