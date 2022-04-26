#include "Precomp.h"
#include <SDL.h>

void ImguiHandler::Initialize(SDL_Window* win, SDL_Renderer* ren)
{
	if (!isInitialized)
	{
		isInitialized = true;
		window = win;
		renderer = ren;

		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO(); (void)io;
		ImGui_ImplSDL2_InitForSDLRenderer(window, renderer);
		ImGui_ImplSDLRenderer_Init(renderer);
	}
}

void ImguiHandler::Update()
{
	ImGui_ImplSDLRenderer_NewFrame();
	ImGui_ImplSDL2_NewFrame();
	ImGui::NewFrame();
}

void ImguiHandler::Draw()
{
	if (windowActivated)
	{
		windowActivated = false;
		printf("Error 'ImguiHandler': When manually activating windows, make sure to disable them as well.\n");
		DisableWindow();
	}

	ImGui::Render();
	ImGui_ImplSDLRenderer_RenderDrawData(ImGui::GetDrawData());
}

void ImguiHandler::CreateWindow(std::string title)
{
	ImGui::Begin(title.c_str(), nullptr);
	ImGui::End();
}

void ImguiHandler::CreateWindow(Vector2 position, Vector2 size, std::string title)
{
	ImGui::SetNextWindowPos(ImVec2(position.x, position.y));
	ImGui::SetNextWindowSize(ImVec2(size.x, size.y));
	ImGui::Begin(title.c_str(), nullptr);
	ImGui::End();
}

void ImguiHandler::ActivateWindow(std::string windowName)
{
	windowActivated = true;
	ImGui::Begin(windowName.c_str(), nullptr);
}

void ImguiHandler::DisableWindow()
{
	windowActivated = false;
	ImGui::End();
}

void ImguiHandler::DrawText(std::string text)
{
	ImGui::Text(text.c_str());
}

void ImguiHandler::DrawText(std::string windowName, std::string text)
{
	ImGui::Begin(windowName.c_str(), nullptr);
	ImGui::Text(text.c_str());
	ImGui::End();
}

void ImguiHandler::SliderFloat(std::string name, float& value, float min, float max)
{
	ImGui::SliderFloat(name.c_str(), &value, min, max, "%.1f");
}

void ImguiHandler::SliderFloat(std::string windowName, std::string name, float& value, float min, float max)
{
	ImGui::Begin(windowName.c_str(), nullptr);
	ImGui::SliderFloat(name.c_str(), &value, min, max, "%.1f");
	ImGui::End();
}