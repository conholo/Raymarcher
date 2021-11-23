#type vertex
#version 450 core

layout(location = 0) in vec3 a_Position;

void main()
{
	gl_Position = vec4(a_Position.xy, 0.0, 1.0);
}

#type fragment
#version 450 core

layout(location = 0) out vec4 o_Color;

uniform float u_ElapsedTime;
uniform float u_DeltaTime;
uniform vec2 u_ScreenResolution;
uniform vec2 u_MousePosition;

#define PI 3.14159265359


float MultiWave(float x, float t)
{
	float y = sin(PI * (x + 0.5 * t));
	y += 0.5 * sin(2.0 * PI *  t);
	y += sin(PI * (x + 0.25 * t));

	return y * (1.0 / 2.5);
}


void main()
{
	vec2 uv = (2.0 * gl_FragCoord.xy - u_ScreenResolution) / u_ScreenResolution.y;
	vec3 color = 0.5 + 0.5 * cos(vec3(u_ElapsedTime) + uv.xyx + vec3(0, 2, 4));

	o_Color = vec4(color, 1.0);
}