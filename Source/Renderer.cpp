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

Vector3 sunPos{0,1,0};

void Renderer::Update(float deltaTime)
{
	Pixel* buffer = screenBuffer;

	for (int y = 0; y < renderHeight; y++)
	{
		for (int x = 0; x < renderWidth; x++)
		{
			int yPos = renderHeight - y - 1;

			// Default to black
			buffer[0] = 0x000000;

			float u = float(x) / (renderWidth - 1);
			float v = float(yPos) / (renderHeight - 1);

			Ray ray = camera.GetRay(CameraType::Pinhole, u, v);

			for (int i = 0; i < primitives.size(); i++)
			{
				if (primitives[i]->HasHit(ray, 0.1f, 10000.0f))
				{
					buffer[0] = primitives[i]->Color;
				}
			}

			if(!buffer[0])
			{
				Vector3 res = GeneratePixel(ray, x,y);
				//printf("Res: %f %f %f\n", res.x, res.y ,res.z);
				buffer[0] = (((int)(res.x * 255) << 16) + ((int)(res.y * 255) << 8) + (int)(res.z * 255));
				//buffer[0] = 0x555599;
			}

			buffer++;
		}
	}
}
