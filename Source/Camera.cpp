#include "Precomp.h"
#include "Camera.h"

Camera::Camera()
{
	cameraPosition = Vector3(0.0f, 0.0f, 0.0f);
	UpdateCameraSettings();
}

void Camera::UpdateCameraSettings()
{
	float theta = FOV * DegToRad; // total view angle		\/
	float h = tanf(theta * 0.5f); // half of the view angel \|

	// since our viewport height is scaled with our FOV
	// our viewportWidth will be correctly scaled as well
	float viewportHeight = 2.0f * h;
	float viewportWidth = aspectRatio * viewportHeight;

	cameraHorizontal = Vector3(viewportWidth, 0.0f, 0.0f);
	cameraVertical = Vector3(0.0f, viewportHeight, 0.0f);
	lowerLeftCorner = cameraPosition - cameraHorizontal * 0.5f - cameraVertical * 0.5f - Vector3(0.0f, 0.0f, focalLength);
}

Ray Camera::GetRay(CameraType type, float u, float v)
{
	Ray primitiveRay;

	switch (type)
	{
	case CameraType::Pinhole:
		primitiveRay = GeneratePinholeRay(u, v);
		break;
	}

	return primitiveRay;
}

Ray Camera::GeneratePinholeRay(float u, float v)
{
	// RTG2 Pinhole ray gen
	/*float x = (u * 2.0f) - 1.0f;
	float y = (v * 2.0f) - 1.0f;
	float theta = FOV * DegToRad;
	float tanHalfAngle = tanf(theta * 0.5f);
	float aspectScale = SCREEN_WIDTH;
	vec2 pixel = vec2(x, y) * tanHalfAngle / aspectScale;
	vec3 direction = vec3(pixel.x, pixel.y, -1);

	return Ray(cameraPosition, direction);*/

	// Shirley pinhole ray gen
	return Ray(cameraPosition, lowerLeftCorner + cameraHorizontal * u + cameraVertical * v - cameraPosition);
}
