#define GLEW_STATIC
#include "GL/glew.h"
#include "scene.h"

#include <iostream>

static void printMat(const glm::mat4 mat)
{
	printf(" matrix: \n");
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
			printf("%f ", mat[j][i]);
		printf("\n");
	}
}

Scene::Scene()
{
	glLineWidth(5);

	pickedShape = -1;
	depth = 0;

	isActive = false;
}

void Scene::AddShapeFromFile(const std::string& fileName, int parent, unsigned int mode)
{
	chainParents.push_back(parent);
	shapes.push_back(new Shape(fileName, mode));
}

void Scene::AddShape(int type, int parent, unsigned int mode)
{
	chainParents.push_back(parent);
	shapes.push_back(new Shape(type, mode));
}

void Scene::AddShapeCopy(int indx, int parent, unsigned int mode)
{
	chainParents.push_back(parent);
	shapes.push_back(new Shape(*shapes[indx], mode));
}

int Scene::AddShader(const std::string& fileName)
{
	shaders.push_back(new Shader(fileName));
	return (shaders.size() - 1);
}

int  Scene::AddTexture(const std::string& textureFileName, int dim)
{
	textures.push_back(new Texture(textureFileName, dim));
	return(textures.size() - 1);
}

int Scene::AddTexture(int width, int height, unsigned char* data, int mode)
{
	textures.push_back(new Texture(width, height));

	switch (mode)
	{
	case COLOR:
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data); //note GL_RED internal format, to save memory.
		break;
	case DEPTH:
		glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT32, width, height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, data);
		break;
	case STENCIL:
		glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH24_STENCIL8, width, height, 0, GL_DEPTH_STENCIL, GL_UNSIGNED_INT_24_8, data);
		break;
	default:
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data); //note GL_RED internal format, to save memory.
	}
	glBindTexture(GL_TEXTURE_2D, 0);
	return(textures.size() - 1);
}

int Scene::AddMaterial(unsigned int texIndices[], unsigned int slots[], unsigned int size)
{
	materials.push_back(new Material(texIndices, slots, size));
	return (materials.size() - 1);
}

void Scene::Draw(int shaderIndx, const glm::mat4& MVP, int viewportIndx, unsigned int flags) 
{
	glm::mat4 Normal = MakeTrans();

	int p = pickedShape;

	for (pickedShape = 0; pickedShape < shapes.size(); pickedShape++)
	{
		if (shapes[pickedShape]->Is2Render(viewportIndx))
		{
			glm::mat4 Model = Normal * shapes[pickedShape]->MakeTrans();

			if (shaderIndx > 0)
			{
				Update(MVP, Model, shapes[pickedShape]->GetShader());
				shapes[pickedShape]->Draw(shaders[shapes[pickedShape]->GetShader()], false);
			}
			else
			{ //picking
				Update(MVP, Model, 0);
				shapes[pickedShape]->Draw(shaders[0], true);
			}
		}
	}
	pickedShape = p;
}



void Scene::ShapeTransformation(int type, float amt)
{
	if (glm::abs(amt) > 1e-5)
	{
		switch (type)
		{
		case xTranslate:
			shapes[pickedShape]->MyTranslate(glm::vec3(amt, 0, 0), 0);
			break;
		case yTranslate:
			shapes[pickedShape]->MyTranslate(glm::vec3(0, amt, 0), 0);
			break;
		case zTranslate:
			shapes[pickedShape]->MyTranslate(glm::vec3(0, 0, amt), 0);
			break;
		case xRotate:
			shapes[pickedShape]->MyRotate(amt, glm::vec3(1, 0, 0), 0);
			break;
		case yRotate:
			shapes[pickedShape]->MyRotate(amt, glm::vec3(0, 1, 0), 0);
			break;
		case zRotate:
			shapes[pickedShape]->MyRotate(amt, glm::vec3(0, 0, 1), 0);
			break;
		default:
			break;
		}
	}

}

bool is_equal(int x,int z) {
	if ((x == z) || (abs(x - z) == 1) || (x==0 && z <=0))
		return true;
	return false;
}

bool Scene::comp_normals(int x, int y, int z, glm::vec4 wall_normal) {
	if (is_equal(z, (int)(wall_normal.z * 10)) &&
		is_equal(y, (int)(wall_normal.y * 10)) &&
		is_equal(x, (int)(wall_normal.x * 10)))

		return true;

	/*
	if (((z == (int)(wall_normal.z * 10)) || ((z == 0 && (int)(wall_normal.z * 10) <= 0))) &&
		((y == (int)(wall_normal.y * 10)) || ((y == 0 && (int)(wall_normal.y * 10) <= 0))) &&
		((x == (int)(wall_normal.x * 10)) || ((x == 0 && (int)(wall_normal.x * 10) <= 0))) )
		return true;
	*/
	return false;
}

