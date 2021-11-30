#version 450 core

layout(location = 0) out vec4 o_Color;

uniform float u_ElapsedTime;
uniform float u_DeltaTime;
uniform vec2 u_ScreenResolution;
uniform vec2 u_MousePosition;
uniform mat4 u_InverseView;
uniform vec3 u_CameraPosition;
uniform vec3 u_CameraForward;

#define PI 3.14159265359

float Random(float s, float minV, float maxV)
{
	float r = sin(s * s * 27.12345 + 1000.9876 / (s * s + 1e-5));
	return (r + 1.0) * 0.5 * (maxV - minV) + minV;
}


//Defines

#define FOG_ENABLED 1
#define SHADOWS_ENABLED 1
#define GLOW_ENABLED 1
#define SUN_ENABLED 1
#define GAMMA_CORRECTION 2.000000
#define AO_STRENGTH 0.010000
#define GLOW_SHARPNESS 100.000000
#define DOF_STRENGTH 1.000000
#define DOF_DISTANCE 50.000000
#define EXPOSURE 1.000000
#define LOD_MULTIPLIER 50.000000
#define FOV 45.000000
#define MAX_DISTANCE 50.000000
#define MAX_MARCHES 1000.000000
#define MIN_DISTANCE 0.000010
#define SHADOW_DARKNESS 0.800000
#define SHADOW_SHARPNESS 8.000000
#define SPECULAR_HIGHTLIGHT 4.000000
#define SUN_SIZE 0.005000
#define SUN_SHARPNESS 2.000000
#define AO_COLOR_DELTA vec3(0.800000, 0.800000, 0.800000)
#define GLOW_COLOR_DELTA vec3(-0.200000, 0.500000, -0.200000)
#define BG_COLOR vec3(0.700000, 0.700000, 0.900000)
#define LIGHT_POSITION vec3(100.000000, 200.000000, 10.000000)
#define LIGHT_COLOR vec3(1.000000, 1.000000, 1.000000)
#define DE DE_New
#define CE CE_New

//Defines

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

