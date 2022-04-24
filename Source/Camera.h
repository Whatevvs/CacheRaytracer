#pragma once

struct Ray;

enum class CameraType
{
	Pinhole,
	ThinLens,
	GeneralisedPanini,
	Fisheye,
	Lenslet,
	Octohedral,
	Cube,
	Orthographic,
	FibonacciSphere
};

class Camera
{
public:
	Camera();

	void UpdateCameraSettings();
	Ray GetRay(CameraType type, ScreenPos_UV uv);

	float cameraFOV = 90.0f; // amount of visible space measured in degrees
	float focalLength = 1.0f; // distance between sensor and image plane/lens 
	float aspectRatio = AspectRatio; // determines the aspect ratio

	Vector3 cameraPosition;
	Vector3 cameraHorizontal;
	Vector3 cameraVertical;

private:
	Ray GetPinholeRay(ScreenPos_UV uv);
	Ray GetThinLensRay(ScreenPos_UV uv);
	Ray GetGeneralisedPaniniRay(ScreenPos_Pixel pixel);
	Ray GetFisheyeRay(ScreenPos_Pixel pixel);
	Ray GetLensletRay(ScreenPos_UV uv);
	Ray GetOctahedralRay(ScreenPos_UV uv);
	Ray GetOrthographicRay(ScreenPos_NDC ndc);
	Ray GetFibonacciSphereRay(ScreenPos_UV uv);

	Vector3 lowerLeftCorner; // bottom left corner of the image plane
};