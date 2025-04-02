workspace "SpaceTraders"
    configurations { "Debug", "Release" }

project "Shared"
    kind "StaticLib"
    language "C++"
    cppdialect "C++17"

    files { "src/Shared/**.h", "src/Shared/**.cpp" }
    includedirs { "src/Shared", "vendor", "/usr/include", "/usr/local/include" }

    targetdir "bin/Shared/%{cfg.buildcfg}"
    objdir "obj/Shared/%{cfg.buildcfg}"

    links { "crypto", "ssl" }

    filter "configurations:Debug"
        defines { "DEBUG" }
        symbols "On"

    filter "configurations:Release"
        defines { "NDEBUG" }
        optimize "On"

project "SpaceTraders"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++17"

    files { "src/SpaceTraders/**.h", "src/SpaceTraders/**.cpp", "vendor/imgui/**.cpp" }
    includedirs { "src/Shared", "src/SpaceTraders", "vendor", "/usr/include", "/usr/local/include" }

    targetdir "bin/SpaceTraders/%{cfg.buildcfg}"
    objdir "obj/SpaceTraders/%{cfg.buildcfg}"

    links { "Shared", "crypto", "GL", "glfw", "ssl" }

    filter "configurations:Debug"
        defines { "DEBUG" }
        symbols "On"

    filter "configurations:Release"
        defines { "NDEBUG" }
        optimize "On"

project "Contract"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++17"

    files { "src/Contract/**.h", "src/Contract/**.cpp" }
    includedirs { "src/Shared", "src/Contract", "vendor" }

    targetdir "bin/Contract/%{cfg.buildcfg}"
    objdir "obj/Contract/%{cfg.buildcfg}"

    filter "configurations:Debug"
        defines { "DEBUG" }
        symbols "On"

    filter "configurations:Release"
        defines { "NDEBUG" }
        optimize "On"
