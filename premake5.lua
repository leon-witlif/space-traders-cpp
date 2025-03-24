workspace "SpaceTraders"
    configurations { "Debug", "Release" }

project "SpaceTraders"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++17"
    targetdir "bin/%{cfg.buildcfg}"

    files { "src/**.h", "src/**.cpp" }
    includedirs { "vendor/", "/usr/include", "/usr/local/include" }

    links { "crypto", "ssl" }

    filter "configurations:Debug"
        defines { "DEBUG" }
        symbols "On"

    filter "configurations:Release"
        defines {"NDEBUG"}
        optimize "On"
