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

include "../../Libs/glfwPremake5.lua"
include "../../Libs/glmPremake5.lua"
include "../../Libs/gladPremake5.lua"

project "Intro"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++17"
	architecture "x64"

    targetdir "bin/%{cfg.buildcfg}"
    objdir "bin-int/%{cfg.buildcfg}"

    includedirs
    {
        "../../Libs/glfw/include/", 
        "../../Libs/glm/", 
        "../../Libs/glad/include/",
    }

    files
    {
        "Src/**.cpp",
        "Src/**.h"

    }
    links
    {
        "GLFW", 
        "GLM", 
        "GLAD",
    }
    filter "system:windows"
		systemversion "latest"
		staticruntime "On"
        links
        {
            "OpenGL32"
        }
    filter "system:macosx"
        links
        {
            "OpenGL.framework",
            "Cocoa.framework",
            "IOKit.framework",
            "CoreFoundation.framework"
        }
        defines
        {
            "GL_SILENCE_DEPRECATION"
        }