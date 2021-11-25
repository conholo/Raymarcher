#version 450 core

layout(location = 0) out vec4 o_Color;

uniform float u_ElapsedTime;
uniform float u_DeltaTime;
uniform vec2 u_ScreenResolution;
uniform vec2 u_MousePosition;
uniform mat4 u_ViewProjection;
uniform vec3 u_CameraPosition;
uniform vec3 u_CameraForward;

#define PI 3.14159265359
#define MAX_MARCHES 1000.0
#define MIN_DISTANCE 0.00001
#define MAX_DISTANCE 50.0




//##########################################
//   Distance Estimators
//##########################################
float DE_Box(vec4 position, vec3 scale)
{
	vec3 a = abs(position.xyz) - scale;
	return (min(max(max(a.x, a.y), a.z), 0.0) + length(max(a, 0.0))) / position.w;
}

float DE_Sphere(vec4 position, float r)
{
	return (length(position.xyz) - r) / position.w;
}

float DE_Tetrahedron(vec4 position, float r)
{
	float md = max(max(-position.x - position.y - position.z, position.x + position.y - position.z),
		max(-position.x + position.y + position.z, position.x - position.y + position.z));
	return (md - r) / (position.w * sqrt(3.0));
}
//##########################################
//   Distance Estimators
//##########################################


//##########################################
//   Space Folds
//##########################################
void PlaneFold(inout vec4 z, vec3 normal, float d)
{
	z.xyz -= 2.0 * min(0.0, dot(z.xyz, normal) - d) * normal;
}

void BoxFold(inout vec4 z, vec3 range)
{
	z.xyz = clamp(z.xyz, -range, range) * 2.0 - z.xyz;
}

void SphereFold(inout vec4 z, float minR, float maxR)
{
	float r2 = dot(z.xyz, z.xyz);
	z *= max(maxR / max(minR, r2), 1.0);
}

void MengerFold(inout vec4 z)
{
	float a = min(z.x - z.y, 0.0);
	z.x -= a;
	z.y += a;
	a = min(z.x - z.z, 0.0);
	z.x -= a;
	z.z += a;
	a = min(z.y - z.z, 0.0);
	z.y -= a;
	z.z += a;
}

void SierpinskiFold(inout vec4 z)
{
	z.xy -= min(z.x + z.y, 0.0);
	z.xz -= min(z.x + z.z, 0.0);
	z.yz -= min(z.y + z.z, 0.0);
}

void AbsFold(inout vec4 z, vec3 c)
{
	z.xyz = abs(z.xyz - c) + c;
}

void RotationXFold(inout vec4 z, float s, float c)
{
	z.yz = vec2(c * z.y + s * z.z, c * z.z - s * z.y);
}
void RotationYFold(inout vec4 z, float s, float c)
{
	z.xz = vec2(c * z.x - s * z.z, c * z.z + s * z.x);
}
void RotationZFold(inout vec4 z, float s, float c)
{
	z.xy = vec2(c * z.x + s * z.y, c * z.y - s * z.x);
}
//##########################################
//   Space Folds
//##########################################


//DE/CE Begin

