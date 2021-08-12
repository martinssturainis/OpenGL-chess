#version 330 core
in vec2 UV;

out vec4 fragColor;

uniform sampler2D image;
uniform vec4 newColor;

void main()
{
	fragColor = vec4(newColor) * texture(image, UV);
}