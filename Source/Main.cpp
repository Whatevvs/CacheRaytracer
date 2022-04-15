#include <SDL.h>
#include "Timer.h"
#include <iostream>

#include "ImGui/imgui.h"
#include "ImGui/imgui_impl_sdl.h"
#include "ImGui/imgui_impl_sdlrenderer.h"

typedef uint32_t Pixel;

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
bool isApplicationRunning { true };

int main(int argc, char* args[])
{
	SDL_Window* window = NULL;

	SDL_Init(SDL_INIT_VIDEO);
	window = SDL_CreateWindow("Cache Raytracer", 250, 250, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	SDL_Texture* frameBuffer = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, SCREEN_WIDTH, SCREEN_HEIGHT);

	Pixel* pixels = new Pixel[SCREEN_WIDTH * SCREEN_HEIGHT];

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	ImGui::StyleColorsDark();
	ImGui_ImplSDL2_InitForSDLRenderer(window, renderer);
	ImGui_ImplSDLRenderer_Init(renderer);

	Timer timer;
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

		static float x = 0.0f;

		ImGui_ImplSDLRenderer_NewFrame();
		ImGui_ImplSDL2_NewFrame();
		ImGui::NewFrame();
		ImGui::SetNextWindowPos(ImVec2(0, 0));
		ImGui::SetNextWindowSize(ImVec2(250, 100));
		ImGui::Begin("Test Window:", nullptr);
		ImGui::Text("Hi Matt and Angel");
		ImGui::Text("~Huge Stefan");
		ImGui::Text("P.S. Matt make input work...");
		ImGui::Text("P.P.S. Just did it ;)");
		ImGui::End();
		ImGui::Render();

		float s = (sinf(x += 0.03f) + 1.0f) * 0.5f;
		Pixel p = (1.0f - s) * 10 + s * 250;

		for (int i = 0; i < SCREEN_WIDTH * SCREEN_HEIGHT; i++)
			pixels[i] = p;

		SDL_UpdateTexture(frameBuffer, NULL, pixels, SCREEN_WIDTH * sizeof(uint32_t));

		SDL_RenderClear(renderer);
		SDL_RenderCopy(renderer, frameBuffer, NULL, NULL);

		ImGui_ImplSDLRenderer_RenderDrawData(ImGui::GetDrawData());

		SDL_RenderPresent(renderer);

		printf("Frametime: %fs\n", timer.TimeSinceLast());
	}

	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0;
}