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

	void SliderFloat(std::string name, float& value, float min, float max);
	void SliderFloat(std::string windowName, std::string name, float& value, float min, float max);
	void SliderVector3(std::string name, Vector3& value, float min, float max);
	void SliderVector3(std::string windowName, std::string name, Vector3& value, float min, float max);

	void InputVector3(std::string name, Vector3& value);
	void InputVector3(std::string windowName, std::string name, Vector3& value);


private:
	SDL_Window* window;
	SDL_Renderer* renderer;

	bool isInitialized = false;
	bool windowActivated = false;
};