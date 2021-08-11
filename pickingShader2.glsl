#version 330

in vec3 normal0;

uniform sampler2D sampler1;
uniform vec4 lightDirection;
uniform vec4 lightColor;

void main()
{
	//vec3 color = vec4(clamp(lightColor.r,0.0,1.0),lightColor.g,lightColor.b);
	float x = normal0.x * 0.01;
	float y = normal0.y * 0.01;
	float z = normal0.z * 0.01;
	gl_FragColor = vec4(lightColor.r,normal0.x,normal0.y,normal0.z);
}
