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
#define RAYGUI_IMPLEMENTATION
#include "raygui.h"
#include "raylib.h"
#include "utils.h"

#define TEXT_SIZE 128
#define SCREEN_WIDTH 545
#define SCREEN_HEIGHT 260

//----------------------------------------------------------------------------------
// Structures
//----------------------------------------------------------------------------------

typedef struct _InputBox_
{
    char Text[TEXT_SIZE];
    bool EditMode;
    Rectangle Rect;
} InputBox, *pInputBox;

typedef struct _State
{
    bool MainToggleActive;
    double lastClickTime;
    int clickCount;
    long clickIntervalMs; // Cached interval in milliseconds
} State, *pState;

//----------------------------------------------------------------------------------
// Globals
//----------------------------------------------------------------------------------

InputBox MinInputBox = {.EditMode = false,
                        .Text = "Mins",
                        .Rect = {80, 72, 64, 24}};

InputBox SecondsInputBox = {.EditMode = false,
                            .Text = "Seconds",
                            .Rect = {144, 72, 84, 24}};


InputBox MsInputBox = {.EditMode = false,
                       .Text = "Ms",
                       .Rect = {228, 72, 60, 24}};

InputBox DelayRandomMsInputBox = {.EditMode = false,
                                  .Text = "+- Ms",
                                  .Rect = {320, 72, 120, 24}};

InputBox StopAfterClickInputBox = {.EditMode = false,
                                   .Text = "0",
                                   .Rect = {80, 216, 120, 24}};

InputBox DelayMinsInputBox = {.EditMode = false,
                              .Text = "Mins",
                              .Rect = {320, 144, 64, 24}};

InputBox DelaySecondsInputBox = {.EditMode = false,
                                 .Text = "Seconds",
                                 .Rect = {384, 144, 84, 24}};

InputBox DelayMsInputBox = {.EditMode = false,
                            .Text = "Ms",
                            .Rect = {468, 144, 40, 24}};

// Define controls rectangles
Rectangle layoutRecs[5] = {
    (Rectangle) {80, 48, 120, 24},   // Label: Label002
    (Rectangle) {80, 120, 88, 24},   // Toggle: Toggle003
    (Rectangle) {320, 48, 120, 24},  // Label: Label006
    (Rectangle) {80, 192, 180, 24},  // Label: Label009
    (Rectangle) {320, 120, 120, 24}, // Label: Label011
};

State state = {.MainToggleActive = false, .clickCount = 0, .lastClickTime = 0.0, .clickIntervalMs = 100};

void Init()
{
    int screenWidth = SCREEN_WIDTH;
    int screenHeight = SCREEN_HEIGHT;
    SetConfigFlags(FLAG_WINDOW_HIGHDPI | FLAG_MSAA_4X_HINT | FLAG_VSYNC_HINT);
    InitWindow(screenWidth, screenHeight, "Rayclicker");
    GuiLoadStyle("../resources/style_jungle.rgs");
    GuiSetStyle(DEFAULT, TEXT_SIZE, 15);
}

void AutoclickLoop()
{
    double currentTime = GetTime();
    double interval = state.clickIntervalMs / 1000.0; // Convert to seconds

    if (currentTime - state.lastClickTime >= interval)
    {
        SimulateMouseClick();
        state.clickCount++;
        state.lastClickTime = currentTime;
        TraceLog(LOG_INFO, "Click #%d performed at %.2f seconds", state.clickCount, currentTime);

        // Check if we should stop after X clicks
        long maxClicks = 0;
        if (isGetNumber(StopAfterClickInputBox.Text, &maxClicks) && maxClicks > 0)
        {
            if (state.clickCount >= maxClicks)
            {
                state.MainToggleActive = false;
                TraceLog(LOG_INFO, "Stopped after %d clicks", state.clickCount);
            }
        }
    }
}

