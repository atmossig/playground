#ifndef CONTROL_H
#define CONTROL_H

class Camera; // Forward declaration

class Control {
public:
    Control(Camera& camera);

    void kbDown(unsigned char key, int x, int y);
    void kbUp(unsigned char key, int x, int y);
    void PassiveMouseMotion(int x, int y);
    void UpdateControl(float deltaTime);

    bool isCursorLocked() const { return CursorLocked; }

private:
    Camera& camera;
    bool Keys[256];
    bool CursorLocked;
    int LastMouseX;
    int LastMouseY;
    bool FirstMouse;
};

#endif // CONTROL_H