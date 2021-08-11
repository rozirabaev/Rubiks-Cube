#include "RubicsCube.h"
#include <iostream>
#include "GL/glew.h"
#include <random>;

static void printMat(const glm::mat4 mat)
{
	std::cout<<" matrix:"<<std::endl;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
			std::cout<< mat[j][i]<<" ";
		std::cout<<std::endl;
	}
}

RubicsCube::RubicsCube() : Scene()
{
	rotation_speed = 1;
	clockwise = true;
	rotation = 0;
	locked = -1;
	
}


void RubicsCube::Init()
{		
	unsigned int texIDs[3] = { 0 , 1, 0};
	unsigned int slots[3] = { 0 , 1, 0 };
	
	AddShader("../res/shaders/pickingShader2");	
	AddShader("../res/shaders/basicShader2");
	
	AddTexture("../res/textures/plane.png",2);
	int x;
	int z = -2;
	int y = 2;
	for (int j = 0; j < 3; j++) {
		x = -2;
		y = -2;
		for (int i = 0; i < 3; i++) {
			AddShape(Cube, -1, TRIANGLES);
			pickedShape = i+9*j;
			ShapeTransformation(xTranslate, x);
			ShapeTransformation(yTranslate, y);
			ShapeTransformation(zTranslate, z);
			x = x + 2;
		}
		x = -2;
		y = 0;
		for (int i = 3; i < 6; i++) {
			AddShape(Cube, -1, TRIANGLES);
			pickedShape = i + 9 * j;
			ShapeTransformation(xTranslate, x);
			ShapeTransformation(yTranslate, y);
			ShapeTransformation(zTranslate, z);
			x = x + 2;
		}
		y = 2;
		x = -2;
		for (int i = 6; i < 9; i++) {
			AddShape(Cube, -1, TRIANGLES);
			pickedShape = i + 9 * j;
			ShapeTransformation(xTranslate, x);
			ShapeTransformation(yTranslate, y);
			ShapeTransformation(zTranslate, z);
			x = x + 2;
		}
		z = z + 2;
	}
	pickedShape = -1;

	for (int i = 0; i < 27; i++) {
		cubes[i] = i;
	}
	
}

void RubicsCube:: update_cubes(int w) {
	std::vector <int> *tmp = new std::vector<int>(27);
	for (int i = 0; i < 27; i++)
		tmp->at(i) = cubes[i];
	switch(w){
	case Up: 
		if (clockwise) {
			for (int i = 0; i < 3; i++) {
				cubes[side_up[i][0]] = tmp->at(side_up[0][2 - i]);
				cubes[side_up[i][1]] = tmp->at(side_up[1][2 - i]);
				cubes[side_up[i][2]] = tmp->at(side_up[2][2 - i]);
			}
		}
		else {
			for (int i = 0; i < 3; i++) {
				cubes[side_up[i][0]] = tmp->at(side_up[2][i]);
				cubes[side_up[i][1]] = tmp->at(side_up[1][i]);
				cubes[side_up[i][2]] = tmp->at(side_up[0][i]);
			}
		}
		break;
	case Down:
		if (clockwise) {
			for (int i = 0; i < 3; i++) {
				cubes[side_down[i][0]] = tmp->at(side_down[0][2 - i]);
				cubes[side_down[i][1]] = tmp->at(side_down[1][2 - i]);
				cubes[side_down[i][2]] = tmp->at(side_down[2][2 - i]);
			}
		}
		else {
			for (int i = 0; i < 3; i++) {
				cubes[side_down[i][0]] = tmp->at(side_down[2][i]);
				cubes[side_down[i][1]] = tmp->at(side_down[1][i]);
				cubes[side_down[i][2]] = tmp->at(side_down[0][i]);
			}
		}
		break;

	case Left:
		if (clockwise) {
			for (int i = 0; i < 3; i++) {
				cubes[side_left[i][0]] = tmp->at(side_left[0][2 - i]);
				cubes[side_left[i][1]] = tmp->at(side_left[1][2 - i]);
				cubes[side_left[i][2]] = tmp->at(side_left[2][2 - i]);
			}
		}
		else {
			for (int i = 0; i < 3; i++) {
				cubes[side_left[i][0]] = tmp->at(side_left[2][i]);
				cubes[side_left[i][1]] = tmp->at(side_left[1][i]);
				cubes[side_left[i][2]] = tmp->at(side_left[0][i]);
			}
		}
		break;

	case Right:
		if (clockwise) {
			for (int i = 0; i < 3; i++) {
				cubes[side_right[i][0]] = tmp->at(side_right[0][2 - i]);
				cubes[side_right[i][1]] = tmp->at(side_right[1][2 - i]);
				cubes[side_right[i][2]] = tmp->at(side_right[2][2 - i]);
			}
		}
		else {
			for (int i = 0; i < 3; i++) {
				cubes[side_right[i][0]] = tmp->at(side_right[2][i]);
				cubes[side_right[i][1]] = tmp->at(side_right[1][i]);
				cubes[side_right[i][2]] = tmp->at(side_right[0][i]);
			}
		}
		break;

	case Front:
		if (clockwise) {
			for (int i = 0; i < 3; i++) {
				cubes[side_front[i][0]] = tmp->at(side_front[0][2 - i]);
				cubes[side_front[i][1]] = tmp->at(side_front[1][2 - i]);
				cubes[side_front[i][2]] = tmp->at(side_front[2][2 - i]);
			}
		}
		else {
			for (int i = 0; i < 3; i++) {
				cubes[side_front[i][0]] = tmp->at(side_front[2][i]);
				cubes[side_front[i][1]] = tmp->at(side_front[1][i]);
				cubes[side_front[i][2]] = tmp->at(side_front[0][i]);
			}
		}
		break;

	case Back:
		if (clockwise) {
			for (int i = 0; i < 3; i++) {
				cubes[side_back[i][0]] = tmp->at(side_back[0][2 - i]);
				cubes[side_back[i][1]] = tmp->at(side_back[1][2 - i]);
				cubes[side_back[i][2]] = tmp->at(side_back[2][2 - i]);
			}
		}
		else {
			for (int i = 0; i < 3; i++) {
				cubes[side_back[i][0]] = tmp->at(side_back[2][i]);
				cubes[side_back[i][1]] = tmp->at(side_back[1][i]);
				cubes[side_back[i][2]] = tmp->at(side_back[0][i]);
			}
		}
		break;
	default:
		break;
	}
	
}