float DE_TestFractal(vec4 position)
{
	vec4 o = position;
	float d = 1e20;
	AbsFold(position, vec3(0.000000, 0.000000, 0.000000));
	position *= 1.500000;
	position.xyz += vec3(-1.000000, -0.550000, -0.200000);
	RotationXFold(position, -0.438371, -0.898794);
	RotationYFold(position, 0.898794, -0.438371);
	AbsFold(position, vec3(0.000000, 0.000000, 0.000000));
	position *= 1.500000;
	position.xyz += vec3(-1.000000, -0.550000, -0.200000);
	RotationXFold(position, -0.438371, -0.898794);
	RotationYFold(position, 0.898794, -0.438371);
	AbsFold(position, vec3(0.000000, 0.000000, 0.000000));
	position *= 1.500000;
	position.xyz += vec3(-1.000000, -0.550000, -0.200000);
	RotationXFold(position, -0.438371, -0.898794);
	RotationYFold(position, 0.898794, -0.438371);
	AbsFold(position, vec3(0.000000, 0.000000, 0.000000));
	position *= 1.500000;
	position.xyz += vec3(-1.000000, -0.550000, -0.200000);
	RotationXFold(position, -0.438371, -0.898794);
	RotationYFold(position, 0.898794, -0.438371);
	AbsFold(position, vec3(0.000000, 0.000000, 0.000000));
	position *= 1.500000;
	position.xyz += vec3(-1.000000, -0.550000, -0.200000);
	RotationXFold(position, -0.438371, -0.898794);
	RotationYFold(position, 0.898794, -0.438371);
	AbsFold(position, vec3(0.000000, 0.000000, 0.000000));
	position *= 1.500000;
	position.xyz += vec3(-1.000000, -0.550000, -0.200000);
	RotationXFold(position, -0.438371, -0.898794);
	RotationYFold(position, 0.898794, -0.438371);
	AbsFold(position, vec3(0.000000, 0.000000, 0.000000));
	position *= 1.500000;
	position.xyz += vec3(-1.000000, -0.550000, -0.200000);
	RotationXFold(position, -0.438371, -0.898794);
	RotationYFold(position, 0.898794, -0.438371);
	AbsFold(position, vec3(0.000000, 0.000000, 0.000000));
	position *= 1.500000;
	position.xyz += vec3(-1.000000, -0.550000, -0.200000);
	RotationXFold(position, -0.438371, -0.898794);
	RotationYFold(position, 0.898794, -0.438371);
	AbsFold(position, vec3(0.000000, 0.000000, 0.000000));
	position *= 1.500000;
	position.xyz += vec3(-1.000000, -0.550000, -0.200000);
	RotationXFold(position, -0.438371, -0.898794);
	RotationYFold(position, 0.898794, -0.438371);
	AbsFold(position, vec3(0.000000, 0.000000, 0.000000));
	position *= 1.500000;
	position.xyz += vec3(-1.000000, -0.550000, -0.200000);
	RotationXFold(position, -0.438371, -0.898794);
	RotationYFold(position, 0.898794, -0.438371);
	AbsFold(position, vec3(0.000000, 0.000000, 0.000000));
	position *= 1.500000;
	position.xyz += vec3(-1.000000, -0.550000, -0.200000);
	RotationXFold(position, -0.438371, -0.898794);
	RotationYFold(position, 0.898794, -0.438371);
	AbsFold(position, vec3(0.000000, 0.000000, 0.000000));
	position *= 1.500000;
	position.xyz += vec3(-1.000000, -0.550000, -0.200000);
	RotationXFold(position, -0.438371, -0.898794);
	RotationYFold(position, 0.898794, -0.438371);
	AbsFold(position, vec3(0.000000, 0.000000, 0.000000));
	position *= 1.500000;
	position.xyz += vec3(-1.000000, -0.550000, -0.200000);
	RotationXFold(position, -0.438371, -0.898794);
	RotationYFold(position, 0.898794, -0.438371);
	AbsFold(position, vec3(0.000000, 0.000000, 0.000000));
	position *= 1.500000;
	position.xyz += vec3(-1.000000, -0.550000, -0.200000);
	RotationXFold(position, -0.438371, -0.898794);
	RotationYFold(position, 0.898794, -0.438371);
	AbsFold(position, vec3(0.000000, 0.000000, 0.000000));
	position *= 1.500000;
	position.xyz += vec3(-1.000000, -0.550000, -0.200000);
	RotationXFold(position, -0.438371, -0.898794);
	RotationYFold(position, 0.898794, -0.438371);
	AbsFold(position, vec3(0.000000, 0.000000, 0.000000));
	position *= 1.500000;
	position.xyz += vec3(-1.000000, -0.550000, -0.200000);
	RotationXFold(position, -0.438371, -0.898794);
	RotationYFold(position, 0.898794, -0.438371);
	AbsFold(position, vec3(0.000000, 0.000000, 0.000000));
	position *= 1.500000;
	position.xyz += vec3(-1.000000, -0.550000, -0.200000);
	RotationXFold(position, -0.438371, -0.898794);
	RotationYFold(position, 0.898794, -0.438371);
	AbsFold(position, vec3(0.000000, 0.000000, 0.000000));
	position *= 1.500000;
	position.xyz += vec3(-1.000000, -0.550000, -0.200000);
	RotationXFold(position, -0.438371, -0.898794);
	RotationYFold(position, 0.898794, -0.438371);
	AbsFold(position, vec3(0.000000, 0.000000, 0.000000));
	position *= 1.500000;
	position.xyz += vec3(-1.000000, -0.550000, -0.200000);
	RotationXFold(position, -0.438371, -0.898794);
	RotationYFold(position, 0.898794, -0.438371);
	AbsFold(position, vec3(0.000000, 0.000000, 0.000000));
	position *= 1.500000;
	position.xyz += vec3(-1.000000, -0.550000, -0.200000);
	RotationXFold(position, -0.438371, -0.898794);
	RotationYFold(position, 0.898794, -0.438371);
	AbsFold(position, vec3(0.000000, 0.000000, 0.000000));
	position *= 1.500000;
	position.xyz += vec3(-1.000000, -0.550000, -0.200000);
	RotationXFold(position, -0.438371, -0.898794);
	RotationYFold(position, 0.898794, -0.438371);
	AbsFold(position, vec3(0.000000, 0.000000, 0.000000));
	position *= 1.500000;
	position.xyz += vec3(-1.000000, -0.550000, -0.200000);
	RotationXFold(position, -0.438371, -0.898794);
	RotationYFold(position, 0.898794, -0.438371);
	AbsFold(position, vec3(0.000000, 0.000000, 0.000000));
	position *= 1.500000;
	position.xyz += vec3(-1.000000, -0.550000, -0.200000);
	RotationXFold(position, -0.438371, -0.898794);
	RotationYFold(position, 0.898794, -0.438371);
	AbsFold(position, vec3(0.000000, 0.000000, 0.000000));
	position *= 1.500000;
	position.xyz += vec3(-1.000000, -0.550000, -0.200000);
	RotationXFold(position, -0.438371, -0.898794);
	RotationYFold(position, 0.898794, -0.438371);
	AbsFold(position, vec3(0.000000, 0.000000, 0.000000));
	position *= 1.500000;
	position.xyz += vec3(-1.000000, -0.550000, -0.200000);
	RotationXFold(position, -0.438371, -0.898794);
	RotationYFold(position, 0.898794, -0.438371);
	AbsFold(position, vec3(0.000000, 0.000000, 0.000000));
	position *= 1.500000;
	position.xyz += vec3(-1.000000, -0.550000, -0.200000);
	RotationXFold(position, -0.438371, -0.898794);
	RotationYFold(position, 0.898794, -0.438371);
	AbsFold(position, vec3(0.000000, 0.000000, 0.000000));
	position *= 1.500000;
	position.xyz += vec3(-1.000000, -0.550000, -0.200000);
	RotationXFold(position, -0.438371, -0.898794);
	RotationYFold(position, 0.898794, -0.438371);
	AbsFold(position, vec3(0.000000, 0.000000, 0.000000));
	position *= 1.500000;
	position.xyz += vec3(-1.000000, -0.550000, -0.200000);
	RotationXFold(position, -0.438371, -0.898794);
	RotationYFold(position, 0.898794, -0.438371);
	AbsFold(position, vec3(0.000000, 0.000000, 0.000000));
	position *= 1.500000;
	position.xyz += vec3(-1.000000, -0.550000, -0.200000);
	RotationXFold(position, -0.438371, -0.898794);
	RotationYFold(position, 0.898794, -0.438371);
	AbsFold(position, vec3(0.000000, 0.000000, 0.000000));
	position *= 1.500000;
	position.xyz += vec3(-1.000000, -0.550000, -0.200000);
	RotationXFold(position, -0.438371, -0.898794);
	RotationYFold(position, 0.898794, -0.438371);
	d = min(d, DE_Sphere(position - vec4(vec3(0.000000, 0.000000, 0.000000), 0.0), 1.000000));
	return d;
}
vec4 CE_TestFractal(vec4 position)
{
	vec4 o = position;
	vec4 color = vec4(1e20);
	vec4 newColor;
	vec3 orbit = vec3(0.0);
	AbsFold(position, vec3(0.000000, 0.000000, 0.000000));
	position *= 1.500000;
	position.xyz += vec3(-1.000000, -0.550000, -0.200000);
	orbit += (position.xyz - vec3(0.000000, 0.000000, 0.000000)) * vec3(0.500000, 0.300000, 0.000000);
	RotationXFold(position, -0.438371, -0.898794);
	RotationYFold(position, 0.898794, -0.438371);
	AbsFold(position, vec3(0.000000, 0.000000, 0.000000));
	position *= 1.500000;
	position.xyz += vec3(-1.000000, -0.550000, -0.200000);
	orbit += (position.xyz - vec3(0.000000, 0.000000, 0.000000)) * vec3(0.500000, 0.300000, 0.000000);
	RotationXFold(position, -0.438371, -0.898794);
	RotationYFold(position, 0.898794, -0.438371);
	AbsFold(position, vec3(0.000000, 0.000000, 0.000000));
	position *= 1.500000;
	position.xyz += vec3(-1.000000, -0.550000, -0.200000);
	orbit += (position.xyz - vec3(0.000000, 0.000000, 0.000000)) * vec3(0.500000, 0.300000, 0.000000);
	RotationXFold(position, -0.438371, -0.898794);
	RotationYFold(position, 0.898794, -0.438371);
	AbsFold(position, vec3(0.000000, 0.000000, 0.000000));
	position *= 1.500000;
	position.xyz += vec3(-1.000000, -0.550000, -0.200000);
	orbit += (position.xyz - vec3(0.000000, 0.000000, 0.000000)) * vec3(0.500000, 0.300000, 0.000000);
	RotationXFold(position, -0.438371, -0.898794);
	RotationYFold(position, 0.898794, -0.438371);
	AbsFold(position, vec3(0.000000, 0.000000, 0.000000));
	position *= 1.500000;
	position.xyz += vec3(-1.000000, -0.550000, -0.200000);
	orbit += (position.xyz - vec3(0.000000, 0.000000, 0.000000)) * vec3(0.500000, 0.300000, 0.000000);
	RotationXFold(position, -0.438371, -0.898794);
	RotationYFold(position, 0.898794, -0.438371);
	AbsFold(position, vec3(0.000000, 0.000000, 0.000000));
	position *= 1.500000;
	position.xyz += vec3(-1.000000, -0.550000, -0.200000);
	orbit += (position.xyz - vec3(0.000000, 0.000000, 0.000000)) * vec3(0.500000, 0.300000, 0.000000);
	RotationXFold(position, -0.438371, -0.898794);
	RotationYFold(position, 0.898794, -0.438371);
	AbsFold(position, vec3(0.000000, 0.000000, 0.000000));
	position *= 1.500000;
	position.xyz += vec3(-1.000000, -0.550000, -0.200000);
	orbit += (position.xyz - vec3(0.000000, 0.000000, 0.000000)) * vec3(0.500000, 0.300000, 0.000000);
	RotationXFold(position, -0.438371, -0.898794);
	RotationYFold(position, 0.898794, -0.438371);
	AbsFold(position, vec3(0.000000, 0.000000, 0.000000));
	position *= 1.500000;
	position.xyz += vec3(-1.000000, -0.550000, -0.200000);
	orbit += (position.xyz - vec3(0.000000, 0.000000, 0.000000)) * vec3(0.500000, 0.300000, 0.000000);
	RotationXFold(position, -0.438371, -0.898794);
	RotationYFold(position, 0.898794, -0.438371);
	AbsFold(position, vec3(0.000000, 0.000000, 0.000000));
	position *= 1.500000;
	position.xyz += vec3(-1.000000, -0.550000, -0.200000);
	orbit += (position.xyz - vec3(0.000000, 0.000000, 0.000000)) * vec3(0.500000, 0.300000, 0.000000);
	RotationXFold(position, -0.438371, -0.898794);
	RotationYFold(position, 0.898794, -0.438371);
	AbsFold(position, vec3(0.000000, 0.000000, 0.000000));
	position *= 1.500000;
	position.xyz += vec3(-1.000000, -0.550000, -0.200000);
	orbit += (position.xyz - vec3(0.000000, 0.000000, 0.000000)) * vec3(0.500000, 0.300000, 0.000000);
	RotationXFold(position, -0.438371, -0.898794);
	RotationYFold(position, 0.898794, -0.438371);
	AbsFold(position, vec3(0.000000, 0.000000, 0.000000));
	position *= 1.500000;
	position.xyz += vec3(-1.000000, -0.550000, -0.200000);
	orbit += (position.xyz - vec3(0.000000, 0.000000, 0.000000)) * vec3(0.500000, 0.300000, 0.000000);
	RotationXFold(position, -0.438371, -0.898794);
	RotationYFold(position, 0.898794, -0.438371);
	AbsFold(position, vec3(0.000000, 0.000000, 0.000000));
	position *= 1.500000;
	position.xyz += vec3(-1.000000, -0.550000, -0.200000);
	orbit += (position.xyz - vec3(0.000000, 0.000000, 0.000000)) * vec3(0.500000, 0.300000, 0.000000);
	RotationXFold(position, -0.438371, -0.898794);
	RotationYFold(position, 0.898794, -0.438371);
	AbsFold(position, vec3(0.000000, 0.000000, 0.000000));
	position *= 1.500000;
	position.xyz += vec3(-1.000000, -0.550000, -0.200000);
	orbit += (position.xyz - vec3(0.000000, 0.000000, 0.000000)) * vec3(0.500000, 0.300000, 0.000000);
	RotationXFold(position, -0.438371, -0.898794);
	RotationYFold(position, 0.898794, -0.438371);
	AbsFold(position, vec3(0.000000, 0.000000, 0.000000));
	position *= 1.500000;
	position.xyz += vec3(-1.000000, -0.550000, -0.200000);
	orbit += (position.xyz - vec3(0.000000, 0.000000, 0.000000)) * vec3(0.500000, 0.300000, 0.000000);
	RotationXFold(position, -0.438371, -0.898794);
	RotationYFold(position, 0.898794, -0.438371);
	AbsFold(position, vec3(0.000000, 0.000000, 0.000000));
	position *= 1.500000;
	position.xyz += vec3(-1.000000, -0.550000, -0.200000);
	orbit += (position.xyz - vec3(0.000000, 0.000000, 0.000000)) * vec3(0.500000, 0.300000, 0.000000);
	RotationXFold(position, -0.438371, -0.898794);
	RotationYFold(position, 0.898794, -0.438371);
	AbsFold(position, vec3(0.000000, 0.000000, 0.000000));
	position *= 1.500000;
	position.xyz += vec3(-1.000000, -0.550000, -0.200000);
	orbit += (position.xyz - vec3(0.000000, 0.000000, 0.000000)) * vec3(0.500000, 0.300000, 0.000000);
	RotationXFold(position, -0.438371, -0.898794);
	RotationYFold(position, 0.898794, -0.438371);
	AbsFold(position, vec3(0.000000, 0.000000, 0.000000));
	position *= 1.500000;
	position.xyz += vec3(-1.000000, -0.550000, -0.200000);
	orbit += (position.xyz - vec3(0.000000, 0.000000, 0.000000)) * vec3(0.500000, 0.300000, 0.000000);
	RotationXFold(position, -0.438371, -0.898794);
	RotationYFold(position, 0.898794, -0.438371);
	AbsFold(position, vec3(0.000000, 0.000000, 0.000000));
	position *= 1.500000;
	position.xyz += vec3(-1.000000, -0.550000, -0.200000);
	orbit += (position.xyz - vec3(0.000000, 0.000000, 0.000000)) * vec3(0.500000, 0.300000, 0.000000);
	RotationXFold(position, -0.438371, -0.898794);
	RotationYFold(position, 0.898794, -0.438371);
	AbsFold(position, vec3(0.000000, 0.000000, 0.000000));
	position *= 1.500000;
	position.xyz += vec3(-1.000000, -0.550000, -0.200000);
	orbit += (position.xyz - vec3(0.000000, 0.000000, 0.000000)) * vec3(0.500000, 0.300000, 0.000000);
	RotationXFold(position, -0.438371, -0.898794);
	RotationYFold(position, 0.898794, -0.438371);
	AbsFold(position, vec3(0.000000, 0.000000, 0.000000));
	position *= 1.500000;
	position.xyz += vec3(-1.000000, -0.550000, -0.200000);
	orbit += (position.xyz - vec3(0.000000, 0.000000, 0.000000)) * vec3(0.500000, 0.300000, 0.000000);
	RotationXFold(position, -0.438371, -0.898794);
	RotationYFold(position, 0.898794, -0.438371);
	AbsFold(position, vec3(0.000000, 0.000000, 0.000000));
	position *= 1.500000;
	position.xyz += vec3(-1.000000, -0.550000, -0.200000);
	orbit += (position.xyz - vec3(0.000000, 0.000000, 0.000000)) * vec3(0.500000, 0.300000, 0.000000);
	RotationXFold(position, -0.438371, -0.898794);
	RotationYFold(position, 0.898794, -0.438371);
	AbsFold(position, vec3(0.000000, 0.000000, 0.000000));
	position *= 1.500000;
	position.xyz += vec3(-1.000000, -0.550000, -0.200000);
	orbit += (position.xyz - vec3(0.000000, 0.000000, 0.000000)) * vec3(0.500000, 0.300000, 0.000000);
	RotationXFold(position, -0.438371, -0.898794);
	RotationYFold(position, 0.898794, -0.438371);
	AbsFold(position, vec3(0.000000, 0.000000, 0.000000));
	position *= 1.500000;
	position.xyz += vec3(-1.000000, -0.550000, -0.200000);
	orbit += (position.xyz - vec3(0.000000, 0.000000, 0.000000)) * vec3(0.500000, 0.300000, 0.000000);
	RotationXFold(position, -0.438371, -0.898794);
	RotationYFold(position, 0.898794, -0.438371);
	AbsFold(position, vec3(0.000000, 0.000000, 0.000000));
	position *= 1.500000;
	position.xyz += vec3(-1.000000, -0.550000, -0.200000);
	orbit += (position.xyz - vec3(0.000000, 0.000000, 0.000000)) * vec3(0.500000, 0.300000, 0.000000);
	RotationXFold(position, -0.438371, -0.898794);
	RotationYFold(position, 0.898794, -0.438371);
	AbsFold(position, vec3(0.000000, 0.000000, 0.000000));
	position *= 1.500000;
	position.xyz += vec3(-1.000000, -0.550000, -0.200000);
	orbit += (position.xyz - vec3(0.000000, 0.000000, 0.000000)) * vec3(0.500000, 0.300000, 0.000000);
	RotationXFold(position, -0.438371, -0.898794);
	RotationYFold(position, 0.898794, -0.438371);
	AbsFold(position, vec3(0.000000, 0.000000, 0.000000));
	position *= 1.500000;
	position.xyz += vec3(-1.000000, -0.550000, -0.200000);
	orbit += (position.xyz - vec3(0.000000, 0.000000, 0.000000)) * vec3(0.500000, 0.300000, 0.000000);
	RotationXFold(position, -0.438371, -0.898794);
	RotationYFold(position, 0.898794, -0.438371);
	AbsFold(position, vec3(0.000000, 0.000000, 0.000000));
	position *= 1.500000;
	position.xyz += vec3(-1.000000, -0.550000, -0.200000);
	orbit += (position.xyz - vec3(0.000000, 0.000000, 0.000000)) * vec3(0.500000, 0.300000, 0.000000);
	RotationXFold(position, -0.438371, -0.898794);
	RotationYFold(position, 0.898794, -0.438371);
	AbsFold(position, vec3(0.000000, 0.000000, 0.000000));
	position *= 1.500000;
	position.xyz += vec3(-1.000000, -0.550000, -0.200000);
	orbit += (position.xyz - vec3(0.000000, 0.000000, 0.000000)) * vec3(0.500000, 0.300000, 0.000000);
	RotationXFold(position, -0.438371, -0.898794);
	RotationYFold(position, 0.898794, -0.438371);
	AbsFold(position, vec3(0.000000, 0.000000, 0.000000));
	position *= 1.500000;
	position.xyz += vec3(-1.000000, -0.550000, -0.200000);
	orbit += (position.xyz - vec3(0.000000, 0.000000, 0.000000)) * vec3(0.500000, 0.300000, 0.000000);
	RotationXFold(position, -0.438371, -0.898794);
	RotationYFold(position, 0.898794, -0.438371);
	AbsFold(position, vec3(0.000000, 0.000000, 0.000000));
	position *= 1.500000;
	position.xyz += vec3(-1.000000, -0.550000, -0.200000);
	orbit += (position.xyz - vec3(0.000000, 0.000000, 0.000000)) * vec3(0.500000, 0.300000, 0.000000);
	RotationXFold(position, -0.438371, -0.898794);
	RotationYFold(position, 0.898794, -0.438371);
	newColor = vec4(orbit, DE_Sphere(position - vec4(vec3(0.000000, 0.000000, 0.000000), 0.0), 1.000000));
	if (newColor.w < color.w) { color = newColor; }
	return color;
}

