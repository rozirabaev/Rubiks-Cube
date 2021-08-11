#pragma once   //maybe should be static class
#include "display.h"
#include "renderer.h"
#include "RubicsCube.h"



void mouse_callback(GLFWwindow* window, int button, int action, int mods)
{

	Renderer* rndr = (Renderer*)glfwGetWindowUserPointer(window);
	RubicsCube* scn = (RubicsCube*)rndr->GetScene();
	if (action == GLFW_PRESS && button == GLFW_MOUSE_BUTTON_RIGHT)
	{
		double x2, y2;
		glfwGetCursorPos(window, &x2, &y2);
		if (rndr->Picking(x2, y2)) {
			scn->rotate_picked_wall();
		}


	}
}
	void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
	{
		Renderer* rndr = (Renderer*)glfwGetWindowUserPointer(window);
		RubicsCube* scn = (RubicsCube*)rndr->GetScene();
		rndr->MoveCamera(0, scn->zTranslate, (-yoffset) * 1.2f);
	}
	
	void cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
	{
		Renderer* rndr = (Renderer*)glfwGetWindowUserPointer(window);
		RubicsCube* scn = (RubicsCube*)rndr->GetScene();

		rndr->UpdatePosition((float)xpos,(float)ypos);

			
			if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
			{
				rndr->MouseProccessing(GLFW_MOUSE_BUTTON_LEFT);
			}

	}

	void window_size_callback(GLFWwindow* window, int width, int height)
	{
		Renderer* rndr = (Renderer*)glfwGetWindowUserPointer(window);
		
		rndr->Resize(width,height);
		
	}
	
	void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
	{
		Renderer* rndr = (Renderer*)glfwGetWindowUserPointer(window);
		RubicsCube* scn = (RubicsCube*)rndr->GetScene();

		if (action == GLFW_PRESS || action == GLFW_REPEAT)
		{
			switch (key)
			{
			case GLFW_KEY_ESCAPE:
				glfwSetWindowShouldClose(window, GLFW_TRUE);
				break;
			case GLFW_KEY_SPACE:
				scn->change_clockwise();
				break;

			case GLFW_KEY_UP:

				rndr->MoveCamera(0, scn->zTranslate, 0.4f);
				break;
			case GLFW_KEY_DOWN:
				rndr->MoveCamera(0, scn->zTranslate, -0.4f);
				break;

			case GLFW_KEY_R:
				scn->add_motion(scn->RotateWall, scn->Right);
				break;

			case GLFW_KEY_L:
				scn->add_motion(scn->RotateWall, scn->Left);
				break;

			case GLFW_KEY_B:
				scn->add_motion(scn->RotateWall, scn->Back);
				break;

			case GLFW_KEY_F:
				scn->add_motion(scn->RotateWall, scn->Front);
				break;

			case GLFW_KEY_U:
				scn->add_motion(scn->RotateWall, scn->Up);
				break;

			case GLFW_KEY_D:
				scn->add_motion(scn->RotateWall, scn->Down);
				break;

			case GLFW_KEY_Z:
				scn->increase();
				break;

			case GLFW_KEY_A:
				scn->decrease();
				break;

			case GLFW_KEY_M:
				scn->random_rotation();
				break;


			default:
				break;
			}
		}
	}

	void Init(Display &display)
	{
		display.AddKeyCallBack(key_callback);
		display.AddMouseCallBacks(mouse_callback,scroll_callback,cursor_position_callback);
		display.AddResizeCallBack(window_size_callback);
	}
