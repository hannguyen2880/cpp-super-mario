/*******************************************************************************************
*
*   raygui v3.2 - A simple and easy-to-use immediate-mode gui library
*
*   DESCRIPTION:
*       raygui is a simple and easy-to-use tools library to draw immediate-mode graphical
*       user interface elements with raylib.
*
*   LICENSE: zlib/libpng
*
*   raygui is licensed under an unmodified zlib/libpng license, which is an OSI-certified,
*   BSD-like license that allows static linking with closed source software:
*
*   This software is provided "as-is", without any express or implied warranty. In no event
*   will the authors be held liable for any damages arising from the use of this software.
*
*   Permission is granted to anyone to use this software for any purpose, including commercial
*   applications, and to alter it and redistribute it freely, subject to the following
*   restrictions:
*
*     1. The origin of this software must not be misrepresented; you must not claim that you
*        wrote the original software. If you use this software in a product, an acknowledgment
*        in the product documentation would be appreciated but is not required.
*     2. Altered source versions must be plainly marked as such, and must not be misrepresented
*        as being the original software.
*     3. This notice may not be removed or altered from any source distribution.
*
**********************************************************************************************/

#include "raygui.h"
#include <stdlib.h>  // Thêm tệp tiêu đề này để sử dụng strtof và NULL

// Định nghĩa hàm TextToFloat
float TextToFloat(const char *text) {
    return strtof(text, NULL);
}

//----------------------------------------------------------------------------------
// Defines and Macros
//----------------------------------------------------------------------------------
//...

//----------------------------------------------------------------------------------
// Global Variables Definition
//----------------------------------------------------------------------------------
#define RAYGUI_IMPLEMENTATION
#include "raygui.h"

//----------------------------------------------------------------------------------
// Module specific Functions Declaration
//----------------------------------------------------------------------------------
//...

//----------------------------------------------------------------------------------
// Module Functions Definition
//----------------------------------------------------------------------------------
//...
