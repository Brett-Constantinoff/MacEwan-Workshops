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
include "../../Libs/imguiPremake5.lua"
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
        "../../Libs/imgui/", 
        "../../Libs/glad/include/",
    }

    files
    {
        "Src/**.cpp"
    }

    links
    {
        "GLFW", 
        "GLM", 
        "ImGui" ,
        "GLAD",
        "OpenGL32"
    }