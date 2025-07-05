#ifndef APP_H
#define APP_H

#include "camera.h"
#include "control.h"
#include "grid.h"

class App {
public:
    static App& GetInstance();
    void Init(int argc, char** argv);
    void Run();

    // Deleted functions to prevent copies
    App(const App&) = delete;
    void operator=(const App&) = delete;

private:
    App(); // Private constructor for singleton

    // Member function callbacks
    void Display();
    void ReShape(int w, int h);
    void Idle();
    void kbDown(unsigned char key, int x, int y);
    void kbUp(unsigned char key, int x, int y);
    void PassiveMouseMotion(int x, int y);

    // Static callback functions that forward to the instance
    static void DisplayCB();
    static void ReShapeCB(int w, int h);
    static void IdleCB();
    static void kbDownCB(unsigned char key, int x, int y);
    static void kbUpCB(unsigned char key, int x, int y);
    static void PassiveMouseMotionCB(int x, int y);

    Camera camera;
    Control control;
    Grid grid;
    int lastFrameTime;
};

#endif // APP_H