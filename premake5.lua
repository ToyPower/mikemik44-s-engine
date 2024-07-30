premake.tools.gcc.ldflags.flags._Symbols = nil
workspace "MyGameEngine"
	
	architecture "x64"
	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}
	startproject "Sandbox"
	
outputDir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"
includeDir = {}
includeDir["GLFW"] = "MeGameEngine/vendors/glfw/include"
includeDir["GLAD"] = "MeGameEngine/vendors/glad/include"
includeDir["IMGUI"] = "MeGameEngine/vendors/imgui"
includeDir["GLM"] = "MeGameEngine/vendors/glm2"
includeDir["STB"] = "MeGameEngine/vendors/stb"

group "dependecies" 
	include "MeGameEngine/vendors/glfw/premake5.lua"
	include "MeGameEngine/vendors/glad/premake5.lua"
	include "MeGameEngine/vendors/imgui/premake5.lua"
group ""

project "MeGameEngine"
	defines {
		"_CRT_SECURE_NO_WARNINGS",
		"GLFW_INCLUDE_NONE"
	}
	location "MeGameEngine"
	kind "StaticLib"
	language "c++"
	targetdir ("bin/" .. outputDir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputDir .. "/%{prj.name}")
	
	staticruntime "off"
	pchheader "hzpch.h"
	pchsource "MeGameEngine/src/hzpch.cpp"
	cppdialect "C++17"
	files {
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/vendors/glm2/glm/**.hpp",
		"%{prj.name}/vendors/glm2/glm/**.inl",
		"%{prj.name}/vendors/stb/**.cpp",
		"%{prj.name}/vendors/stb/**.h"
	}
	
	includedirs {
		"MeGameEngine/src",
		"MeGameEngine/vendors/stdlog/include",
		"%{includeDir.GLFW}",
		"%{includeDir.GLAD}",
		"%{includeDir.IMGUI}",
		"%{includeDir.GLM}",
		"%{includeDir.STB}",
	}
	
	links {
		"GLFW",
		"GLAD",
		"ImGui",
		"opengl32.lib"
	}
	filter "system:windows"
		
		systemversion "latest"
		
		defines {
			"ME_PLATFORM_WINDOWS",
			"ME_BUILD_DLL"
		}
		
	filter "configurations:Debug"
		defines "ME_Debug"
		runtime "Debug"
		symbols "on"
	filter "configurations:Release"
		defines "ME_Release"
		runtime "Release"
		optimize "speed"
	filter "configurations:Dist"
		defines "ME_Dist"
		runtime "Release"
		optimize "speed"
			
project "Sandbox"
	defines {
		"_CRT_SECURE_NO_WARNINGS",
		"GLFW_INCLUDE_NONE"
	}
	location "Sandbox"
	kind "ConsoleApp"
	language "c++"
	targetdir ("bin/" .. outputDir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputDir .. "/%{prj.name}")
	cppdialect "C++17"
	staticruntime "off"

	files {
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}
	
	includedirs {
		"MeGameEngine/vendors/stdlog/include",
		"MeGameEngine/src",
		"MeGameEngine/vendors",
		"%{includeDir.GLM}",
		"%{includeDir.GLFW}",
		"%{includeDir.GLAD}",
		"%{includeDir.STB}",
	}
	
	links {
		"MeGameEngine"
	}
	
	filter "system:windows"
		
		systemversion "latest"
		
		defines {
			"ME_PLATFORM_WINDOWS"
		}
		
	filter "configurations:Debug"
		defines "ME_Debug"
		runtime "Debug"
		symbols "on"
	filter "configurations:Release"
		defines "ME_Release"
		runtime "Release"
		optimize "speed"
	filter "configurations:Dist"
		defines "ME_Dist"
		runtime "Release"
		optimize "speed"