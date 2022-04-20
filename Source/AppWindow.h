#pragma once
#include "SDL.h"
#include "Timer.h"

typedef uint32_t Pixel;

class AppWindow
{
	SDL_Window* m_window { nullptr };
	SDL_Renderer* m_renderer { nullptr };
	SDL_Texture* m_frameBufferTexture { nullptr };

	const int m_windowWidth { 1280 };
	const int m_windowHeight { 720 };
	const int m_windowSize { 1280 * 720 };

	Timer* m_timer { nullptr };
	Pixel* m_buffer { nullptr };
	bool& m_closeWindow;

	float m_lastFrameTime { 0 };

public:
	AppWindow(bool closeWindow, int windowWidth = 1280, int windowHeight = 720);
	~AppWindow();

	void Update();
	void DrawUI();
	void Render();

	float GetDeltaTime() { return m_lastFrameTime; };
	Pixel* GetScreenBuffer() { return m_buffer; };
};