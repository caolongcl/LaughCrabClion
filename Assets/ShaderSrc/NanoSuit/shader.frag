#version 330 core

in vec2 TexCoords;

out vec4 color;

uniform sampler2D texture_diffuse1;//Âş·´ÉäÌùÍ¼
uniform sampler2D texture_specular1;//¾µÃæÌùÍ¼

void main()
{
	color = texture(texture_diffuse1, TexCoords);
}
