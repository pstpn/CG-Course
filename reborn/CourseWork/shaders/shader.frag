#version 330

out vec4 FragColor;

in vec3 Normal;
in vec4 FragPos;

in vec4 figureColor;

void main()
{
	//vec3 lightPos = vec3(3, 3, 3);
	//float k = max(0, dot(Normal, normalize(lightPos - FragPos.xyz))) + 0.2;
	//float opacity = figureColor.w;
	//FragColor = vec4(figureColor.xyz * k, opacity);

	FragColor = figureColor;
}