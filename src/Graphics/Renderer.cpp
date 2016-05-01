#include <Ice/Graphics/Renderer.hpp>
#include <Ice/Graphics/Vertex.hpp>
#include <Ice/System/Window.hpp>
#include <Ice/Maths/Maths.hpp>

namespace Ice
{
	Renderer::Renderer()
	{
		// Set the default clear colour.
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

		// Tell OpenGL which face to cull.
		// glFrontFace( GL_CW    );
		// glCullFace ( GL_FRONT );

		_shader = new Shader("data/shaders/basic.vert",
			"data/shaders/basic.frag");

		_shader->RegisterUniform("model");
		_shader->RegisterUniform("view");
		_shader->RegisterUniform("projection");

		std::vector<Vertex> vertices = {
			//  Positions                Normals               Colours       Texture Coordinates
			{ { +0.5f, +0.5f, +0.0f },{ 0.0f, 0.0f, 1.0f }, Colour_White,{ 1.0f, 0.0f } },
			{ { +0.5f, -0.5f, +0.0f },{ 0.0f, 0.0f, 1.0f }, Colour_Red  ,{ 1.0f, 1.0f } },
			{ { -0.5f, -0.5f, +0.0f },{ 0.0f, 0.0f, 1.0f }, Colour_Green,{ 0.0f, 1.0f } },
			{ { -0.5f, +0.5f, +0.0f },{ 0.0f, 0.0f, 1.0f }, Colour_Blue ,{ 0.0f, 0.0f } },
		};

		std::vector<GLuint> indices = {
			0, 1, 3,
			3, 1, 2
		};

		std::vector<Texture> textures = { load_texture("data/test/box.jpg", TextureType::Diffuse) };

		//_cube_model.loadModel

		_cube.SetTranslation({ 0.0f, 0.0f, 0.0f });
		_cube.SetScale({ 1.0f, 1.0f, 1.0f });
		// _cube.SetRotation   ( { 2.0f, 1.0f, 0.0f } );

		// _view = look_at( { 1.0f, 2.0f, 4.0f },
		//                  { 1.0f, 0.0f, 0.0f },
		//                  { 0.0f, 1.0f, 0.0f } );

		_view = translate({ 0.0f, 0.0f, 0.0f });
	}

	Renderer::~Renderer()
	{
		delete _shader;
	}

	void Renderer::Render(const RenderContext& context)
	{
		context.wire_frame
			? glPolygonMode(GL_FRONT_AND_BACK, GL_LINE)
			: glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

		context.has_depth
			? glEnable(GL_DEPTH_TEST)
			: glDisable(GL_DEPTH_TEST);

		_cube.SetTranslation({ sinf(glfwGetTime()), cosf(glfwGetTime()), 0.0f });
		// _cube.SetScale      ( { sinf( glfwGetTime() ), cosf( glfwGetTime() ), 0.0f } );

		// _view = translate( { sinf( glfwGetTime() ), cosf( glfwGetTime() ), -2.0f } );

		_shader->Bind();
		_shader->UpdateUniform("model", _cube.GetTransform());
		_shader->UpdateUniform("view", _view);
		_shader->UpdateUniform("projection", context.projection);

		//_cube_model.Draw(_shader);
	}

	void Renderer::Clear()
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}
}