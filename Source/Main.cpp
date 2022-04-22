#include <SDL.h>
#include "Precomp.h"

#include "Style.h"
#include "AppWindow.h"
#include "Renderer.h"

bool isApplicationRunning { true };
AppWindow* window { nullptr };

int main(int argc, char* args[])
{
	// Initalize SDL and Dear ImGUI
	SDL_Init(SDL_INIT_VIDEO);
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	ImGui::StyleColorsDark();

	window = new AppWindow(isApplicationRunning, ScreenWidth, ScreenHeight);

	Style();
	

#ifdef _DEBUG
	printf("Testing Screen Coordinate conversions\n");
	printf("-------------------------------------\n");
	ScreenPos_Pixel pixel = ScreenPos_Pixel(640,360);	
	printf("	Pixel ScreenPos: %i %i\n", ScreenPos_Pixel(pixel).x, ScreenPos_Pixel(pixel).y);
	printf("	UV ScreenPos: %f %f\n", ScreenPos_UV(pixel).u, ScreenPos_UV(pixel).v);
	printf("	NDC ScreenPos: %f %f\n\n", ScreenPos_NDC(pixel).x, ScreenPos_NDC(pixel).y);

	ScreenPos_UV uv = ScreenPos_UV(0.5f,0.5f);
	printf("	Pixel ScreenPos: %i %i\n", ScreenPos_Pixel(uv).x, ScreenPos_Pixel(uv).y);
	printf("	UV ScreenPos: %f %f\n", ScreenPos_UV(uv).u, ScreenPos_UV(uv).v);
	printf("	NDC ScreenPos: %f %f\n\n", ScreenPos_NDC(uv).x, ScreenPos_NDC(uv).y);

	ScreenPos_NDC ndc = ScreenPos_NDC(0.0f,0.0f);
	printf("	Pixel ScreenPos: %i %i\n", ScreenPos_Pixel(ndc).x, ScreenPos_Pixel(ndc).y);
	printf("	UV ScreenPos: %f %f\n", ScreenPos_UV(ndc).u, ScreenPos_UV(ndc).v);
	printf("	NDC ScreenPos: %f %f\n", ScreenPos_NDC(ndc).x, ScreenPos_NDC(ndc).y);
	printf("-------------------------------------\n\n");

#endif

	Renderer renderer;
	renderer.Start(window->GetScreenBuffer());

	while (isApplicationRunning)
	{
		ImGui_ImplSDLRenderer_NewFrame();
		ImGui_ImplSDL2_NewFrame();
		ImGui::NewFrame();

		SDL_Event event;
		while (SDL_PollEvent(&event)) 
		{
			switch(event.type)
			{
			case SDL_QUIT:
				isApplicationRunning = false;
				break;
			}

			ImGui_ImplSDL2_ProcessEvent(&event);
		}

		renderer.Update(window->GetDeltaTime());
		window->Update();
	}

	SDL_Quit();

	return 0;
}