//DE/CE End

float CalculateSoftShadow(vec4 rayOrigin, vec3 rayDirection, float minT, float maxT)
{
	float volume = (0.8 - rayOrigin.y) / rayOrigin.y;
	if (volume > 0.0)
		maxT = min(maxT, volume);

	float result = 1.0;
	float t = minT;

	for (int i = 0; i < 24; i++)
	{
		float h = DE_TestFractal(rayOrigin + vec4(rayDirection, 0.0) * t);
		float s = clamp(8.0 * h / t, 0.0, 1.0);
		result = min(result, s * s * (3.0 - 2.0 * s));
		t += clamp(h, 0.02, 0.2);
		if (result < 0.004 || t > maxT) break;
	}

	return clamp(result, 0.0, 1.0);
}

float CalculateAO(vec4 position, vec3 normal)
{
	float occlusion = 0.0f;
	float scale = 1.0f;
	for (int i = 0; i < 5; i++)
	{
		float h = 0.01 + 0.12 * float(i) / 4.0;
		float dist = DE_TestFractal(position + h * vec4(normal, 1.0));
		occlusion += (h - dist) * scale;
		scale *= 0.95;
		if (occlusion > 0.35) break;
	}

	return clamp(1.0 - 3.0 * occlusion, 0.0, 1.0) * (0.5 + 0.5 * normal.y);
}

