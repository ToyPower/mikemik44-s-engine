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

include "MeGameEngine/vendors/glfw/premake5.lua"
project "MeGameEngine"
	location "MeGameEngine"
	kind "SharedLib"
	language "c++"
	targetdir ("bin/" .. outputDir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputDir .. "/%{prj.name}")
	
	pchheader "hzpch.h"
	pchsource "MeGameEngine/src/hzpch.cpp"

	files {
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}
	
	includedirs {
		"%{prj.name}/vendors/stdlog/include",
		"%{prj.name}/src",
		"%{includeDir.GLFW}"
	}
	
	links {
		"GLFW",
		"opengl32.lib"
	}
	
	filter "system:windows"
		cppdialect "C++17"
		staticruntime "on"
		systemversion "latest"
		
		defines {
			"ME_PLATFORM_WINDOWS",
			"ME_BUILD_DLL"
		}
		
		postbuildcommands {
			("{copy} %{cfg.buildtarget.relpath} ../bin/" .. outputDir .. "/Sandbox")
		}
		
		filter "configurations.Debug"
			defines "ME_Debug"
			symbols "On"
		filter "configurations.Release"
			defines "ME_Release"
			optimize "On"
		filter "configurations.Dist"
			defines "ME_Dist"
			optimize "On"
			
project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "c++"
	targetdir ("bin/" .. outputDir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputDir .. "/%{prj.name}")

	files {
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}
	
	includedirs {
		"MeGameEngine/vendors/stdlog/include",
		"MeGameEngine/src",
		"%{prj.name}/src",
		"%{includeDir.GLFW}"
	}
	
	links {"MeGameEngine"}
	
	filter "system:windows"
		cppdialect "C++17"
		staticruntime "on"
		systemversion "latest"
		
		defines {
			"ME_PLATFORM_WINDOWS"
		}
		
		filter "configurations.Debug"
			defines "ME_Debug"
			symbols "On"
		filter "configurations.Release"
			defines "ME_Release"
			optimize "On"
		filter "configurations.Dist"
			defines "ME_Dist"
			optimize "On"