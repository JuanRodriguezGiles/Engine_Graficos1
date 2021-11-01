#pragma once
#include "Export.h"
#include "Window/_window.h"
#include "VertexBuffer/VertexBuffer.h"
#include "VertexBufferLayout/VertexBufferLayout.h"
#include "Texture/Texture.h"
#include <memory>
namespace Engine
{
	class ENGINE_API base_game
	{
	public:
		window* myWindow = nullptr;
		glm::vec3 m_TranslationA, m_TranslationB;
		base_game();
		void Play(int width, int height, const char* name);
		void Init(int width, int height, const char* name);
		virtual void Update() = 0;
		void Draw();
		void DeInit();
	private:
		std::unique_ptr<VertexArray> m_VAO;
		std::unique_ptr<VertexBuffer> m_VertexBuffer;
		std::unique_ptr<IndexBuffer> m_IndexBuffer;
		std::unique_ptr<Shader> m_Shader;
		std::unique_ptr<Texture> m_Texture;

		glm::mat4 m_Proj, m_View;
	};
}