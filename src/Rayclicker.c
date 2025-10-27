/*******************************************************************************************
*
*   Rayclicker v1.0.0 - Autoclicker with raygui
*
*   LICENSE: Propietary License
*
*   Copyright (c) 2022 . All Rights Reserved.
*
*   Unauthorized copying of this file, via any medium is strictly prohibited
*   This project is proprietary and confidential unless the owner allows
*   usage in any other form by expresely written permission.
*
**********************************************************************************************/

#include "raylib.h"

#define RAYGUI_IMPLEMENTATION
#include "raygui.h"

//----------------------------------------------------------------------------------
// Controls Functions Declaration
//----------------------------------------------------------------------------------


//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main()
{
    // Initialization
    //---------------------------------------------------------------------------------------
    int screenWidth = 800;
    int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "Rayclicker");

    // Rayclicker: controls initialization
    //----------------------------------------------------------------------------------
    // Define controls variables
    bool WindowBox000Active = true;            // WindowBox: WindowBox000
    bool TextBox001EditMode = false;
    char TextBox001Text[128] = "Mins";            // TextBox: TextBox001
    bool Toggle003Active = true;            // Toggle: Toggle003
    bool TextBox004EditMode = false;
    char TextBox004Text[128] = "Seconds";            // TextBox: TextBox004
    bool TextBox005EditMode = false;
    char TextBox005Text[128] = "Ms";            // TextBox: TextBox005
    bool TextBox007EditMode = false;
    char TextBox007Text[128] = "+- Ms";            // TextBox: TextBox007
    bool TextBox010EditMode = false;
    char TextBox010Text[128] = "0";            // TextBox: TextBox010
    bool TextBox012EditMode = false;
    char TextBox012Text[128] = "Mins";            // TextBox: TextBox012
    bool TextBox013EditMode = false;
    char TextBox013Text[128] = "Seconds";            // TextBox: TextBox013
    bool TextBox014EditMode = false;
    char TextBox014Text[128] = "Ms";            // TextBox: TextBox014

    // Define controls rectangles
    Rectangle layoutRecs[14] = {
        (Rectangle){ 288, 120, 488, 312 },    // WindowBox: WindowBox000
        (Rectangle){ 312, 168, 64, 24 },    // TextBox: TextBox001
        (Rectangle){ 312, 144, 120, 24 },    // Label: Label002
        (Rectangle){ 312, 216, 88, 24 },    // Toggle: Toggle003
        (Rectangle){ 376, 168, 64, 24 },    // TextBox: TextBox004
        (Rectangle){ 440, 168, 40, 24 },    // TextBox: TextBox005
        (Rectangle){ 552, 144, 120, 24 },    // Label: Label006
        (Rectangle){ 552, 168, 120, 24 },    // TextBox: TextBox007
        (Rectangle){ 312, 288, 120, 24 },    // Label: Label009
        (Rectangle){ 312, 312, 120, 24 },    // TextBox: TextBox010
        (Rectangle){ 552, 216, 120, 24 },    // Label: Label011
        (Rectangle){ 552, 240, 64, 24 },    // TextBox: TextBox012
        (Rectangle){ 616, 240, 64, 24 },    // TextBox: TextBox013
        (Rectangle){ 680, 240, 40, 24 },    // TextBox: TextBox014
    };
    //----------------------------------------------------------------------------------

    SetTargetFPS(60);
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        // TODO: Implement required update logic
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(GetColor(GuiGetStyle(DEFAULT, BACKGROUND_COLOR))); 

            // raygui: controls drawing
            //----------------------------------------------------------------------------------
            // Draw controls
            if (WindowBox000Active)
            {
                WindowBox000Active = !GuiWindowBox(layoutRecs[0], "4Fun Auto clicker");
                if (GuiTextBox(layoutRecs[1], TextBox001Text, 128, TextBox001EditMode)) TextBox001EditMode = !TextBox001EditMode;
                GuiLabel(layoutRecs[2], "Interval");
                GuiToggle(layoutRecs[3], "Start", &Toggle003Active);
                if (GuiTextBox(layoutRecs[4], TextBox004Text, 128, TextBox004EditMode)) TextBox004EditMode = !TextBox004EditMode;
                if (GuiTextBox(layoutRecs[5], TextBox005Text, 128, TextBox005EditMode)) TextBox005EditMode = !TextBox005EditMode;
                GuiLabel(layoutRecs[6], "Random delay");
                if (GuiTextBox(layoutRecs[7], TextBox007Text, 128, TextBox007EditMode)) TextBox007EditMode = !TextBox007EditMode;
                GuiLabel(layoutRecs[8], "Stop after X clicks");
                if (GuiTextBox(layoutRecs[9], TextBox010Text, 128, TextBox010EditMode)) TextBox010EditMode = !TextBox010EditMode;
                GuiLabel(layoutRecs[10], "Start Delay");
                if (GuiTextBox(layoutRecs[11], TextBox012Text, 128, TextBox012EditMode)) TextBox012EditMode = !TextBox012EditMode;
                if (GuiTextBox(layoutRecs[12], TextBox013Text, 128, TextBox013EditMode)) TextBox013EditMode = !TextBox013EditMode;
                if (GuiTextBox(layoutRecs[13], TextBox014Text, 128, TextBox014EditMode)) TextBox014EditMode = !TextBox014EditMode;
            }
            //----------------------------------------------------------------------------------

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}

//------------------------------------------------------------------------------------
// Controls Functions Definitions (local)
//------------------------------------------------------------------------------------

