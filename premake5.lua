workspace "Algolang"
	configurations {"Release", "Debug"}
	architecture "x86"
	language "C++"
    cppdialect "C++11"
	targetdir "build/%{prj.name}/%{cfg.buildcfg}"
    objdir    "build/objs"
    characterset("MBCS")
    buildoptions { }
	location "./"
	project "Algolang"
	includedirs {
		"include/"
	}
	files {
		"src/*.cpp",
		"include/*.h",
		"include/*.hpp",
		"premake5.lua"
	}
	filter "configurations:Release"
		kind "ConsoleApp"
		optimize "On"
	filter "configurations:Debug" 
		kind "ConsoleApp"
		symbols "On"
	
