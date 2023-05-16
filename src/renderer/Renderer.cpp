#include <gl/glew.h>
#include <exception>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/integer.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Renderer.h"
#include "../Config.h"
#include "../gl/wrappers/VAO.h"
#include "../gl/wrappers/Shader.h"
#include "../gl/wrappers/Program.h"
#include "../Window/Window.h"

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include "../Window/input/events/modded/MouseClickEvent.h"


Renderer::Renderer(Window& window) : window(window)
{
	this->window.MakeContextCurrent();

	if (glewInit() != GLEW_OK)
		throw std::exception("glewInit failed");

	this->window.GetFramebufferSize(this->framebufferWidth, this->framebufferHeight);
	this->window.SetInputEventHandler([&](const InputEvent& inputEvent)
		{
			if (!ImGui::GetIO().WantCaptureMouse)
				this->scene->HandleEvent(inputEvent);
		});
	this->window.SetFramebufferSizeEventHandler([&](const ResizeEvent& ev)
		{
			this->framebufferWidth = ev.width;
			this->framebufferHeight= ev.height;

			this->UpdateSceneFramebufferSize();
		});

	this->scene = std::make_unique<Scene>(this->framebufferWidth, this->framebufferHeight);

	this->SetupGUI();
}

void Renderer::SetupGUI()
{
	ImGui::CreateContext();
	ImGui::StyleColorsDark();
	ImGui_ImplGlfw_InitForOpenGL(this->window.GetRawWindow(), true);
	ImGui_ImplOpenGL3_Init("#version 450");
}


Renderer::~Renderer()
{
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
}

void Renderer::Update()
{
	clock.Query();
	double dt = clock.getFrameTime();
	this->scene->Update(dt);
}

void Renderer::UpdateSceneFramebufferSize()
{
	this->scene->SetFramebufferSize(this->framebufferWidth, this->framebufferHeight);
}

void Renderer::Render()
{
	glViewport(0, 0, this->framebufferWidth, this->framebufferHeight);
	this->scene->Render();

	//this->RenderGUI();
}

void Renderer::RenderGUI()
{
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();

	static const float GUI_WIDTH = 400.f;
	ImGui::ShowDemoWindow();

	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}