float DE_New(vec4 position)
{
	vec4 o = position;
	float d = 1e20;
	RotationXFold(position, 0.965926, 0.258819);
SierpinskiFold(position);
	position *= 1.500000;
	position.xyz += vec3(-3.000000, -1.000000, 0.000000);
	position.z = -abs(position.z + 0.000000) - 0.000000;
	RotationXFold(position, 0.965926, 0.258819);
SierpinskiFold(position);
	position *= 1.500000;
	position.xyz += vec3(-3.000000, -1.000000, 0.000000);
	position.z = -abs(position.z + 0.000000) - 0.000000;
	RotationXFold(position, 0.965926, 0.258819);
SierpinskiFold(position);
	position *= 1.500000;
	position.xyz += vec3(-3.000000, -1.000000, 0.000000);
	position.z = -abs(position.z + 0.000000) - 0.000000;
	RotationXFold(position, 0.965926, 0.258819);
SierpinskiFold(position);
	position *= 1.500000;
	position.xyz += vec3(-3.000000, -1.000000, 0.000000);
	position.z = -abs(position.z + 0.000000) - 0.000000;
	RotationXFold(position, 0.965926, 0.258819);
SierpinskiFold(position);
	position *= 1.500000;
	position.xyz += vec3(-3.000000, -1.000000, 0.000000);
	position.z = -abs(position.z + 0.000000) - 0.000000;
	RotationXFold(position, 0.965926, 0.258819);
SierpinskiFold(position);
	position *= 1.500000;
	position.xyz += vec3(-3.000000, -1.000000, 0.000000);
	position.z = -abs(position.z + 0.000000) - 0.000000;
	RotationXFold(position, 0.965926, 0.258819);
SierpinskiFold(position);
	position *= 1.500000;
	position.xyz += vec3(-3.000000, -1.000000, 0.000000);
	position.z = -abs(position.z + 0.000000) - 0.000000;
	RotationXFold(position, 0.965926, 0.258819);
SierpinskiFold(position);
	position *= 1.500000;
	position.xyz += vec3(-3.000000, -1.000000, 0.000000);
	position.z = -abs(position.z + 0.000000) - 0.000000;
	RotationXFold(position, 0.965926, 0.258819);
SierpinskiFold(position);
	position *= 1.500000;
	position.xyz += vec3(-3.000000, -1.000000, 0.000000);
	position.z = -abs(position.z + 0.000000) - 0.000000;
	RotationXFold(position, 0.965926, 0.258819);
SierpinskiFold(position);
	position *= 1.500000;
	position.xyz += vec3(-3.000000, -1.000000, 0.000000);
	position.z = -abs(position.z + 0.000000) - 0.000000;
	RotationXFold(position, 0.965926, 0.258819);
SierpinskiFold(position);
	position *= 1.500000;
	position.xyz += vec3(-3.000000, -1.000000, 0.000000);
	position.z = -abs(position.z + 0.000000) - 0.000000;
	RotationXFold(position, 0.965926, 0.258819);
SierpinskiFold(position);
	position *= 1.500000;
	position.xyz += vec3(-3.000000, -1.000000, 0.000000);
	position.z = -abs(position.z + 0.000000) - 0.000000;
	RotationXFold(position, 0.965926, 0.258819);
SierpinskiFold(position);
	position *= 1.500000;
	position.xyz += vec3(-3.000000, -1.000000, 0.000000);
	position.z = -abs(position.z + 0.000000) - 0.000000;
	RotationXFold(position, 0.965926, 0.258819);
SierpinskiFold(position);
	position *= 1.500000;
	position.xyz += vec3(-3.000000, -1.000000, 0.000000);
	position.z = -abs(position.z + 0.000000) - 0.000000;
	RotationXFold(position, 0.965926, 0.258819);
SierpinskiFold(position);
	position *= 1.500000;
	position.xyz += vec3(-3.000000, -1.000000, 0.000000);
	position.z = -abs(position.z + 0.000000) - 0.000000;
	position.z = -abs(position.z + 0.000000) - 0.000000;
	d = min(d, DE_Sphere(position - vec4(vec3(0.000000, 0.000000, 0.000000), 0.0), 3.000000));
	return d;
}
vec4 CE_New(vec4 position)
{
	vec4 o = position;
	vec4 color = vec4(1e20);
	vec4 newColor;
	vec3 orbit = vec3(1e20);
	RotationXFold(position, 0.965926, 0.258819);
SierpinskiFold(position);
	orbit = min(orbit, abs((position.xyz - vec3(0.000000, 0.000000, 0.000000)) * vec3(0.800000, 0.200000, 0.000000)));
	position *= 1.500000;
	position.xyz += vec3(-3.000000, -1.000000, 0.000000);
	position.z = -abs(position.z + 0.000000) - 0.000000;
	RotationXFold(position, 0.965926, 0.258819);
SierpinskiFold(position);
	orbit = min(orbit, abs((position.xyz - vec3(0.000000, 0.000000, 0.000000)) * vec3(0.800000, 0.200000, 0.000000)));
	position *= 1.500000;
	position.xyz += vec3(-3.000000, -1.000000, 0.000000);
	position.z = -abs(position.z + 0.000000) - 0.000000;
	RotationXFold(position, 0.965926, 0.258819);
SierpinskiFold(position);
	orbit = min(orbit, abs((position.xyz - vec3(0.000000, 0.000000, 0.000000)) * vec3(0.800000, 0.200000, 0.000000)));
	position *= 1.500000;
	position.xyz += vec3(-3.000000, -1.000000, 0.000000);
	position.z = -abs(position.z + 0.000000) - 0.000000;
	RotationXFold(position, 0.965926, 0.258819);
SierpinskiFold(position);
	orbit = min(orbit, abs((position.xyz - vec3(0.000000, 0.000000, 0.000000)) * vec3(0.800000, 0.200000, 0.000000)));
	position *= 1.500000;
	position.xyz += vec3(-3.000000, -1.000000, 0.000000);
	position.z = -abs(position.z + 0.000000) - 0.000000;
	RotationXFold(position, 0.965926, 0.258819);
SierpinskiFold(position);
	orbit = min(orbit, abs((position.xyz - vec3(0.000000, 0.000000, 0.000000)) * vec3(0.800000, 0.200000, 0.000000)));
	position *= 1.500000;
	position.xyz += vec3(-3.000000, -1.000000, 0.000000);
	position.z = -abs(position.z + 0.000000) - 0.000000;
	RotationXFold(position, 0.965926, 0.258819);
SierpinskiFold(position);
	orbit = min(orbit, abs((position.xyz - vec3(0.000000, 0.000000, 0.000000)) * vec3(0.800000, 0.200000, 0.000000)));
	position *= 1.500000;
	position.xyz += vec3(-3.000000, -1.000000, 0.000000);
	position.z = -abs(position.z + 0.000000) - 0.000000;
	RotationXFold(position, 0.965926, 0.258819);
SierpinskiFold(position);
	orbit = min(orbit, abs((position.xyz - vec3(0.000000, 0.000000, 0.000000)) * vec3(0.800000, 0.200000, 0.000000)));
	position *= 1.500000;
	position.xyz += vec3(-3.000000, -1.000000, 0.000000);
	position.z = -abs(position.z + 0.000000) - 0.000000;
	RotationXFold(position, 0.965926, 0.258819);
SierpinskiFold(position);
	orbit = min(orbit, abs((position.xyz - vec3(0.000000, 0.000000, 0.000000)) * vec3(0.800000, 0.200000, 0.000000)));
	position *= 1.500000;
	position.xyz += vec3(-3.000000, -1.000000, 0.000000);
	position.z = -abs(position.z + 0.000000) - 0.000000;
	RotationXFold(position, 0.965926, 0.258819);
SierpinskiFold(position);
	orbit = min(orbit, abs((position.xyz - vec3(0.000000, 0.000000, 0.000000)) * vec3(0.800000, 0.200000, 0.000000)));
	position *= 1.500000;
	position.xyz += vec3(-3.000000, -1.000000, 0.000000);
	position.z = -abs(position.z + 0.000000) - 0.000000;
	RotationXFold(position, 0.965926, 0.258819);
SierpinskiFold(position);
	orbit = min(orbit, abs((position.xyz - vec3(0.000000, 0.000000, 0.000000)) * vec3(0.800000, 0.200000, 0.000000)));
	position *= 1.500000;
	position.xyz += vec3(-3.000000, -1.000000, 0.000000);
	position.z = -abs(position.z + 0.000000) - 0.000000;
	RotationXFold(position, 0.965926, 0.258819);
SierpinskiFold(position);
	orbit = min(orbit, abs((position.xyz - vec3(0.000000, 0.000000, 0.000000)) * vec3(0.800000, 0.200000, 0.000000)));
	position *= 1.500000;
	position.xyz += vec3(-3.000000, -1.000000, 0.000000);
	position.z = -abs(position.z + 0.000000) - 0.000000;
	RotationXFold(position, 0.965926, 0.258819);
SierpinskiFold(position);
	orbit = min(orbit, abs((position.xyz - vec3(0.000000, 0.000000, 0.000000)) * vec3(0.800000, 0.200000, 0.000000)));
	position *= 1.500000;
	position.xyz += vec3(-3.000000, -1.000000, 0.000000);
	position.z = -abs(position.z + 0.000000) - 0.000000;
	RotationXFold(position, 0.965926, 0.258819);
SierpinskiFold(position);
	orbit = min(orbit, abs((position.xyz - vec3(0.000000, 0.000000, 0.000000)) * vec3(0.800000, 0.200000, 0.000000)));
	position *= 1.500000;
	position.xyz += vec3(-3.000000, -1.000000, 0.000000);
	position.z = -abs(position.z + 0.000000) - 0.000000;
	RotationXFold(position, 0.965926, 0.258819);
SierpinskiFold(position);
	orbit = min(orbit, abs((position.xyz - vec3(0.000000, 0.000000, 0.000000)) * vec3(0.800000, 0.200000, 0.000000)));
	position *= 1.500000;
	position.xyz += vec3(-3.000000, -1.000000, 0.000000);
	position.z = -abs(position.z + 0.000000) - 0.000000;
	RotationXFold(position, 0.965926, 0.258819);
SierpinskiFold(position);
	orbit = min(orbit, abs((position.xyz - vec3(0.000000, 0.000000, 0.000000)) * vec3(0.800000, 0.200000, 0.000000)));
	position *= 1.500000;
	position.xyz += vec3(-3.000000, -1.000000, 0.000000);
	position.z = -abs(position.z + 0.000000) - 0.000000;
	position.z = -abs(position.z + 0.000000) - 0.000000;
	newColor = vec4(orbit, DE_Sphere(position - vec4(vec3(0.000000, 0.000000, 0.000000), 0.0), 3.000000));
	if (newColor.w < color.w) { color = newColor; }
	return color;
}