int RubicsCube::get_index(int i) {
	for (int j = 0; j < 27; j++)
		if (i == cubes[j])
			return j;
	return -1;
}

void RubicsCube:: print_array() {
	printf("array: \n");
	for (int i = 0; i < 27; i++)
		printf("%d ", i);
	printf("\n");
	for (int i = 0; i < 27; i++)
		printf("%d ", cubes[i]);
	printf("\n\n");
}



void RubicsCube::rotate_wall(int w) {
	if ((locked==-1) || (locked == w)){
		//locked = w;
		rotation = rotation + 1 ;
	switch (w)
	{
	case Up:
		for (int i = 0; i < 3; i++)
			for (int j = 0; j < 3; j++) {
				pickedShape = cubes[side_up[i][j]];
				ShapeTransformation(yRotate, (clockwise ? -1 : 1) * 90.0f / rotation_speed);

			}

		break;
	case Down:
		for (int i = 0; i < 3; i++)
			for (int j = 0; j < 3; j++) {
				pickedShape = cubes[side_down[i][j]];
				ShapeTransformation(yRotate, (clockwise ? 1 : -1) * 90.0f / rotation_speed);
			}
		break;

	case Right:
		for (int i = 0; i < 3; i++)
			for (int j = 0; j < 3; j++) {
				pickedShape = cubes[side_right[i][j]];
				ShapeTransformation(xRotate, (clockwise ? -1 : 1) * 90.0f / rotation_speed);
			}
		break;

	case Left:
		for (int i = 0; i < 3; i++)
			for (int j = 0; j < 3; j++) {
				pickedShape = cubes[side_left[i][j]];
				ShapeTransformation(xRotate, (clockwise ? 1 : -1) * 90.0f / rotation_speed);
			}
		break;

	case Front:
		for (int i = 0; i < 3; i++)
			for (int j = 0; j < 3; j++) {
				pickedShape = cubes[side_front[i][j]];
				ShapeTransformation(zRotate, (clockwise ? -1 : 1) * 90.0f / rotation_speed);

			}

		break;

	case Back:
		for (int i = 0; i < 3; i++)
			for (int j = 0; j < 3; j++) {
				pickedShape = cubes[side_back[i][j]];
				ShapeTransformation(zRotate, (clockwise ? 1 : -1) * 90.0f / rotation_speed);
			}

		break;


	default:
		break;

		//std::this_thread::sleep_for(std::chrono::milliseconds(20));
	}
	if (rotation == rotation_speed) {
		update_cubes(w);
		print_array();
		rotation = 0;
		//locked = -1;
	
	}
	
	}
	pickedShape = -1;
	//print_array();
	//pickedShape = 15;
	//ShapeTransformation(xTranslate, 2);

}

