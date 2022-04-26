#pragma once

#include "Camera.h"

class Primitive;

// Idea/Concept: contains/manages the output of the ray tracer
// So things like the framebuffer and camera are updated "in" here, 
class Renderer
{
public:
	void Start(Pixel* screenBuffer);
	void DrawUI();
	void Update(float deltaTime);
	void CalculateShading(Pixel* pixel, const Ray& ray);

private:
	Pixel* screenBuffer;
	Camera camera;
	std::vector<Primitive*> primitives;

	// Width/Height from our actual 'rendered' image, determined by the camera FOV
	int renderWidth;
	int renderHeight;

	float tMin = 0.01f;
	float tMax = 3.40282e+038;
	float lightX = 0.0f;
};

