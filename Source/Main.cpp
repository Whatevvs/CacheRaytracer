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