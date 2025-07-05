#include "app.h"
#include "config.h"
#include <GL/glut.h>
#include <iostream>

// Singleton instance retrieval
App& App::GetInstance() {
    static App instance;
    return instance;
}

// Private constructor
App::App() : control(camera), grid(50, 1.0f), lastFrameTime(0) {}

// Initialization
void App::Init(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(SCREEN_WIDTH, SCREEN_HEIGHT);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Playground");

    glEnable(GL_DEPTH_TEST);
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f); // Dark background

    // Register static callbacks
    glutDisplayFunc(DisplayCB);
    glutReshapeFunc(ReShapeCB);
    glutIdleFunc(IdleCB);
    glutKeyboardFunc(kbDownCB);
    glutKeyboardUpFunc(kbUpCB);
    glutPassiveMotionFunc(PassiveMouseMotionCB);
    glutMotionFunc(PassiveMouseMotionCB); // Also capture mouse when button is down

    // Initial cursor state
    glutSetCursor(GLUT_CURSOR_NONE);
    glutWarpPointer(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);

    lastFrameTime = glutGet(GLUT_ELAPSED_TIME);
}

// Start the main loop
void App::Run() {
    glutMainLoop();
}

// --- Member Function Implementations ---

void App::Display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    camera.UpdateView();
    grid.DrawGrid();

    glutSwapBuffers();
}

void App::ReShape(int w, int h) {
    glViewport(0, 0, w, h);
    camera.UpdateProjection(w, h);
}

void App::Idle() {
    int currentTime = glutGet(GLUT_ELAPSED_TIME);
    float deltaTime = (currentTime - lastFrameTime) / 1000.0f;
    lastFrameTime = currentTime;

    control.UpdateControl(deltaTime);

    glutPostRedisplay();
}

void App::kbDown(unsigned char key, int x, int y) {
    control.kbDown(key, x, y);
}

void App::kbUp(unsigned char key, int x, int y) {
    control.kbUp(key, x, y);
}

void App::PassiveMouseMotion(int x, int y) {
    control.PassiveMouseMotion(x, y);
}

// --- Static Callback Wrappers ---

void App::DisplayCB() {
    GetInstance().Display();
}

void App::ReShapeCB(int w, int h) {
    GetInstance().ReShape(w, h);
}

void App::IdleCB() {
    GetInstance().Idle();
}

void App::kbDownCB(unsigned char key, int x, int y) {
    GetInstance().kbDown(key, x, y);
}

void App::kbUpCB(unsigned char key, int x, int y) {
    GetInstance().kbUp(key, x, y);
}

void App::PassiveMouseMotionCB(int x, int y) {
    GetInstance().PassiveMouseMotion(x, y);
}