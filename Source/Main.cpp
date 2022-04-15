#include <SDL.h>
#include "../Timer.h"
#include <iostream>

typedef uint32_t Pixel;

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
int main(int argc, char* args[])
{
	SDL_Window* window = NULL;

	SDL_Init(SDL_INIT_VIDEO);
	window = SDL_CreateWindow("Cache Raytracer", 250, 250, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	SDL_Texture* frameBuffer = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, SCREEN_WIDTH, SCREEN_HEIGHT);

	Pixel* pixels = new Pixel[SCREEN_WIDTH * SCREEN_HEIGHT];

	Timer timer;

	while (true)
	{
		static float x = 0.0f;

		float s = (sinf(x += 0.03f) + 1.0f) * 0.5f;
		Pixel p = (1.0f - s) * 10 + s * 250;

		for (int i = 0; i < SCREEN_WIDTH * SCREEN_HEIGHT; i++)
			pixels[i] = p;

		SDL_UpdateTexture(frameBuffer, NULL, pixels, SCREEN_WIDTH * sizeof(uint32_t));

		SDL_RenderClear(renderer);
		SDL_RenderCopy(renderer, frameBuffer, NULL, NULL);
		SDL_RenderPresent(renderer);

		printf("Frametime: %fs\n", timer.TimeSinceLast());
	}

	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0;
}