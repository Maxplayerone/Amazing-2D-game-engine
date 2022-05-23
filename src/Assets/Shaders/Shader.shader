#type vertex
#version 330 core
layout(location = 0) in vec3 aPos;
layout(location = 1) in vec4 aColor;
layout(location = 2) in vec2 aTexCoords;

out vec4 fColor;
out vec2 fTexCoords;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main() {
	fColor = aColor;
	fTexCoords = aTexCoords;
	gl_Position = projection * view * model * vec4(aPos, 1.0f);
}

#type fragment
#version 330 core

in vec4 fColor;
in vec2 fTexCoords;

uniform sampler2D fTexture;

out vec4 color;

void main() {
	vec4 texColor = texture(fTexture, fTexCoords);
	color = texColor;
}