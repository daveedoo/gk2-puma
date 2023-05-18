#pragma once
#include "../Window/Window.h"
#include "../Camera.h"
#include "Scene.h"
#include "../gl/wrappers/FBO.h"
#include "../gl/wrappers/textures/Texture2D.h"
#include "../FPSClock.h"

/// <summary>
/// Class responsible for rendering everything (scene and the GUI) and handling the input.
/// </summary>
class Renderer
{
private:
	mini::FPSClock<> clock;
	Window& window;
	int framebufferWidth;
	int framebufferHeight;

	std::unique_ptr<Scene> scene;

	/// This method sends info to the `scene` object that frame size has changed
	void UpdateSceneFramebufferSize();

public:
	Renderer(Window& window);
	~Renderer();

	void Update();
	void Render();

private:
	void SetupGUI();
	void RenderGUI();
};
