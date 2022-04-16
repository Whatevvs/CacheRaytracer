#include "AppWindow.h"
#include <cstdlib>

AppWindow::AppWindow(bool closeWindow, int windowWidth, int windowHeight) :
	m_windowWidth(windowWidth),
	m_windowHeight(windowHeight),
	m_windowSize(m_windowWidth* m_windowHeight),
	m_closeWindow(closeWindow),
	m_timer(new Timer())
{
	// WINDOW SETUP : Creating SDL objects
	m_window = SDL_CreateWindow("Cache Raytracer", 250, 250, windowWidth, windowHeight, SDL_WINDOW_SHOWN);
	m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	m_frameBufferTexture = SDL_CreateTexture(m_renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, windowWidth, windowHeight);

	// WINDOW SETUP : Initialize window and render with Dear ImGUI
	ImGui_ImplSDL2_InitForSDLRenderer(m_window, m_renderer);
	ImGui_ImplSDLRenderer_Init(m_renderer);

	// WINDOW SETUP : Create pixel buffer we can write to
	m_buffer = new Pixel[m_windowSize];

#ifdef _DEBUG
	assert(m_window != nullptr);
	assert(m_renderer != nullptr);
	assert(m_frameBufferTexture != nullptr);
	assert(m_buffer != nullptr);
#endif
}

AppWindow::~AppWindow()
{
	SDL_DestroyWindow(m_window);

	delete[] & m_buffer;
}

void AppWindow::Update()
{
	float i = 1.0f / RAND_MAX;

	srand(0);
	for (int i = 0; i < m_windowSize; i++)
		m_buffer[i] = rand() * i * 0xffffffff;

	Render();
}

void AppWindow::Render()
{
	SDL_UpdateTexture(m_frameBufferTexture, NULL, m_buffer, m_windowWidth * sizeof(uint32_t));

	DrawUI();

	SDL_SetRenderDrawColor(m_renderer, 255, 0, 255, 255);
	SDL_RenderClear(m_renderer);
	SDL_RenderCopy(m_renderer, m_frameBufferTexture, NULL, NULL);
	ImGui_ImplSDLRenderer_RenderDrawData(ImGui::GetDrawData());
	SDL_RenderPresent(m_renderer);
}

const int frameTimePlotCount = 32; // How many lines to plot
const int frameTimeAverageStepCount = 10; // How many frames to average

float maxFrameTime = 0.0f;
float minFrameTime = 10000000.0f;
float frameTimes[frameTimePlotCount]{};
float frameStepAverage = 0.0f;
int frameTimeIndex = 0;
int frameTimeAverageStepIndex = 0;

void AppWindow::DrawUI()
{
	ImGui_ImplSDLRenderer_NewFrame();
	ImGui_ImplSDL2_NewFrame();
	ImGui::NewFrame();

	ImGuiWindowFlags flags{ 0 };

#pragma region Performance Metrics Overlay
	ImGui::SetNextWindowPos(ImVec2(5, m_windowHeight - 5), ImGuiCond_Always, { 0.0f, 1.0f });
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
		float tsl = m_timer->TimeSinceLast() * 1000.0f;
		frameStepAverage += tsl;
		if (frameTimeAverageStepIndex++ >= frameTimeAverageStepCount)
		{
			maxFrameTime = tsl > maxFrameTime ? tsl : maxFrameTime;
			minFrameTime = tsl < minFrameTime ? tsl : minFrameTime;
			frameTimes[frameTimeIndex++] = frameStepAverage / static_cast<float>(frameTimeAverageStepCount);
			frameTimeIndex %= frameTimePlotCount;
			frameTimeAverageStepIndex = 0;
			frameStepAverage = 0;
		}

		ImGui::Text("Time per frame: %.2fms (%.f FPS)", tsl, 1000.0f / tsl);
		ImGui::PlotLines("", frameTimes, frameTimePlotCount, 0, "10 Frame average (ms)", minFrameTime, maxFrameTime < 16.0f ? 16.0f : maxFrameTime, { 350,64 });
	}

	flags = 0;
	ImGui::End();
#pragma endregion

	//ImGui::ShowDemoWindow();

	ImGui::Render();
}