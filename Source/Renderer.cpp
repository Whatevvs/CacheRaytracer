#include "Precomp.h"
#include "Renderer.h"
#include "AABB.h"
#include "Sphere.h"

void Renderer::Start(Pixel* screenBuffer)
{
	this->screenBuffer = screenBuffer;

	Primitive* testAABB = new AABB(Vector3(0.2f, 0.2f, -5.0f), Vector3(1.0f, 1.0f, 1.0f), 0xff0f0f);
	Primitive* testAABB2 = new AABB(Vector3(-4.0f, 0.2f, -5.0f), Vector3(1.0f, 1.25f, 2.0f), 0x0fff0f);
	Primitive* testAABB3 = new AABB(Vector3(2.5f, 1.2f, -5.0f), Vector3(1.0f, 0.25f, 1.0f), 0x0f0fff);
	Primitive* testSphere = new Sphere(1.0f, Vector3(2.0f, -1.0f, -5.0f), 0xff0fff);

	primitives.push_back(testAABB);
	primitives.push_back(testAABB2);
	primitives.push_back(testAABB3);
	primitives.push_back(testSphere);

	renderWidth = ScreenWidth;
	renderHeight = renderWidth / camera.aspectRatio;
}

void Renderer::Update(float deltaTime)
{
	for (int x = 0; x < renderWidth; x++)
	{
		for (int y = 0; y < renderHeight; y++)
		{
			int yPos = renderHeight - y - 1;

			// Default to black
			screenBuffer[x + yPos * renderWidth] = 0x000000;

			float u = float(x) / (renderWidth - 1);
			float v = float(y) / (renderHeight - 1);

			Ray ray = camera.GetRay(CameraType::Pinhole, u, v);

			for (int i = 0; i < primitives.size(); i++)
			{
				if (primitives[i]->HasHit(ray, 0.1f, 10000.0f))
				{
					screenBuffer[x + yPos * renderWidth] = primitives[i]->Color;
				}
			}
		}
	}
}