void MsTextBoxHandler()
{
    TraceLog(LOG_INFO, "New ms text %s", MsInputBox.Text);
    MsInputBox.EditMode = !MsInputBox.EditMode;

    // Update cached interval when text box is edited
    if (isGetNumber(MsInputBox.Text, &state.clickIntervalMs))
    {
        TraceLog(LOG_INFO, "Interval updated to %ld ms", state.clickIntervalMs);
    }
    else
    {
        state.clickIntervalMs = 100; // Reset to default if invalid
    }
}

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main()
{
    Init();
    SetTargetFPS(60);

    // Main game loop
    while (!WindowShouldClose()) // Detect window close button or ESC key
    {
        // Auto-clicking logic
        if (state.MainToggleActive)
        {
            AutoclickLoop();
        }
        //----------------------------------------------------------------------------------
        if (IsWindowResized())
        {
            TraceLog(LOG_INFO, "Updated size width=%d, height=%d", GetScreenWidth(), GetScreenHeight());
        }
        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

        ClearBackground(GetColor(GuiGetStyle(DEFAULT, BACKGROUND_COLOR)));

        // raygui: controls drawing
        //----------------------------------------------------------------------------------
        // Draw controls
        if (GuiTextBox(MinInputBox.Rect, MinInputBox.Text, TEXT_SIZE, MinInputBox.EditMode))
        {
            MinInputBox.EditMode = !MinInputBox.EditMode;
        }

        GuiLabel(layoutRecs[0], "Interval");
        if (GuiButton(layoutRecs[1], state.MainToggleActive ? "Stop" : "Start"))
        {
            state.MainToggleActive = !state.MainToggleActive;
            if (state.MainToggleActive)
            {
                TraceLog(LOG_INFO, "Auto-clicker started!");
                state.lastClickTime = GetTime();
                state.clickCount = 0;
            }
            else
            {
                TraceLog(LOG_INFO, "Auto-clicker stopped. Total clicks: %d", state.clickCount);
            }
        }

        if (GuiTextBox(SecondsInputBox.Rect, SecondsInputBox.Text, TEXT_SIZE, SecondsInputBox.EditMode))
        {
            SecondsInputBox.EditMode = !SecondsInputBox.EditMode;
        }
        if (GuiTextBox(MsInputBox.Rect, MsInputBox.Text, TEXT_SIZE, MsInputBox.EditMode))
        {
            MsTextBoxHandler();
        }
        GuiLabel(layoutRecs[2], "Random delay");
        if (GuiTextBox(DelayRandomMsInputBox.Rect, DelayRandomMsInputBox.Text, TEXT_SIZE, DelayRandomMsInputBox.EditMode))
        {
            DelayRandomMsInputBox.EditMode = !DelayRandomMsInputBox.EditMode;
        }
        GuiLabel(layoutRecs[3], "Stop after X clicks");
        if (GuiTextBox(StopAfterClickInputBox.Rect, StopAfterClickInputBox.Text, TEXT_SIZE, StopAfterClickInputBox.EditMode))
        {
            StopAfterClickInputBox.EditMode = !StopAfterClickInputBox.EditMode;
        }
        GuiLabel(layoutRecs[4], "Start Delay");
        if (GuiTextBox(DelayMinsInputBox.Rect, DelayMinsInputBox.Text, TEXT_SIZE, DelayMinsInputBox.EditMode))
        {
            DelayMinsInputBox.EditMode = !DelayMinsInputBox.EditMode;
        }
        if (GuiTextBox(DelaySecondsInputBox.Rect, DelaySecondsInputBox.Text, TEXT_SIZE, DelaySecondsInputBox.EditMode))
        {
            DelaySecondsInputBox.EditMode = !DelaySecondsInputBox.EditMode;
        }
        if (GuiTextBox(DelayMsInputBox.Rect, DelayMsInputBox.Text, TEXT_SIZE, DelayMsInputBox.EditMode))
        {
            DelayMsInputBox.EditMode = !DelayMsInputBox.EditMode;
        }
        //----------------------------------------------------------------------------------

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow(); // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}

//------------------------------------------------------------------------------------
// Controls Functions Definitions (local)
//------------------------------------------------------------------------------------
