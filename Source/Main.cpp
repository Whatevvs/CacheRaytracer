#include <SDL.h>
#include "Timer.h"
#include <iostream>

#include "ImGui/imgui.h"
#include "ImGui/imgui_impl_sdl.h"
#include "ImGui/imgui_impl_sdlrenderer.h"

#include "../Style.h"

typedef uint32_t Pixel;

const int SCREEN_WIDTH = 1920;
const int SCREEN_HEIGHT = 1080;
bool isApplicationRunning { true };
Timer timer;




const int frameTimePlotCount = 32; // How many lines to plot
float maxFrameTime = 0.0f;
float minFrameTime = 10000000.0f;
float frameTimes[frameTimePlotCount] {};
int frameTimeIndex = 0;

const int frameTimeAverageStepCount = 10; // How many frames to average
float frameStepAverage = 0.0f;
int frameTimeAverageStepIndex = 0;

void DrawUI()
{
	ImGui_ImplSDLRenderer_NewFrame();
	ImGui_ImplSDL2_NewFrame();
	ImGui::NewFrame();

	ImGuiWindowFlags flags {0};

#pragma region Performance Metrics Overlay
	ImGui::SetNextWindowPos(ImVec2(5, SCREEN_HEIGHT - 5), ImGuiCond_Always, {0.0f, 1.0f});
	ImGui::SetNextWindowBgAlpha(0.5f);

	flags |= ImGuiWindowFlags_NoDecoration;
	flags |= ImGuiWindowFlags_NoFocusOnAppearing;
	flags |= ImGuiWindowFlags_AlwaysAutoResize;
	flags |= ImGuiWindowFlags_NoNav;
	flags |= ImGuiWindowFlags_NoMove;

	if (ImGui::Begin("Example: Simple overlay", nullptr, flags))
	{
		// Create title and separator
		ImGui::Text("Performance Metrics");
		ImGui::Separator();

		// Calculate deltaTime and 10 frame average
		float tsl = timer.TimeSinceLast()  * 1000.0f;
		frameStepAverage += tsl;
		if(frameTimeAverageStepIndex++ >= frameTimeAverageStepCount)
		{
			maxFrameTime = tsl > maxFrameTime ? tsl : maxFrameTime;
			minFrameTime = tsl < minFrameTime ? tsl : minFrameTime;
			frameTimes[frameTimeIndex++] = frameStepAverage / static_cast<float>(frameTimeAverageStepCount);
			frameTimeIndex %= frameTimePlotCount;
			frameTimeAverageStepIndex = 0;
			frameStepAverage = 0;
		}

		ImGui::Text("Time per frame: %.2fms (%.f FPS)",tsl, 1000.0f / tsl);
		ImGui::PlotLines("", frameTimes, frameTimePlotCount, 0, "10 Frame average (ms)", minFrameTime, maxFrameTime < 16.0f ? 16.0f : maxFrameTime, {350,64});
	}

	flags = 0;
	ImGui::End();
#pragma endregion

	ImGui::Render();
}

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

	Style();

	ImGui_ImplSDL2_InitForSDLRenderer(window, renderer);
	ImGui_ImplSDLRenderer_Init(renderer);

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

		float s = (sinf(x += 0.03f) + 1.0f) * 0.5f;
		Pixel p = (1.0f - s) * 10 + s * 250;

		for (int i = 0; i < SCREEN_WIDTH * SCREEN_HEIGHT; i++)
			pixels[i] = p;

		DrawUI();

		SDL_UpdateTexture(frameBuffer, NULL, pixels, SCREEN_WIDTH * sizeof(uint32_t));
		SDL_RenderClear(renderer);
		SDL_RenderCopy(renderer, frameBuffer, NULL, NULL);
		ImGui_ImplSDLRenderer_RenderDrawData(ImGui::GetDrawData());
		SDL_RenderPresent(renderer);

	}

	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0;
}