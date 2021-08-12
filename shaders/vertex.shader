#version 330 core
layout(location = 0) in vec4 PosUV;

out vec2 UV;

uniform mat4 model;
uniform mat4 projection;

void main()
{
	UV = PosUV.zw;
	gl_Position = projection * model * vec4(PosUV.xy, 0.0f, 1.0f);
}