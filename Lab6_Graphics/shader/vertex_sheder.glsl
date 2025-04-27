#version 460 core

layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aNormal;
uniform mat3 normalMatrix;


out vec3 Normal;
out vec3 FragPos;
out vec4 FragColor;
uniform vec3 yPos;
uniform mat4 transorm;
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
void main() {
    FragColor = vec4(0.2, 0.4, 0.7, 1.0);
    Normal = normalMatrix * aNormal;
    FragPos = aPos;
    gl_Position = projection * view * vec4(aPos, 1.0); 
}
