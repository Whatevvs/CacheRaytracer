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
	Ray GetRay(CameraType type, ScreenPos_UV uv);

	float FOV = 90.0f; // amount of visible space measured in degrees
	float focalLength = 1.0f; // distance between sensor and image plane/lens 
	float aspectRatio = AspectRatio; // determines the aspect ratio

	Vector3 cameraPosition;
	Vector3 cameraHorizontal;
	Vector3 cameraVertical;
private:
	Ray GetPinholeRay(ScreenPos_UV uv);
	Ray GetThinLensRay(ScreenPos_UV uv);
	Ray GetGeneralisedPaniniRay(ScreenPos_UV uv);
	Ray GetFisheyeRay(ScreenPos_UV uv);
	Ray GetLensletRay(ScreenPos_UV uv);
	Ray GetOctahedralRay(ScreenPos_UV uv);
	Ray GetFibonacciSphereRay(ScreenPos_UV uv);

	Vector3 lowerLeftCorner; // bottom left corner of the image plane
};