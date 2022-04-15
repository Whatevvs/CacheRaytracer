#include <SDL.h>
#include <chrono>
#include <iostream>

typedef uint32_t Pixel;

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
using ms = std::chrono::duration<float, std::milli>;
int main(int argc, char* args[])
{
	SDL_Window* window = NULL;

	SDL_Init(SDL_INIT_VIDEO);
	window = SDL_CreateWindow("Cache: Ray Tracer", 250, 250, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	SDL_Texture* frameBuffer = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, SCREEN_WIDTH, SCREEN_HEIGHT);

	Pixel* pixels = new Pixel[SCREEN_WIDTH * SCREEN_HEIGHT];
	float x = 0.0f;

	float deltaTime = 0.0f;
	std::chrono::high_resolution_clock timer;
	while (true)
	{
		auto start = timer.now();

		x += deltaTime;
		float s = (sinf(x) + 1.0f) * 0.5f;
		Pixel p = (1.0f - s) * 10 + s * 250;

		for (int i = 0; i < SCREEN_WIDTH * SCREEN_HEIGHT; i++)
		{
			pixels[i] = p;
		}

		SDL_UpdateTexture(frameBuffer, NULL, pixels, SCREEN_WIDTH * sizeof(uint32_t));

		SDL_RenderClear(renderer);
		SDL_RenderCopy(renderer, frameBuffer, NULL, NULL);
		SDL_RenderPresent(renderer);

		auto stop = timer.now();
		deltaTime = std::chrono::duration_cast<ms>(stop - start).count() * 0.001f;

		float fps = (1.0f / deltaTime);
		std::cout << "FPS: " << fps << std::endl;
	}

	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0;
}