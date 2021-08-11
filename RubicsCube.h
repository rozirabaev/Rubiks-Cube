#pragma once
#include "scene.h"
#include <queue>


class RubicsCube : public Scene
{
public:
	struct cube_functions {
		int f;
		int param;
	};

	enum wall {Front, Right, Up, Left, Down, Back};
	enum cube_func{ RotateWall ,  Lock,Unlock};
	RubicsCube();
	void Init();
	void Update(const glm::mat4 &MVP,const glm::mat4 &Model,const int  shaderIndx);
	
	void WhenRotate();
	void WhenTranslate();
	void Motion();
	void rotate_wall(int);
	void change_clockwise();
	void increase();
	void decrease();
	void update_cubes(int);
	int get_index(int);
	void print_array();
	void random_rotation();
	void lock(int w);
	void unlock();
	void rotate_picked_wall();
	bool comp_normals(int x, int y, int z, glm::vec3 wall_normal);
	unsigned int TextureDesine(int width, int height);
	~RubicsCube(void);
	void UpdatePosition(float xpos, float ypos);
	float xrel, yrel;
	int rotation_speed;
	bool clockwise;
	void add_motion(int f,int w);
	std::queue< cube_functions> motions;


	int picked_wall;
	int rotation;
	int locked;
	int cubes[27];
	int side_back[3][3] = { {2,1,0},{5,4,3},{8,7,6} }; //from down to up , x
	int side_front[3][3] = { {26,25,24},{23,22,21},{20,19,18} };//from down to up , x
	int side_right[3][3] = { {2,5,8}, { 11,14,17}, {20,23,26 } };//from down to up , x
	int side_left[3][3] = { {6,3,0}, {15,12,9 }, {24,21,18 }}; //from down to up , x
	int side_up[3][3] = { {8,7,6}, {17,16,15}, {26,25,24 } }; //from back to front
	int side_down[3][3] = { {0,1,2}, {9,10,11}, {18,19,20 } }; //from back to front
	


};

