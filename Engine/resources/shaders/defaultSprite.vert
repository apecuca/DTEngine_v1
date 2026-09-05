#version 330 core

layout (location = 0) in vec2 aPos;
layout (location = 1) in vec2 aTexCoord;

out vec2 TexCoord;

uniform mat3 model;
uniform mat3 view;
uniform mat3 projection;

void main()
{
   vec3 pos = projection * view * model * vec3(aPos, 1.0f);
   gl_Position = vec4(pos.xy, 0.0f, 1.0f);
   TexCoord = vec2(aTexCoord.x, aTexCoord.y);
}