bool Scene::Picking(unsigned char data[4],float x,float y)
{
		pickedShape = -1;
	//	if (data[0] > 0)
		//{
			float picked_f = (float)((data[0] / 255.0 * 100.0));
			printf("picked: %f\n\n", picked_f);
			pickedShape = (int)round(picked_f);
			int wall = -1;
			glm::mat4 Normal = MakeTrans();
			glm::mat4 Model = Normal * shapes[pickedShape]->MakeTrans();

			glm::vec4 normal_x = glm::vec4(Normal * (glm::vec4(1, 0, 0, 0)));
			glm::vec4 normal_y = glm::vec4(Normal * (glm::vec4(0, 1, 0, 0)));
			glm::vec4 normal_z = glm::vec4(Normal * (glm::vec4(0, 0, 1, 0)));

			glm::vec4 normal_x_ = glm::vec4(Normal * (glm::vec4(-1, 0, 0, 0)));
			glm::vec4 normal_y_ = glm::vec4(Normal * (glm::vec4(0, -1, 0, 0)));
			glm::vec4 normal_z_ = glm::vec4(Normal * (glm::vec4(0, 0, -1, 0)));


			
			printf("normalx  : (%d, %d, %d)\n", (int)(normal_x.x * 10.0), (int)(normal_x.y * 10.0), (int)(normal_x.z * 10.0));
			printf("normaly  : (%d, %d, %d)\n", (int)(normal_y.x * 10.0), (int)(normal_y.y * 10.0), (int)(normal_y.z * 10.0));
			printf("normalz  : (%d, %d, %d)\n\n", (int)(normal_z.x * 10.0), (int)(normal_z.y * 10.0), (int)(normal_z.z * 10.0));
			printf("normalx -: (%d, %d, %d)\n", (int)(normal_x_.x * 10.0), (int)(normal_x_.y * 10.0), (int)(normal_x_.z * 10.0));
			printf("normaly -: (%d, %d, %d)\n", (int)(normal_y_.x * 10.0), (int)(normal_y_.y * 10.0), (int)(normal_y_.z * 10.0));
			printf("normalz -: (%d, %d, %d)\n\n", (int)(normal_z_.x * 10.0), (int)(normal_z_.y * 10.0), (int)(normal_z_.z * 10.0));

			
			glm::vec3 normal_pos = glm::vec3((data[1] / 255.0), (data[2] / 255.0 ), (data[3] / 255.0 ));
			printf("normalx_pos: (%d, %d, %d)\n", (int)(normal_pos.x * 10), (int)(normal_pos.y * 10.0), (int)(normal_pos.z * 10.0));
			
			int x_normal = (int)(normal_pos.x * 10);
			int y_normal = (int)(normal_pos.y * 10);
			int z_normal = (int)(normal_pos.z * 10);

			if ( comp_normals(x_normal,y_normal,z_normal,normal_z) ){
				pickedShape = Front; //front
				return true;
			}
			if (comp_normals(x_normal, y_normal, z_normal, normal_x) ) {
				pickedShape = Right; //right
				return true;
			}
			if (comp_normals(x_normal, y_normal, z_normal, normal_y)) {
				pickedShape = Up; //up
				return true;
			}
			if (comp_normals(x_normal, y_normal, z_normal, normal_x_)) {
				pickedShape = Left; //left
				return true;
			}
			if (comp_normals(x_normal, y_normal, z_normal, normal_y_)) {
				pickedShape = Down; //down
				return true;
			}
			if (comp_normals(x_normal, y_normal, z_normal, normal_z_)) {
				pickedShape = Back;
				return true;
			}
			return false;
}
//return coordinates in global system for a tip of arm position is local system 
void Scene::MouseProccessing(int button, int xrel, int yrel)
{
	MovableGLM* obj;
	if (pickedShape == -1)
		obj = (MovableGLM*)shapes[0];// , shapes[1];//(MovableGLM*)this;
	else
		obj = (MovableGLM*)shapes[pickedShape];
	//{
	if (button == 1)
	{
	}
	else
	{
			obj = (MovableGLM*)this;
			obj->MyRotate(-yrel / 10.0f, glm::vec3(1, 0, 0), 0); 
			obj->MyRotate(-xrel / 10.0f, glm::vec3(0, 1, 0), 1);
	
			WhenRotate();
		
	}
	//}

}

void Scene::ZeroShapesTrans()
{
	for (unsigned int i = 0; i < shapes.size(); i++)
	{
		shapes[i]->ZeroTrans();
	}
}

void Scene::ReadPixel()
{
	glReadPixels(1, 1, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &depth);
}

void Scene::AddShapeViewport(int shpIndx,int viewPortIndx)
{
	shapes[shpIndx]->AddViewport(viewPortIndx);
}

void Scene::RemoveShapeViewport(int shpIndx, int viewPortIndx)
{
	shapes[shpIndx]->RemoveViewport(viewPortIndx);
}

void Scene::BindMaterial(Shader* s, unsigned int materialIndx)
{

	for (size_t i = 0; i < materials[materialIndx]->GetNumOfTexs(); i++)
	{
		materials[materialIndx]->Bind(textures, i);
		s->SetUniform1i("sampler" + std::to_string(i + 1), materials[materialIndx]->GetSlot(i));
	}
}

Scene::~Scene(void)
{
	for (Shape* shp : shapes)
	{
		delete shp;
	}

	for (Shader* sdr : shaders)
	{
		delete sdr;
	}
	for (Texture* tex : textures)
	{
		delete tex;
	}
	for (Material* mat : materials)
	{
		delete mat;
	}

}