void RubicsCube::rotate_picked_wall() {
	picked_wall = pickedShape;
	add_motion(RotateWall, picked_wall);
	
}

void RubicsCube::random_rotation() {
	for (int i = 0; i < 10; i++) {
		int w = rand() % 6;
		cube_functions l = { Lock, w };
		cube_functions u = { Unlock, w };
		cube_functions f = { RotateWall, w };
		motions.push(u);
		for (int i = 0; i < rotation_speed; i++) {

			motions.push(f);
		}
		motions.push(l);
		
	}
}

void RubicsCube::decrease() {
	rotation_speed=rotation_speed*2;
}

void RubicsCube::increase() {
	if (rotation_speed != 1)
		rotation_speed=rotation_speed/2;
}

void RubicsCube::change_clockwise() {
	if (clockwise) clockwise = false;
	else clockwise = true;
}

void RubicsCube::Update(const glm::mat4 &MVP,const glm::mat4 &Model,const int  shaderIndx)
{
	Shader *s = shaders[shaderIndx];
	int r = ((pickedShape+1) & 0x000000FF) >>  0;
	int g = ((pickedShape+1) & 0x0000FF00) >>  8;
	int b = ((pickedShape+1) & 0x00FF0000) >> 16;
	//std::cout << r << " " << g << " " << b << std::endl;
	 float rr = pickedShape * 0.01;
	 //printf("r: %f\n", rr);
	if (shapes[pickedShape]->GetMaterial() >= 0 && !materials.empty())
		BindMaterial(s, shapes[pickedShape]->GetMaterial());
	textures[0]->Bind(0);
	s->Bind();
	if (shaderIndx == 0)
	{
		s->SetUniform4fv("lightColor", &glm::vec4(rr, 0.0, 0.0,1.0),1);
	}

		s->SetUniformMat4f("MVP", MVP);
		s->SetUniformMat4f("Normal", Model);
	
	s->SetUniform1i("sampler1", materials[shapes[pickedShape]->GetMaterial()]->GetSlot(0));
	if(shaderIndx!=1)
		s->SetUniform1i("sampler2", materials[shapes[pickedShape]->GetMaterial()]->GetSlot(1));

	s->Unbind();
}

void RubicsCube::WhenRotate()
{
}

void RubicsCube::WhenTranslate()
{
}

void RubicsCube::add_motion(int f , int w) {
	cube_functions func = { f, w };
	cube_functions l = { Lock, w };
	cube_functions u = { Unlock, w };
	motions.push(u);
	for(int i = 0; i< rotation_speed; i++)
		motions.push(func);
	motions.push(l);
	
}

void RubicsCube::lock(int w) {
	locked = w;
}

void RubicsCube::unlock() {
	locked = -1;
}


void RubicsCube::Motion()
{
	if (!motions.empty()) {
		cube_functions func;
		func = (cube_functions) motions.front();

		switch (func.f)
		{
		case RotateWall:
			
			rotate_wall(func.param);
			break;

		
		case Lock:
			lock(func.param);
			break;

		case Unlock:
			unlock();
			break;


		default:
			break;
		}
		motions.pop();

	}
}

void RubicsCube::UpdatePosition(float xpos, float ypos) {
	xrel = 420 - xpos;
	yrel = 420 - ypos;
	//xold = xpos;
	//yold = ypos;


}

unsigned int RubicsCube::TextureDesine(int width, int height)
{
	unsigned char* data = new unsigned char[width * height * 4];
	for (size_t i = 0; i < width; i++)
	{
		for (size_t j = 0; j < height; j++)
		{
			data[(i * height + j) * 4] = (i + j) % 256;
			data[(i * height + j) * 4 + 1] = (i + j * 2) % 256;
			data[(i * height + j) * 4 + 2] = (i * 2 + j) % 256;
			data[(i * height + j) * 4 + 3] = (i * 3 + j) % 256;
		}
	}
	textures.push_back(new Texture(width, height));
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data); //note GL_RED internal format, to save 
	glBindTexture(GL_TEXTURE_2D, 0);
	delete[] data;
	return(textures.size() - 1);
}

RubicsCube::~RubicsCube(void)
{

}