vec4 RayMarch(inout vec4 position, vec4 ray, float sharpness, float totalDistance)
{
	float dist = MIN_DISTANCE;
	float s = 0.0;
	float closestDistance = 1.0;
	for (; s < MAX_MARCHES; s += 1.0)
	{
		dist = DE_TestFractal(position);
		if (dist < MIN_DISTANCE)
		{
			s += dist / MIN_DISTANCE;
			break;
		}
		else if (totalDistance > MAX_DISTANCE)
			break;

		totalDistance += dist;
		position += ray * dist;
		closestDistance = min(closestDistance, sharpness * dist / totalDistance);
	}
	return vec4(dist, s, totalDistance, closestDistance);
}


vec3 CalculateNormal(vec4 p, float dx)
{
	const vec3 k = vec3(1, -1, 0);
	return normalize(k.xyy * DE_TestFractal(p + k.xyyz * dx) +
		k.yyx * DE_TestFractal(p + k.yyxz * dx) +
		k.yxy * DE_TestFractal(p + k.yxyz * dx) +
		k.xxx * DE_TestFractal(p + k.xxxz * dx));
}


vec4 Scene(vec4 origin, vec4 ray, float vignette, float totalDistance)
{
	vec4 position = origin;
	vec4 marchResult = RayMarch(position, ray, vignette, totalDistance);
	float dist = marchResult.x;
	float steps = marchResult.y;
	totalDistance = marchResult.z;
	float closest = marchResult.w;

	vec3 color = vec3(0.0);
	float minDistance = MIN_DISTANCE * max(totalDistance * 30.0, 1.0);

	vec3 lightColor = vec3(1.0, 1.0, 1.0);

	if (dist < minDistance)
	{
		vec3 originalColor = clamp(CE_TestFractal(position).xyz, 0.0, 1.0);
		vec3 normal = CalculateNormal(position, MIN_DISTANCE * 10.0);
		vec3 reflected = reflect(ray.xyz, normal);

		float k = 1.0;

		vec3 light = normalize(vec3(-0.5, 0.4, -0.6));
		vec3 halfVector = normalize(light - ray.xyz);

		float diffuse = max(dot(normal, light), 0.0);
		diffuse *= CalculateSoftShadow(position, light, 0.02, 2.5);
		float specular = pow(max(dot(halfVector, normal), 0.0), 32.0f * 32.0f);
		specular *= diffuse;
		specular *= 0.04 + 0.96 * pow(clamp(1.0 - dot(halfVector, light), 0.0, 1.0), 5.0);

		color += originalColor * lightColor * 2.20 * diffuse * vec3(1.30, 1.00, 0.70);
		color += 5.0 * specular * vec3(1.30, 1.00, 0.70) * k;


		float aoDiffuse = max(dot(normal, light), 0.0) * clamp(1.0 - position.y, 0.0, 1.0);
		float ambientOcclusion = CalculateAO(position, normal);
		aoDiffuse *= ambientOcclusion;
		color += 0.55 * aoDiffuse * vec3(0.19, 0.19, 0.19);
	}
	else
	{
		color = vec3(0.5f, 0.5f, 0.5f);
	}

	color = pow(color, vec3(0.8585));
	return vec4(color, totalDistance);
}

