project "GLFW"
	kind "StaticLib"
	language "C"
	architecture "x86_64"

	targetdir "bin/%{cfg.buildcfg}"
	objdir "bin-int/%{cfg.buildcfg}"

	includedirs { "glfw/include/" }

	files
	{
		"glfw/include/GLFW/glfw3.h",
		"glfw/include/GLFW/glfw3native.h",
		"glfw/src/internal.h",
		"glfw/src/platform.h",
		"glfw/src/mappings.h",
		"glfw/src/context.c",
		"glfw/src/init.c",
		"glfw/src/input.c",
		"glfw/src/monitor.c",
		"glfw/src/platform.c",
		"glfw/src/vulkan.c",
		"glfw/src/window.c",
		"glfw/src/egl_context.c",
		"glfw/src/osmesa_context.c",
		"glfw/src/null_platform.h",
		"glfw/src/null_joystick.h",
		"glfw/src/null_init.c",
		"glfw/src/null_monitor.c",
		"glfw/src/null_window.c",
		"glfw/src/null_joystick.c",
	}

	filter "system:windows"
		systemversion "latest"
		staticruntime "On"

		files
		{
			"glfw/src/win32_init.c",
			"glfw/src/win32_module.c",
			"glfw/src/win32_joystick.c",
			"glfw/src/win32_monitor.c",
			"glfw/src/win32_time.h",
			"glfw/src/win32_time.c",
			"glfw/src/win32_thread.h",
			"glfw/src/win32_thread.c",
			"glfw/src/win32_window.c",
			"glfw/src/wgl_context.c",
			"glfw/src/egl_context.c",
			"glfw/src/osmesa_context.c"
		}

		defines 
		{ 
			"_GLFW_WIN32",
			"_CRT_SECURE_NO_WARNINGS"
		}
	
	filter "system:not windows"
		files
		{
			"glfw/src/cocoa_time.h",
			"glfw/src/cocoa_time.c",
			"glfw/src/posix_thread.h",
			"glfw/src/posix_module.c",
			"glfw/src/posix_thread.c",
			"glfw/src/cocoa_platform. ",
			"glfw/src/cocoa_joystick.h",
			"glfw/src/cocoa_init.m",
			"glfw/src/cocoa_joystick.m", 
			"glfw/src/cocoa_monitor.m",
			"glfw/src/cocoa_window.m",    
			"glfw/src/nsgl_context.m",
		}

		defines
		{
			"_GLFW_COCOA",
			"_GL_SILENCE_DEPRECATION"
		}

	filter "configurations:Debug"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		runtime "Release"
		optimize "on"