//DE/CE End

float CalculateSoftShadow(vec4 rayOrigin, vec3 rayDirection, float minT, float maxT)
{
	float volume = (SHADOW_DARKNESS - rayOrigin.y) / rayDirection.y;
	if (volume > 0.0)
		maxT = min(maxT, volume);

	float result = 1.0;
	float t = minT;

	for (int i = 0; i < 24; i++)
	{
		float h = DE(rayOrigin + vec4(rayDirection, 0.0) * t);
		float s = clamp(SHADOW_SHARPNESS * h / t, 0.0, 1.0);
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
		float h = AO_STRENGTH + 0.12 * float(i) / 4.0;
		float dist = DE(position + h * vec4(normal, 1.0));
		occlusion += (h - dist) * scale;
		scale *= 0.95;
		if (occlusion > 0.35) break;
	}

	return clamp(1.0 - 3.0 * occlusion, 0.0, 1.0) * (0.5 + 0.5 * normal.y);
}

vec4 RayMarch(inout vec4 position, inout vec4 ray, float sharpness, float totalDistance)
{
	float dist = MIN_DISTANCE;
	float s = 0.0;
	float closestDistance = 1.0;
	for (; s < MAX_MARCHES; s += 1.0)
	{
		dist = DE(position);
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
	return normalize(k.xyy * DE(p + k.xyyz * dx) +
		k.yyx * DE(p + k.yyxz * dx) +
		k.yxy * DE(p + k.yxyz * dx) +
		k.xxx * DE(p + k.xxxz * dx));
}


vec3 ACESTonemap(vec3 color)
{
	mat3 m1 = mat3(
		0.59719, 0.07600, 0.02840,
		0.35458, 0.90834, 0.13383,
		0.04823, 0.01566, 0.83777
	);
	mat3 m2 = mat3(
		1.60475, -0.10208, -0.00327,
		-0.53108, 1.10813, -0.07276,
		-0.07367, -0.00605, 1.07602
	);
	vec3 v = m1 * color;
	vec3 a = v * (v + 0.0245786) - 0.000090537;
	vec3 b = v * (0.983729 * v + 0.4329510) + 0.238081;
	return clamp(m2 * (a / b), 0.0, 1.0);
}

vec3 GammaCorrect(vec3 color)
{
	return pow(color, vec3(1.0 / GAMMA_CORRECTION));
}

vec4 Scene(vec4 origin, inout vec4 ray, float vignette, float totalDistance)
{
	vec4 position = origin;
	vec4 marchResult = RayMarch(position, ray, GLOW_SHARPNESS, totalDistance);
	float dist = marchResult.x;
	float steps = marchResult.y;
	totalDistance = marchResult.z;
	float closest = marchResult.w;

	vec3 backgroundColor = BG_COLOR - max(ray.y, 0.0) * 0.3;

	vec3 color = vec3(0.0);
	float minDistance = MIN_DISTANCE * max(totalDistance * LOD_MULTIPLIER, 1.0);

	vec3 lightColor = LIGHT_COLOR;

	vec3 light = normalize(vec3(-0.5, 0.4, -0.6));

	if (dist < minDistance)
	{
		vec3 originalColor = clamp(CE(position).xyz, 0.0, 1.0);

		vec3 normal = CalculateNormal(position, MIN_DISTANCE * 10.0);
		vec3 reflected = reflect(ray.xyz, normal);

		float k = 1.0;

		vec3 halfVector = normalize(light - ray.xyz);

		float ambientOcclusion = CalculateAO(position, normal);

		{
			float diffuse = max(dot(normal, light), 0.0);
#if SHADOWS_ENABLED
			diffuse *= CalculateSoftShadow(position, light, 0.02, 2.5);
#endif

			float specular = pow(max(dot(halfVector, normal), 0.0), 4.0f * 4.0f);
			specular *= diffuse;
			specular *= 0.04 + 0.96 * pow(clamp(1.0 - dot(halfVector, light), 0.0, 1.0), 5.0);

			color += originalColor * lightColor * 2.20 * diffuse * vec3(1.30, 1.00, 0.70);
			color += 5.0 * specular * vec3(1.30, 1.00, 0.70) * k;
		}

		{
			float diffuse = sqrt(clamp(0.5 + 0.5 * normal.y, 0.0, 1.0));
			diffuse *= ambientOcclusion;
			float specular = smoothstep(-0.2, 0.2, reflected.y);
			specular *= diffuse;
			specular *= 0.04 + 0.96 * pow(clamp(1.0 + dot(normal, vec3(ray.xyz)), 0.0, 1.0), 5.0);

#if SHADOWS_ENABLED
			specular *= CalculateSoftShadow(position, reflected, 0.02, 2.5);
#endif
			color += color * 0.60 * diffuse * vec3(0.40, 0.60, 1.15);
			color += 2.00 * specular * vec3(0.40, 0.60, 1.30) * k;
		}

		//sss
		{
			float diffuse = pow(clamp(1.0 + dot(normal, ray.xyz), 0.0, 1.0), 2.0);
			diffuse *= ambientOcclusion;
			color += color * 0.25 * diffuse * vec3(1.00, 1.00, 1.00);
		}

#if FOG_ENABLED
		float fog = totalDistance / MAX_DISTANCE;
		color = (1.0 - fog) * color + fog * vec3(0.5f, 0.5f, 0.5f);
#endif
		color *= vignette;

		color *= EXPOSURE;
		color = ACESTonemap(color);
		color = GammaCorrect(color);
	}
	else
	{
		color = backgroundColor;

#if GLOW_ENABLED
		color += (1.0 - closest) * (1.0 - closest) * GLOW_COLOR_DELTA;
#endif

#if SUN_ENABLED
		float sunSpecular = dot(ray.xyz, light) - 1.0 + SUN_SIZE;
		sunSpecular = min(exp(sunSpecular * SUN_SHARPNESS / SUN_SIZE), 1.0);
		color += LIGHT_COLOR * sunSpecular;
#endif
	}

	return vec4(color, totalDistance);
}

void main()
{
	vec2 mouse = u_MousePosition / u_ScreenResolution;
	vec4 color = vec4(0.0);
	float time = u_ElapsedTime * 5.0;
	float focalDistance = 1.0 / tan(PI * FOV / 360.0f);

	vec2 screenPosition = gl_FragCoord.xy / u_ScreenResolution.xy;
	vec2 uv = 2.0 * screenPosition - 1.0;
	uv.x *= u_ScreenResolution.x / u_ScreenResolution.y;


	vec4 position = vec4(u_CameraPosition, 1.0);
	vec4 ray = normalize(vec4(uv, -focalDistance, 0.0));
	ray = u_InverseView * normalize(ray * DOF_DISTANCE);
	float vignette = 1.0 - 0.1f * length(uv);

	vec4 sceneColor = Scene(position, ray, vignette, 0.0);
	color += sceneColor;

	o_Color = vec4(color.rgb, 1.0);
}
