/*************************************************************************
> File Name: main.cpp
> Project Name: Hearthstone++
> Author: Chan-Ho Chris Ohk
> Purpose: Main entry of Hearthstone++ GUI program.
> Created Time: 2018/02/04
> Copyright (c) 2017, Chan-Ho Chris Ohk
*************************************************************************/
#include <GLFW/glfw3.h>
#include <imgui/imgui.h>

#include <cstdlib>
#include <string>

void Setup(GLFWwindow* window);
void Render(ImDrawData* drawData);

static struct LoginSceneData
{
    ImGuiWindowFlags flags = 0;

    bool opened = true;

    float positionX = 0.0f;
    float positionY = 0.0f;

    float width = 200.0f;
    float height = 350.0f;

    char nick[32] = {""};
    char password[32] = {""};
    std::string info;
} data;

int main()
{
	if (!glfwInit())
	{
		exit(EXIT_FAILURE);
	}

	static GLFWwindow* window{ glfwCreateWindow(800, 600, "Hearthstone++ simple GUI", nullptr, nullptr) };

	if (!window)
	{
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	glfwMakeContextCurrent(window);

	// Close window on pressing ESC
	glfwSetKeyCallback(window, [](GLFWwindow* window, int key, int, int action, int)
	{
		if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		{
			glfwSetWindowShouldClose(window, GL_TRUE);
		}
	});

	Setup(window);

	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	while (!glfwWindowShouldClose(window))
	{
		glClear(GL_COLOR_BUFFER_BIT);

		glfwPollEvents();

		// Use ImGui functions between here and Render()
		ImGui::NewFrame();

		// This creates a window
        ImGui::SetNextWindowPos(ImVec2(data.positionX, data.positionY));
        ImGui::Begin("Login", &data.opened, ImVec2(data.width, data.height),
                     0.0f, data.flags);
        {
            // Info
            ImGui::TextColored(ImVec4(1.0f, 0.0f, 0.0f, 1.0f),
                               data.info.c_str());

            ImGui::NewLine();

            // Nick
            ImGui::TextColored(ImVec4(1.0f, 1.0f, 1.0f, 1.0f), "Nick:");
            static bool focusHere = true;
            if (focusHere)
            {
                ImGui::SetKeyboardFocusHere();
                focusHere = false;
            }
            ImGui::InputText("##Nick", data.nick, IM_ARRAYSIZE(data.nick));

            ImGui::NewLine();

            // Password
            ImGui::TextColored(ImVec4(1.0f, 1.0f, 1.0f, 1.0f), "Password:");
            if (ImGui::InputText("##Password", data.password,
                                 IM_ARRAYSIZE(data.password),
                                 ImGuiInputTextFlags_Password |
                                     ImGuiInputTextFlags_EnterReturnsTrue))
            {
                
            }

            ImGui::NewLine();

            // Check Login
            if (ImGui::Button("Login"))
            {
                
            }

            ImGui::NewLine();

            // Create Account
            if (ImGui::Button("Create Account"))
            {
                
            }

            ImGui::NewLine();

            // Forgot Password
            if (ImGui::Button("Forgot Password"))
            {
                
            }
        }
        ImGui::End();

		// ImGui functions end here
		ImGui::Render();

		glfwSwapBuffers(window);
	}

	glfwDestroyWindow(window);
	glfwTerminate();

	exit(EXIT_SUCCESS);
}

/*
	Initialize the ImGuiIO struct.
	The ImGuiIO struct is the main configuration and
	I/O between your application and ImGui.
*/
void Setup(GLFWwindow* window)
{
	unsigned char* pixels;
	int width, height, displayWidth, displayHeight;
	GLuint g_fontTexture;

	ImGui::CreateContext();
	ImGuiIO& io{ ImGui::GetIO() };

	io.Fonts->GetTexDataAsAlpha8(&pixels, &width, &height);

	// Upload texture to graphics system
	GLint lastTexture;
	glGetIntegerv(GL_TEXTURE_BINDING_2D, &lastTexture);
	glGenTextures(1, &g_fontTexture);
	glBindTexture(GL_TEXTURE_2D, g_fontTexture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_ALPHA, width, height, 0, GL_ALPHA, GL_UNSIGNED_BYTE, pixels);

	// Get display size
	glfwGetWindowSize(window, &width, &height);
	glfwGetFramebufferSize(window, &displayWidth, &displayHeight);

	io.DisplaySize = ImVec2(static_cast<float>(width), static_cast<float>(height));
	io.RenderDrawListsFn = Render;
	io.Fonts->TexID = reinterpret_cast<void *>(static_cast<intptr_t>(g_fontTexture));

	// Restore state
	glBindTexture(GL_TEXTURE_2D, lastTexture);
}

/*
	Boilerplate function for OpenGL 2.0 rendering.
	
	This function isn't written by us, but is mandatory
	boilerplate from the library. It can be copy/pasted
	into your projects, but should really be part of the
	library itself?
*/
void Render(ImDrawData* drawData)
{
	ImGuiIO& io{ ImGui::GetIO() };
	const int fbWidth{ static_cast<int>(io.DisplaySize.x * io.DisplayFramebufferScale.x) };
	const int fbHeight{ static_cast<int>(io.DisplaySize.y * io.DisplayFramebufferScale.y) };

	drawData->ScaleClipRects(io.DisplayFramebufferScale);

	GLint lastTexture;
	glGetIntegerv(GL_TEXTURE_BINDING_2D, &lastTexture);
	GLint lastViewport[4];
	glGetIntegerv(GL_VIEWPORT, lastViewport);
	
	glPushAttrib(GL_ENABLE_BIT | GL_COLOR_BUFFER_BIT | GL_TRANSFORM_BIT);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDisable(GL_CULL_FACE);
	glDisable(GL_DEPTH_TEST);
	glEnable(GL_SCISSOR_TEST);
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);
	glEnable(GL_TEXTURE_2D);

	// Setup viewport, orthographic projection matrix
	glViewport(0, 0, static_cast<GLsizei>(fbWidth), static_cast<GLsizei>(fbHeight));
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	glOrtho(0.0f, io.DisplaySize.x, io.DisplaySize.y, 0.0f, -1.0f, +1.0f);
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();

	// Render command lists
#define OFFSETOF(TYPE, ELEMENT) ((size_t)&(((TYPE*)0)->ELEMENT))
	for (int n = 0; n < drawData->CmdListsCount; n++)
	{
		const ImDrawList* cmdList = drawData->CmdLists[n];
		const unsigned char* vertexBuffer = reinterpret_cast<const unsigned char*>(&cmdList->VtxBuffer.front());
		const ImDrawIdx* indexBuffer = &cmdList->IdxBuffer.front();
		glVertexPointer(2, GL_FLOAT, sizeof(ImDrawVert), (void*)(vertexBuffer + OFFSETOF(ImDrawVert, pos)));
		glTexCoordPointer(2, GL_FLOAT, sizeof(ImDrawVert), (void*)(vertexBuffer + OFFSETOF(ImDrawVert, uv)));
		glColorPointer(4, GL_UNSIGNED_BYTE, sizeof(ImDrawVert), (void*)(vertexBuffer + OFFSETOF(ImDrawVert, col)));

		for (int cmds = 0; cmds < cmdList->CmdBuffer.size(); ++cmds)
		{
			const ImDrawCmd* pCmd = &cmdList->CmdBuffer[cmds];
			if (pCmd->UserCallback)
			{
				pCmd->UserCallback(cmdList, pCmd);
			}
			else
			{
				glBindTexture(GL_TEXTURE_2D, static_cast<GLuint>(reinterpret_cast<intptr_t>(pCmd->TextureId)));
				glScissor(static_cast<int>(pCmd->ClipRect.x), static_cast<int>(fbHeight - pCmd->ClipRect.w), static_cast<int>(pCmd->ClipRect.z - pCmd->ClipRect.x), static_cast<int>(pCmd->ClipRect.w - pCmd->ClipRect.y));
				glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(pCmd->ElemCount), sizeof(ImDrawIdx) == 2 ? GL_UNSIGNED_SHORT : GL_UNSIGNED_INT, indexBuffer);
			}
			indexBuffer += pCmd->ElemCount;
		}
	}
#undef OFFSETOF

	// Restore modified state
	glDisableClientState(GL_COLOR_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);
	glBindTexture(GL_TEXTURE_2D, lastTexture);
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glPopAttrib();
	glViewport(lastViewport[0], lastViewport[1], static_cast<GLsizei>(lastViewport[2]), static_cast<GLsizei>(lastViewport[3]));
}