#include "Renderer/Renderer.h"
#include "glfw3.h"
#include "glm.hpp"
#include "gtc/matrix_transform.hpp"
#include "gtc/type_ptr.hpp"
#include "BaseGame.h"
#include "Window/_window.h"
#include "Imgui/imgui.h"
#include "Imgui/imgui_impl_glfw_gl3.h"
#include "Imgui/Test.h"
#include "Texture/Texture.h"
#include <iostream>
namespace Engine
{
	void base_game::Play(int width, int height, const char* name)
	{
		/* Initialize the library */
		if (!glfwInit())
			glfwTerminate();

		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		/* Create a windowed mode _window and its OpenGL context */
		window* myWindow = new window(width, height, name, NULL, NULL);

		if (!myWindow->get())
		{
			glfwTerminate();
		}

		/* Make the _window's context current */
		myWindow->makeContextCurrent(myWindow->get());

		glfwSwapInterval(1);

		std::cout << glGetString(GL_VERSION) << std::endl;
		{
			GLCall(glEnable(GL_BLEND));
			GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

			Renderer renderer;

			ImGui::CreateContext();
			ImGui_ImplGlfwGL3_Init(myWindow->get(), true);
			ImGui::StyleColorsDark();

			Test* currentTest = nullptr;
			TestMenu* testMenu = new TestMenu(currentTest);
			currentTest = testMenu;

			testMenu->RegisterTest<TestTexture2D>("2D Texture");

			while (!myWindow->windowShouldClose(myWindow->get()))
			{
				GLCall(glClearColor(0.0f, 0.0f, 0.0f, 1.0f));
				renderer.Clear();

				ImGui_ImplGlfwGL3_NewFrame();
				if (currentTest)
				{
					currentTest->OnUpdate(0.0f);
					currentTest->OnRender();
					ImGui::Begin("Test");
					if (currentTest != testMenu && ImGui::Button("<-"))
					{
						delete currentTest;
						currentTest = testMenu;
					}
					currentTest->OnImGuiRender();
					ImGui::End();
				}

				ImGui::Render();
				ImGui_ImplGlfwGL3_RenderDrawData(ImGui::GetDrawData());

				glfwSwapBuffers(myWindow->get());
				glfwPollEvents();
			}
			delete currentTest;
		}
		ImGui_ImplGlfwGL3_Shutdown();
		ImGui::DestroyContext();
		glfwTerminate();
	}
}