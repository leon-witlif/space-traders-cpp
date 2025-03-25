workspace "SpaceTraders"
    configurations { "Debug", "Release" }

project "SpaceTraders"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++17"

    files { "src/**.h", "src/**.cpp", "vendor/imgui/**.cpp" }
    includedirs { "src", "vendor", "/usr/include", "/usr/local/include" }

    targetdir "bin/%{cfg.buildcfg}"
    objdir "obj/%{cfg.buildcfg}"

    links { "crypto", "GL", "glfw", "ssl" }

    filter "configurations:Debug"
        defines { "DEBUG" }
        symbols "On"

    filter "configurations:Release"
        defines {"NDEBUG"}
        optimize "On"
