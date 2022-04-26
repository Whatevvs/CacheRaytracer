#include "Precomp.h"
#include "Renderer.h"
#include "AABB.h"
#include "Sphere.h"

Pixel VecToPixel(Vector3 color)
{
	color.x = sqrtf(color.x);
	color.y = sqrtf(color.y);
	color.z = sqrtf(color.z);

	unsigned int r = (int)(255.0f * color.x);
	unsigned int g = (int)(255.0f * color.y);
	unsigned int b = (int)(255.0f * color.z);

	return (r << 16) + (g << 8) + b;
}

void Renderer::Start(Pixel* screenBuffer)
{
	this->screenBuffer = screenBuffer;

	Primitive* testSphere = new Sphere(1.0f, Vector3(2.0f, -1.0f, -5.0f), Vector3(1.0f, 0.0f, 0.0f));

	primitives.push_back(testSphere);

	renderWidth = ScreenWidth;
	renderHeight = renderWidth / camera.aspectRatio;
}


std::string cameraTypes[] = 
{
"Pinhole",
"Thin lens",
"Generalized Panini",
"Fisheye lens",
"Lenslet / Microlens Array",
"Octahedral lens",
"Cube map",
"Orthographic lens",
"Fibonacci sphere lens"
};

int currentCamera;

void Renderer::DrawUI()
{
	ImGui::Begin("Camera Options");
	
	if (ImGui::Button("Camera Lens"))
        ImGui::OpenPopup("CameraLensPopup");

    ImGui::SameLine();
    ImGui::TextUnformatted((std::string("Current: ") + (currentCamera == -1 ? "<None>" : cameraTypes[currentCamera])).c_str());

    if (ImGui::BeginPopup("CameraLensPopup"))
    {
        ImGui::Text("Select Camera Lens");
        ImGui::Separator();
        for (int i = 0; i < IM_ARRAYSIZE(cameraTypes); i++)
            if (ImGui::Selectable(cameraTypes[i].c_str()))
                currentCamera = i;
        ImGui::EndPopup();
    }
	ImGui::SetNextItemWidth(128);
	ImGui::SliderFloat("Field of View (Horizontal)", &camera.cameraFOV,1.0f,180.0f);

	ImGui::End();
}

Vector3 sunPos{0,1,0};

void Renderer::Update(float deltaTime)
{
	DrawUI();

	Pixel* pixel = screenBuffer;

	for (int y = 0; y < renderHeight; y++)
	{
		for (int x = 0; x < renderWidth; x++)
		{
			int yPos = renderHeight - y - 1;

			// Default to black
			pixel[0] = 0x000000;

			float u = float(x) / (renderWidth - 1);
			float v = float(yPos) / (renderHeight - 1);

			Ray ray = camera.GetRay((CameraType)currentCamera, {u, v});

			if (ray.direction.SqrLength() == 0)
			{
				pixel[0] = 0xff0000;
			}
			else
			{
				CalculateShading(pixel, ray);
			}
			
			pixel++;
		}
	}
}

void Renderer::CalculateShading(Pixel* pixel, const Ray& ray)
{
	HitRecord record;
	bool hitAnything = false;
	float closestMax = tMax;

	// Find nearest hit
	for (int i = 0; i < primitives.size(); i++)
	{
		if (primitives[i]->HasHit(ray, tMin, closestMax, record))
		{
			hitAnything = true;
			closestMax = record.t;
		}
	}

	if (!hitAnything)
	{
		// replace with background
		pixel[0] = 0x00000;
		return;
	}

	pixel[0] = VecToPixel((record.normal + 1.0f) * 0.5f);
}
