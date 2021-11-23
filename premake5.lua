workspace "Raymarcher"
	architecture "x64"
	startproject "Raymarcher"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

IncludeDirectories = {}
IncludeDirectories["GLFW"] = "Raymarcher/Dependencies/GLFW/include"
IncludeDirectories["glad"] = "Raymarcher/Dependencies/glad/include"
IncludeDirectories["glm"] = "Raymarcher/Dependencies/glm"
IncludeDirectories["ImGui"] = "Raymarcher/Dependencies/ImGui"


group "Dependencies"
	include "Raymarcher/Dependencies/GLFW"
	include "Raymarcher/Dependencies/glad"
	include "Raymarcher/Dependencies/ImGui/imgui"
group ""

project "Raymarcher"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	location "Raymarcher"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	defines
	{
		"_CRT_SECURE_NO_WARNINGS",
		"GLFW_INCLUDE_NONE"
	}

	files
	{
		"%{prj.name}/main.cpp",
		"%{prj.name}/Layers/**.h",
		"%{prj.name}/Layers/**.cpp",
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/vendor/glm/glm/**.hpp",
		"%{prj.name}/vendor/glm/glm/**.inl",
	}

	includedirs 
	{
		"%{prj.name}/src",
		"%{prj.name}/Layers",
		"%{IncludeDirectories.GLFW}",
		"%{IncludeDirectories.glad}",
		"%{IncludeDirectories.glm}",
		"%{IncludeDirectories.ImGui}",
	}

	links
	{
		"GLFW",
		"glad",
		"ImGui"
	}

	pchheader "rmpch.h"
	pchsource "%{prj.name}/src/rmpch.cpp"
	
	filter "system:windows"
		systemversion "latest"

	filter "configurations:Debug"
		defines "RM_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "RM_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "RM_DIST"
		runtime "Release"
		optimize "on"
