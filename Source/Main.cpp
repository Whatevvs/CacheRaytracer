#include <SDL.h>
#include "Timer.h"
#include <iostream>

#include "ImGui/imgui.h"
#include "ImGui/imgui_impl_sdl.h"
#include "ImGui/imgui_impl_sdlrenderer.h"

#include "../Style.h"
#include "../AppWindow.h"
#include "../CacheMath.h"

typedef uint32_t Pixel;

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

	window = new AppWindow(isApplicationRunning);

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

		window->Update();
	}

	SDL_Quit();

	return 0;
}