mat3 SetCameraView(vec3 cameraPosition, vec3 target, float cr)
{
	vec3 cw = normalize(target - cameraPosition);
	vec3 cp = vec3(sin(cr), cos(cr), 0.0);
	vec3 cu = normalize(cross(cw, cp));
	vec3 cv = cross(cu, cw);
	return mat3(cu, cv, cw);
}

void main()
{
	vec2 uv = (2.0 * gl_FragCoord.xy - u_ScreenResolution) / u_ScreenResolution.y;
	vec2 mouse = u_MousePosition / u_ScreenResolution;


	float focalDistance = 1.0 / tan(PI * 45.0f / 360.0f);

	float time = u_ElapsedTime * 5.0;

	vec3 target = vec3(0.0f, 0.0f, 0.0f);
	//vec3 cameraPosition = target + vec3(12.0 * cos(0.1 * time + mouse.x * 5.0), 5.0 + mouse.y * 5.0, 12.0 * sin(0.1 * time + mouse.x * 5.0));
	mat3 cameraView = SetCameraView(u_CameraPosition, u_CameraPosition + u_CameraForward, 0.0);
	const float focalLength = 8.0f;
	
	vec3 rayDirection = cameraView * normalize(vec3(uv, focalDistance));

	vec4 sceneColor = Scene(vec4(u_CameraPosition, 1.0), vec4(rayDirection, 0.0), 10.0, 0.0);

	o_Color = vec4(sceneColor.xyz, 1.0);
}
