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

	window = new AppWindow(isApplicationRunning, ScreenWidth, ScreenHeight);
	
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

	ImguiHandler* imgui = ImguiHandler::GetInstance();
	imgui->Initialize(window->GetSDLWindow(), window->GetSDLRenderer());
	Style();

	while (isApplicationRunning)
	{
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

		imgui->Update();

		// Example of imgui thingy
		imgui->CreateWindow(Vector2(800, 20), Vector2(400, 200), "Hey Matt");
		imgui->DrawText("Hey Matt", "This is an example wow");

		// Instead of having to pass the "Window Name" of what you want to use, we can also activate a window 
		// so you can have multiple calls, it's maybe a bit stupid.
		// We should probably make the WindowName an enum instead
		imgui->ActivateWindow("Hey Matt");
		imgui->DrawText("\nThis window was activated so I can make multiple calls");
		imgui->DrawText("More text...");
		imgui->DrawText("More!");
		imgui->DisableWindow();

		// My idea is that we just we expand on this with whatever we need
		// and it can act as our layer of interaction with ImGui, mainly making it
		// easier to draw to windows from any place.

		renderer.Update(window->GetDeltaTime());
		window->Update();
	}

	SDL_Quit();

	return 0;
}