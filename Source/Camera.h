#pragma once

struct Ray;

enum class CameraType
{
	Pinhole
};

class Camera
{
public:
	Camera();

	void UpdateCameraSettings();
	Ray GetRay(CameraType type, float u, float v);

	float FOV = 90.0f; // amount of visible space measured in degrees
	float focalLength = 1.0f; // distance between sensor and image plane/lens 
	float aspectRatio = 16.0f / 9.0f; // determines the 

	Vector3 cameraPosition;
	Vector3 cameraHorizontal;
	Vector3 cameraVertical;
private:
	Ray GeneratePinholeRay(float u, float v);

	Vector3 lowerLeftCorner; // bottom left corner of the image plane
};