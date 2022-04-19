#pragma once

#include "Camera.h"

class Primitive;

// Idea/Concept: contains/manages the output of the ray tracer
// So things like the framebuffer and camera are updated "in" here, 
class Renderer
{
public:
	void Start(Pixel* screenBuffer);
	void Update(float deltaTime);

private:
	Pixel* screenBuffer;
	Camera camera;
	std::vector<Primitive*> primitives;

	// Width/Height from our actual 'rendered' image, determined by the camera FOV
	int renderWidth;
	int renderHeight;
};

