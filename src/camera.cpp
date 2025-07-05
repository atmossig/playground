#include "camera.h"
#include "config.h"
#include <GL/freeglut.h>
#include <cmath>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

//-------------------------------------------------------
// Camera constructor
// 
// Initializes the camera position, yaw, pitch; and
// calls the function to update the camera vectors.
//-------------------------------------------------------
Camera::Camera()
	: yaw(-90.0f), pitch(0.0f)
{
	// XYZ spawn
	position[0] = 0.0f,
	position[1] = 1.0f,
	position[2] = 5.0f,

	// Function to update the camera vectors
	UpdateCameraVectors();
}

//-------------------------------------------------------
// Update the view matrix based on the camera's 
// position and orientation
//-------------------------------------------------------
void Camera::UpdateView()
{
	// Set the camera's view matrix
	gluLookAt(position[0], position[1], position[2],
		position[0] + front[0], position[1] + front[1], position[2] + front[2],
		up[0], up[1], up[2]);
}

//-------------------------------------------------------
// Update the projection matrix based on 
// the window size
//-------------------------------------------------------
void Camera::UpdateProjection(int width, int height) {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(CAMERA_FOV, (float)width / (float)height, CAMERA_NEAR_PLANE, CAMERA_FAR_PLANE);
	glMatrixMode(GL_MODELVIEW);
}

//-------------------------------------------------------
// Process mouse movement to update yaw and pitch
//-------------------------------------------------------
void Camera::ProcessMouseMovement(float xoffset, float yoffset) {
	xoffset *= MOUSE_SENSITIVITY;
	yoffset *= MOUSE_SENSITIVITY;

	yaw += xoffset;
	pitch += yoffset;

	// Constrain pitch to avoid flipping
	if (pitch > 89.0f) pitch = 89.0f;
	if (pitch < -89.0f) pitch = -89.0f;

	UpdateCameraVectors();
}

//-------------------------------------------------------
// Move forward
//-------------------------------------------------------
void Camera::MoveForward(float deltaTime) {
	float velocity = CAMERA_SPEED * deltaTime;
	position[0] += front[0] * velocity;
	position[1] += front[1] * velocity;
	position[2] += front[2] * velocity;
}

//-------------------------------------------------------
// Move backward
//-------------------------------------------------------
void Camera::MoveBackward(float deltaTime) {
	float velocity = CAMERA_SPEED * deltaTime;
	position[0] -= front[0] * velocity;
	position[1] -= front[1] * velocity;
	position[2] -= front[2] * velocity;
}

//-------------------------------------------------------
// Move right
//-------------------------------------------------------
void Camera::StrafeLeft(float deltaTime) {
	float velocity = CAMERA_SPEED * deltaTime;
	position[0] -= right[0] * velocity;
	position[1] -= right[1] * velocity;
	position[2] -= right[2] * velocity;
}

//-------------------------------------------------------
// Move right
//-------------------------------------------------------
void Camera::StrafeRight(float deltaTime) {
	float velocity = CAMERA_SPEED * deltaTime;
	position[0] += right[0] * velocity;
	position[1] += right[1] * velocity;
	position[2] += right[2] * velocity;
}

//-------------------------------------------------------
// Update the camera vectors based on yaw and pitch
//--------------------------------------------------------
void Camera::UpdateCameraVectors() 
{
	// Calculate the new Front vector
	float front_x = cos(yaw * M_PI / 180.0f) * cos(pitch * M_PI / 180.0f);
	float front_y = sin(pitch * M_PI / 180.0f);
	float front_z = sin(yaw * M_PI / 180.0f) * cos(pitch * M_PI / 180.0f);

	// Normalize front vector
	float front_len = sqrt(front_x * front_x + front_y * front_y + front_z * front_z);
	front[0] = front_x / front_len;
	front[1] = front_y / front_len;
	front[2] = front_z / front_len;

	// Recalculate the Right vector (cross product)
	right[0] = front[1] * worldUp[2] - front[2] * worldUp[1];
	right[1] = front[2] * worldUp[0] - front[0] * worldUp[2];
	right[2] = front[0] * worldUp[1] - front[1] * worldUp[0];
	float right_len = sqrt(right[0] * right[0] + right[1] * right[1] + right[2] * right[2]);
	right[0] /= right_len;
	right[1] /= right_len;
	right[2] /= right_len;

	// Recalculate the Up vector (cross product)
	up[0] = right[1] * front[2] - right[2] * front[1];
	up[1] = right[2] * front[0] - right[0] * front[2];
	up[2] = right[0] * front[1] - right[1] * front[0];
}