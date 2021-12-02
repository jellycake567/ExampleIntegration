#include "Graphics.h"
#include <math.h>
#include "Utilities.h"
#include "ShaderProgram.h"
#include <iostream>
#include "glm.hpp"
//We need to bring this in for transform functions like 'LookAt' and 'Rotate'
#include "ext/matrix_transform.hpp"
//We need this for 'Perspective' for our projection matrix.
#include "ext/matrix_clip_space.hpp"
#include <cstdlib>;
#include "AS.h"
#include "asSubclass.h"
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
float number = 50.0f;
int main()
{
	asSubclass* ASEngine = new asSubclass();
	ASEngine->Load();
	GLFWwindow* window;

	if (!glfwInit())
		return -1;	//glfw failed to initialise.

	window = glfwCreateWindow(1280, 720, "UI creation/modification using Angelscript", nullptr, nullptr);
	
	if (!window)             
	{
		glfwTerminate();
		return -1;
	}

	//We have to tell glfw to use the OpenGL context from the window.
	//This stuff can be relevant if you have multiple windows - you're
	//telling OpenGL which one to apply render commands to.
	//But if we only have one window we just do this once at the start.
	glfwMakeContextCurrent(window);

	//This is where GLAD gets set up. After this point we can use openGL functions.
	if (!gladLoadGL())
		return -1;


	//Load our basic shader.
	ShaderProgram test("Simple.vsd", "Simple.fsd");

	glfwSwapInterval(1);	//This is essentially turning on vsync.

	//These two buffers represent the vertices of our cube and then the indices.
	GLuint cubeVerts;
	GLuint cubeIndices;

	//This is the vertex array object - it contains 'metadata' for our vert/index buffers, above.
	GLuint cubeVAO;

	glGenBuffers(1, &cubeVerts);	//Generate the OpenGL handle for the vertices.
	glGenBuffers(1, &cubeIndices);
	glGenVertexArrays(1, &cubeVAO);


	//THIS IS NEW! If we don't enable depth testing our cube will look all busted.
	glEnable(GL_DEPTH_TEST);

	//The vertices themselves. First the position (3 floats) then the colour (also 3 floats)
	int vertSize = 9;	//The number of floats per vert
	int vertCount = 24;	//The number of verts total
	float vertexPosData[] = { 0, 0, 1,     1, 0, 0,     0, 0, 1,
							  0, 1, 1,     1, 0, 0,     0, 0, 1,
							  1, 1, 1,     1, 0, 0,     0, 0, 1,
							  1, 0, 1,     1, 0, 0,     0, 0, 1,
													    
							  0, 0, 0,     0, 0, 1,     0, 0,-1,
							  0, 1, 0,     0, 0, 1,     0, 0,-1,
							  1, 1, 0,     0, 0, 1,     0, 0,-1,
							  1, 0, 0,     0, 0, 1,     0, 0,-1,
													    
							  0, 0, 0,     0, 1, 0,    -1, 0, 0,
							  0, 0, 1,     0, 1, 0,    -1, 0, 0,
							  0, 1, 1,     0, 1, 0,    -1, 0, 0,
							  0, 1, 0,     0, 1, 0,    -1, 0, 0,
													    
							  1, 0, 0,     0, 1, 1,     1, 0, 0,
							  1, 0, 1,     0, 1, 1,     1, 0, 0,
							  1, 1, 1,     0, 1, 1,     1, 0, 0,
							  1, 1, 0,     0, 1, 1,     1, 0, 0,
													    
							  0, 0, 0,     1, 1, 0,     0,-1, 0,
							  0, 0, 1,     1, 1, 0,     0,-1, 0,
							  1, 0, 1,     1, 1, 0,     0,-1, 0,
							  1, 0, 0,     1, 1, 0,     0,-1, 0, 
													    
							  0, 1, 0,     1, 0, 1,     0, 1, 0,
							  0, 1, 1,     1, 0, 1,     0, 1, 0,
							  1, 1, 1,     1, 0, 1,     0, 1, 0,
							  1, 1, 0,     1, 0, 1,     0, 1, 0,
	};

	//These are our indices - every three indices is a triangle, and refers to a position (a row of numbers) in the above vert array.
	unsigned short indices[] = {
		0, 1, 2, 2, 3, 0,
		4, 5, 6, 6, 7, 4,
		8, 9, 10, 10, 11, 8,
		12, 13, 14, 14, 15, 12,
		16, 17, 18, 18, 19, 16,
		20, 21, 22, 22, 23, 20
	};

	glm::vec3 cameraPos = { 0, 2, 15 };
	glm::vec3 lightPos = { 2, 2, 2 };

	float ambientLightLevel = 0.1f;

	//We upload our vertex and index buffers like normal, now:
	glBindBuffer(GL_ARRAY_BUFFER, cubeVerts);	//Bind the triangle buffer to the GL_ARRAY_BUFFER type.
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertSize * vertCount, vertexPosData, GL_STATIC_DRAW);	//Upload the actual data to the GPU.
	glBindBuffer(GL_ARRAY_BUFFER, 0); //Unbind (good practice).


	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, cubeIndices);	//Now bind the index buffer to this (different!) target.
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned short) * 36, indices, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	//We're done uploading - now we want to 'record' our VAO.


	glBindVertexArray(cubeVAO);	//By binding our VAO, we start recording.
	glBindBuffer(GL_ARRAY_BUFFER, cubeVerts);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, cubeIndices);
	
	//We're using the first and second attribute in our simple shader,
	//meaning position and colour. So we enable both attribute arrays here.
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, vertSize * sizeof(float), (const void*)(0 * sizeof(float)));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, vertSize * sizeof(float), (const void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, vertSize * sizeof(float), (const void*)(6 * sizeof(float)));

	glBindVertexArray(0);	//We're done recording, we unbind the VAO.

	//Unbind our vert/index buffers
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);


	//Tracking time here so we can fade the background colour around.
	float time = 0;
	glClearColor(0.1f, 0.1f, 0.1f, 1);

	bool spaceBarDown;	//For detecting initial press of the space bar, for shader reloading.


	//ImGui stuff

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();

	// Setup Dear ImGui style
	ImGui::StyleColorsDark();
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init("#version 150");
	ImGui_ImplOpenGL3_Init("#version 150");
	
	ImVec4 clear_color = ImVec4(0.35f, 0.40f, 0.42f, 1.00f);

	while (!glfwWindowShouldClose(window))
	{
		//ImGui stuff
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		ImGui::ShowStyleEditor();
		
		static float f = 0.0f;
		static int counter = 0;

		glClearColor(clear_color.x* clear_color.w, clear_color.y* clear_color.w, clear_color.z* clear_color.w, clear_color.w);
		glClear(GL_COLOR_BUFFER_BIT);


		ASEngine->Update();


		if (glfwGetKey(window, GLFW_KEY_GRAVE_ACCENT) == GLFW_PRESS)
		{
			ASEngine->Load();
		}
		if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		{
			lightPos.y += 0.1f;
		}
		if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		{
			lightPos.y -= 0.1f;
		}
		if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		{
			lightPos.x -= 0.1f;
		}
		if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		{
			lightPos.x += 0.1f;
		}

		test.UseShader();

		bool spaceBarDownNew = glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS;
		if (spaceBarDownNew && !spaceBarDown) //It is newly pressed, so reload our shaders.
		{
			//Reload our shaders...
			std::cout << std::endl << "Reloading shaders..." << std::endl;
			test = ShaderProgram("Simple.vsd", "Simple.fsd");
		}
		spaceBarDown = spaceBarDownNew;


		time += 0.01f;
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//We 'use' our shader - that means that draw commands make use of it.
		//Since we only have one shader in our program and we're always using
		//it, we *could* do this once at the start. But more complex programs
		//will have to switch up between shaders each render pass.
		

		float rotation = time;

		//We need to send our model-view-projection matrix to the shader, so now we create it:

		//rotation matrix will be our model matrix for now.
		glm::mat4 rotMat = glm::rotate(glm::mat4(1), rotation, glm::vec3(0, 1, 0));
	
		//We build our view matrix by 'looking at' position 0, 0, 0, from position 10, 10, 10. The last bit is the up vector.
		glm::mat4 view = glm::lookAt(cameraPos, glm::vec3(0, 0.5f, 0), glm::vec3(0, 1, 0));
		
		//We build our projection as a perspective camera with a pi/4 (90 degrees) vertical fov, a dodgy hardcoded aspect ratio,
		//and some probably-reasonable near and far clip planes.
		glm::mat4 projection = glm::perspective(glm::pi<float>() * 0.25f, 16 / 9.f, 0.1f, 100.f);


		test.SetUniform("LightPosition", lightPos);
		test.SetUniform("CameraPosition", cameraPos);
		test.SetUniform("AmbientLightLevel", ambientLightLevel);

		glBindVertexArray(cubeVAO);
		//for (int x = -2; x <= 2; x++)
		//{
		//	for (int y = -2; y <= 2; y++)
		//	{
				glm::mat4 modelTransform = glm::translate(glm::mat4(1), glm::vec3(0, 0, 0)) * rotMat;
				//Set the matrices.
				test.SetUniform("mvpMatrix", projection * view * modelTransform);
				test.SetUniform("modelMatrix", modelTransform);
				//Our draw logic is now very simplified by using the VAO - we just bind it and all the stuff we 'recorded' earlier
				//happens automatically!
				//Because we're doing an indexed draw, this is a different command. GL_UNSIGNED_SHORT is used because the indices are 16 bit ints.
				//The last argument means 'offset into the index array' - since we're starting at the start, use zero.
				glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_SHORT, 0);
		//	}
		//}
		glBindVertexArray(0);
		
		
		// Rendering
		ImGui::Render();
		int display_w, display_h;
		glfwGetFramebufferSize(window, &display_w, &display_h);
		glViewport(0, 0, display_w, display_h);
	
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());


		//That's it for rendering! Swapping the buffers means we
		//take what we've rendered and present it to the player.
		//More on this later.
		glfwSwapBuffers(window);

		//This tells GLFW to check for whether keys are down, mice have
		//moved, etc.
		glfwPollEvents();
		
	}


	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	//~fin~
	glfwTerminate();
	return 0;
}