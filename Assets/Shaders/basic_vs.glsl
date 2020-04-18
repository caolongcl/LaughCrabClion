#version 330

in vec3 i_position;
in vec3 i_normal;
in vec2 i_uv;

out vec4 normal;
out vec4 v;
out vec2 uv;

uniform mat4 model;

uniform mat4 world;
uniform mat4 view;
uniform mat4 projection;

////////////////////////////////////////////////////////////////////////////////
// Vertex Shader
////////////////////////////////////////////////////////////////////////////////
void main(void)
{
    mat4 transformMatrix = world * model;
	// Calculate the i_position of the vertex against the world, view, and projection matrices.
	v = transformMatrix * vec4(i_position, 1.0f);
	v = view * v;
	gl_Position = projection * v;

    normal = transformMatrix * vec4(i_normal, 0.0f);
    normal = view * normal;
    uv.x = i_uv.x;
    uv.y = 1.0f - i_uv.y;
}

