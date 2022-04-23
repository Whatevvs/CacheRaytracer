#pragma once

class ImguiHandler
{
public:
	static ImguiHandler* GetInstance()
	{
		static ImguiHandler instance;
		return &instance;
	}

	void Initialize(SDL_Window* window, SDL_Renderer* renderer);
	void Update();
	void Draw();

	// Window creation & Activation
	void CreateWindow(std::string title);
	void CreateWindow(Vector2 position, Vector2 size, std::string title);
	void ActivateWindow(std::string windowName);
	void DisableWindow();

	// Window Interaction
	void DrawText(std::string text);
	void DrawText(std::string windowName, std::string text);

private:
	SDL_Window* window;
	SDL_Renderer* renderer;

	bool isInitialized = false;
	bool windowActivated = false;
};