#ifndef CAMERA_H
#define CAMERA_H

class Camera {
public:
	Camera();

	void UpdateView();
	void UpdateProjection(int width, int height);
	void ProcessMouseMovement(float xoffset, float yoffset);

	// Movement methods
	void MoveForward(float deltaTime);
	void MoveBackward(float deltaTime);
	void StrafeLeft(float deltaTime);
	void StrafeRight(float deltaTime);
private:
	void UpdateCameraVectors();

	// Camera attributes
	float position[3];
	float front[3];
	float up[3];
	float right[3];
	const float worldUp[3] = { 0.0f, 1.0f, 0.0f };

	// Euler angles
	float yaw;
	float pitch;
};

#endif // CAMERA_H