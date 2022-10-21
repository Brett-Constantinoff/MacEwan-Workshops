workspace "Workshop"
    configurations { "Debug", "Release" }
    startproject "Intro"
    flags { "MultiProcessorCompile" }

    filter "configurations:Debug"
        defines { "DEBUG", "DEBUG_SHADER" }
        symbols "On"

    filter "configurations:Release"
        defines { "RELEASE" }
        optimize "Speed"
        flags { "LinkTimeOptimization" }

project "Workshop2"
    kind "ConsoleApp"
    language "C"
	architecture "x64"

    targetdir "bin/%{cfg.buildcfg}"
    objdir "bin-int/%{cfg.buildcfg}"

    files
    {
        "Src/**.c",
        "Src/**.h"
    }