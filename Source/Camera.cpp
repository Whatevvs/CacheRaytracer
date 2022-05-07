#include "Precomp.h"
#include "Camera.h"

Camera::Camera()
{
	cameraPosition = Vector3(0.0f, 0.0f, 0.0f);
	cameraDirection = Vector3(0.0f, 0.0f, 1.0f);
	UpdateCameraSettings();
}

void Camera::Debug()
{
	ImguiHandler* imgui = ImguiHandler::GetInstance();
	imgui->CreateWindow("Debug: Camera");
	imgui->ActivateWindow("Debug: Camera");
	imgui->SliderVector3("Position", cameraPosition, -10.0f, 10.0f);
	imgui->SliderFloat("Angle", cameraAngleHorizontal, 0.0f, 360.0f);
	imgui->DisableWindow();

	float a = cameraAngleHorizontal * DegToRad;
	float x = cosf(a);
	float z = sinf(a);

	cameraDirection = Vector3(x, 0.0f, z);
	UpdateCameraSettings();
}

void Camera::UpdateCameraSettings()
{
	float theta = cameraFOV * DegToRad; // total view angle		\/
	float h = tanf(theta * 0.5f); // half of the view angel \|

	// since our viewport height is scaled with our FOV
	// our viewportWidth will be correctly scaled as well
	float viewportHeight = 2.0f * h;
	float viewportWidth = aspectRatio * viewportHeight;

	cameraHorizontal = Vector3(viewportWidth, 0.0f, 0.0f);
	cameraVertical = Vector3(0.0f, viewportHeight, 0.0f);
	lowerLeftCorner = cameraPosition - cameraHorizontal * 0.5f - cameraVertical * 0.5f - cameraDirection;
}

Ray Camera::GetRay(CameraType type, ScreenPos_UV uv)
{
	Ray primitiveRay; // Default to Pinhole

	switch (type)
	{
	default:
	case CameraType::Pinhole:
		return GetPinholeRay(uv);
	case CameraType::ThinLens:
		return GetThinLensRay(uv);
	case CameraType::GeneralisedPanini:
		return GetGeneralisedPaniniRay(uv);
	case CameraType::Fisheye:
		return GetFisheyeRay(uv);
	case CameraType::Lenslet:
		return GetLensletRay(uv);
	case CameraType::Octohedral:
		return GetOctahedralRay(uv);
	case CameraType::Cube:
		return GetPinholeRay(uv);
	case CameraType::Orthographic:
		return GetOrthographicRay(uv);
	case CameraType::FibonacciSphere:
		return GetFibonacciSphereRay(uv);
	}
}

Ray Camera::GetPinholeRay(ScreenPos_UV uv)
{
	// RTG2 Pinhole ray gen
	/*float x = (u * 2.0f) - 1.0f;
	float y = (v * 2.0f) - 1.0f;
	float theta = FOV * DegToRad;
	float tanHalfAngle = tanf(theta * 0.5f);
	float aspectScale = aspectRatio;
	Vector2 pixel = Vector2(x, y) * tanHalfAngle / aspectScale;
	Vector3 direction = Vector3(pixel.x, pixel.y, -1);

	return Ray(cameraPosition, direction);*/

	// Shirley pinhole ray gen
	return Ray(cameraPosition, lowerLeftCorner + cameraHorizontal * uv.u + cameraVertical * uv.v - cameraPosition);
}

Ray Camera::GetThinLensRay(ScreenPos_UV uv)
{
	return Ray();
}

Ray Camera::GetGeneralisedPaniniRay(ScreenPos_Pixel pixel)
{
	 Vector2 pixelCenterCoords = Vector2(pixel.x,pixel.y) + Vector2(0.5f) - ScreenSizeHalf;
	 Vector2 hv = (pixelCenterCoords / ScreenSizeHalf) * (cameraFOV * 0.5f);
	
	 float halfFOV = cameraFOV * 0.5f;
	 float halfPaniniFOV = atan2f(sin(halfFOV), cos(halfFOV) + paniniDistance);
	
	 hv *= halfPaniniFOV;
	
	 float M = sqrtf(1.0f - (sinf(hv.x * sinf(hv.x) * paniniDistance))) + paniniDistance * cosf(hv.x);
	
	 float x = (sin(hv.x) * M);
	 float z = (cos(hv.x) * M) - paniniDistance;
	 float y = Lerp(tan(hv.y) * (1 + z), tan(hv.y) * z, paniniVerticalCompression);
	
	 Vector3 direction = Vector3(x, y, -z).Normalized();
	
	 return Ray(Vector3(0.0f), direction);
}

Ray Camera::GetFisheyeRay(ScreenPos_Pixel pixel)
{
	/* TODO
		I don't know if this is accurate, also it does not scale with field of view
	*/

	Vector2 angle = ((Vector2(pixel.x,pixel.y) - Vector2(ScreenWidth,ScreenHeight) * 0.5f)) / fmaxf(ScreenWidth,ScreenHeight);

	// Crop Fisheye
	if (angle.Length() > 0.5f) 
		return Ray(Vector3(0.0f), Vector3(0.0f));

	Vector3 dir = Vector3(sinf(angle.x), -sinf(angle.y) * cosf(angle.x), -cosf(angle.x) * cosf(angle.y)).Normalized();

	return Ray(Vector3(0.0f), dir);

}

Ray Camera::GetLensletRay(ScreenPos_UV uv)
{
	return Ray();
}

Ray Camera::GetOctahedralRay(ScreenPos_UV uv)
{
	return Ray();
}

Ray Camera::GetOrthographicRay(ScreenPos_NDC ndc)
{
	float aspect = static_cast<float>(ScreenWidth) / static_cast<float>(ScreenHeight);
	Vector3 origin = Vector3(ndc.x * aspect, ndc.y, 0.0f) * 0.1f * cameraFOV;
	return Ray(origin, Vector3(0.0f,0.0f,-1.0f));
}

Ray Camera::GetFibonacciSphereRay(ScreenPos_UV uv)
{
	return Ray();
}
