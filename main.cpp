#include "InputManager.h"
#include "glm/glm.hpp"

int main(int argc,char *argv[])
{
	const int DISPLAY_WIDTH = 840;
	const int DISPLAY_HEIGHT = 840;
	const float CAMERA_ANGLE = 60.0f;
	const float NEAR = 1.0f;
	const float FAR = 100.0f;
	const int infoIndx = 2; 
	std::list<int> x, y;
	//x.push_back(DISPLAY_WIDTH / 2);
	//y.push_back(DISPLAY_HEIGHT / 2);
	Display display(DISPLAY_WIDTH, DISPLAY_HEIGHT, "OpenGL");
	Renderer* rndr = new Renderer(CAMERA_ANGLE, (float)DISPLAY_WIDTH / 1 / DISPLAY_HEIGHT, NEAR, FAR); // adding a camera
	RubicsCube* scn = new RubicsCube();  //initializing scene
	
	Init(display); //adding callback functions
	scn->Init();    //adding shaders, textures, shapes to scene
	rndr->Init(scn,x,y); // adding scene and viewports to the renderer
	display.SetRenderer(rndr);  // updating renderer in as a user pointer in glfw
	//For 2D rendering
	rndr->Create2Dmaterial(1);
	//Orthographic camera.
	rndr->AddCamera(glm::vec3(0,0,0),0,1,-1,1,infoIndx);
	rndr->BindViewport2D(infoIndx);

	while(!display.CloseWindow())
	{
		rndr->DrawAll();
		scn->Motion();
		display.SwapBuffers();
		display.PollEvents();		
	}
	delete scn;
	return 0;
}
