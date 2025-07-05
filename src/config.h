#ifndef CONFIG_H
#define CONFIG_H

// Window settings
constexpr int	SCREEN_WIDTH = 1280;
constexpr int	SCREEN_HEIGHT = 720;

// Camera settings
constexpr float CAMERA_FOV = 75.0f;				// FOV degres
constexpr float CAMERA_NEAR_PLANE = 0.1f;		// Near plane distance
constexpr float CAMERA_FAR_PLANE = 100.0f;		// Far plane distance
constexpr float	CAMERA_SPEED = 5.0f;			// In units per second
constexpr float MOUSE_SENSITIVITY = 0.1f;		// Sensitivity for mouse movement

#endif // CONFIG_H