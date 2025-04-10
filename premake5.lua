workspace "SpaceTraders"
    configurations { "Debug", "Release" }
    platforms { "Win64" }

project "Shared"
    kind "StaticLib"
    language "C++"
    cppdialect "C++17"

    targetdir "bin/Shared/%{cfg.buildcfg}"
    objdir "obj/Shared/%{cfg.buildcfg}"

    files { "src/Shared/**.h", "src/Shared/**.cpp" }
    includedirs { "src/Shared", "vendor" }

    filter "system:linux"
        includedirs { "src/Shared", "vendor", "/usr/include", "/usr/local/include" }
        links { "crypto", "ssl" }

    filter { "configurations:Debug", "system:windows" }
        libdirs { "lib/%{cfg.system}", "lib/%{cfg.system}/MDd" }
        links { "libcrypto", "libssl" }

    filter { "configurations:Release", "system:windows" }
        libdirs { "lib/%{cfg.system}", "lib/%{cfg.system}/MD" }
        links { "libcrypto", "libssl" }

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

    targetdir "bin/SpaceTraders/%{cfg.buildcfg}"
    objdir "obj/SpaceTraders/%{cfg.buildcfg}"

    files { "src/SpaceTraders/**.h", "src/SpaceTraders/**.cpp", "vendor/imgui/**.cpp" }
    includedirs { "src/Shared", "src/SpaceTraders", "vendor" }

    filter "system:linux"
        includedirs { "src/Shared", "src/SpaceTraders", "vendor", "/usr/include", "/usr/local/include" }
        links { "Shared", "crypto", "GL", "glfw", "ssl" }

    filter { "configurations:Debug", "system:windows" }
        libdirs { "lib/%{cfg.system}", "lib/%{cfg.system}/MDd" }
        links { "Shared", "libcrypto", "opengl32", "glfw3", "libssl" }

    filter { "configurations:Release", "system:windows" }
        libdirs { "lib/%{cfg.system}", "lib/%{cfg.system}/MD" }
        links { "Shared", "libcrypto", "opengl32", "glfw3", "libssl" }

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

    targetdir "bin/Contract/%{cfg.buildcfg}"
    objdir "obj/Contract/%{cfg.buildcfg}"

    files { "src/Contract/**.h", "src/Contract/**.cpp" }
    includedirs { "src/Shared", "src/Contract", "vendor" }

    filter "system:linux"
        includedirs { "src/Shared", "src/Contract", "vendor", "/usr/include", "/usr/local/include" }
        links { "Shared", "crypto", "ssl" }

    filter { "configurations:Debug", "system:windows" }
        libdirs { "lib/%{cfg.system}", "lib/%{cfg.system}/MDd" }
        links { "Shared", "libcrypto", "libssl" }

    filter { "configurations:Release", "system:windows" }
        libdirs { "lib/%{cfg.system}", "lib/%{cfg.system}/MD" }
        links { "Shared", "libcrypto", "libssl" }

    filter "configurations:Debug"
        defines { "DEBUG" }
        symbols "On"

    filter "configurations:Release"
        defines { "NDEBUG" }
        optimize "On"
