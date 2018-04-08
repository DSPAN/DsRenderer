#version 450
#extension GL_ARB_separate_shader_objects : enable

layout(location = 0) in vec3 fragPosition;
layout(location = 1) in vec3 fragNormal;
layout(location = 2) in vec2 fragTexCoord;

layout(location = 0) out vec4 outColor;

void main() {
	vec3 viewPos = vec3(0.0, -1.0, 0.0);
	vec3 viewDir = normalize(viewPos - fragPosition);
	vec3 ambientLight = vec3(0.3, 0.3, 0.3);
	vec3 lightColor = vec3(0.8, 0.8, 0.8);
    vec3 lightDir = normalize(vec3(0.85, 0.8, 0.75));
	float ndl = max(0.0,dot(fragNormal,lightDir));
	vec3 diffuse = lightColor * ndl;
    outColor = vec4((ambientLight + diffuse),1);
}