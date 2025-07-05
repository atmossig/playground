#include "control.h"
#include "camera.h"
#include "config.h"
#include <GL/freeglut.h>
#include <iostream>

Control::Control(Camera& cam)
    : camera(cam), CursorLocked(true), FirstMouse(true) {
    for (int i = 0; i < 256; ++i) {
        Keys[i] = false;
    }
}

void Control::kbDown(unsigned char key, int, int) {
    if (key == 27) { // ESC key
        CursorLocked = !CursorLocked;
        if (CursorLocked) {
            glutSetCursor(GLUT_CURSOR_NONE);
            FirstMouse = true;
        }
        else {
            glutSetCursor(GLUT_CURSOR_INHERIT);
        }
    }
    Keys[tolower(key)] = true;
}

void Control::kbUp(unsigned char key, int, int) {
    Keys[tolower(key)] = false;
}

void Control::PassiveMouseMotion(int x, int y) {
    if (!CursorLocked) return;

    if (FirstMouse) {
        LastMouseX = x;
        LastMouseY = y;
        FirstMouse = false;
    }

    float xoffset = x - LastMouseX;
    float yoffset = LastMouseY - y; // Reversed since y-coordinates go from top to bottom

    LastMouseX = x;
    LastMouseY = y;

    camera.ProcessMouseMovement(xoffset, yoffset);

    // Warp pointer to center of screen to prevent it from leaving the window
    if (x < 100 || x > SCREEN_WIDTH - 100 || y < 100 || y > SCREEN_HEIGHT - 100) {
        LastMouseX = SCREEN_WIDTH / 2;
        LastMouseY = SCREEN_HEIGHT / 2;
        glutWarpPointer(LastMouseX, LastMouseY);
    }
}

void Control::UpdateControl(float deltaTime) {
    if (Keys['w']) camera.MoveForward(deltaTime);
    if (Keys['s']) camera.MoveBackward(deltaTime);
    if (Keys['a']) camera.StrafeLeft(deltaTime);
    if (Keys['d']) camera.StrafeRight(deltaTime);
}