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

    filter "system:linux"
        includedirs { "src/Shared", "vendor", "/usr/include", "/usr/local/include" }
        links { "crypto", "ssl" }

    filter { "system:windows", "configurations:Debug" }
        includedirs { "src/Shared", "vendor", "$(OPENSSL_ROOT)/include" }
        libdirs { "$(OPENSSL_ROOT)/lib/VC/x64/MDd" }
        links { "libcrypto", "libssl" }

    filter { "system:windows", "configurations:Release" }
        includedirs { "src/Shared", "vendor", "$(OPENSSL_ROOT)/include" }
        libdirs { "$(OPENSSL_ROOT)/lib/VC/x64/MD" }
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

    filter "system:linux"
        includedirs { "src/Shared", "src/SpaceTraders", "vendor", "/usr/include", "/usr/local/include" }
        links { "Shared", "crypto", "GL", "glfw", "ssl" }

    filter { "system:windows", "configurations:Debug" }
        includedirs { "src/Shared", "src/SpaceTraders", "vendor", "$(OPENSSL_ROOT)/include" }
        libdirs { "$(OPENSSL_ROOT)/lib/VC/x64/MDd", "lib/%{cfg.system}" }
        links { "Shared", "libcrypto", "opengl32", "glfw3", "libssl" }

    filter { "system:windows", "configurations:Release" }
        includedirs { "src/Shared", "src/SpaceTraders", "vendor", "$(OPENSSL_ROOT)/include" }
        libdirs { "$(OPENSSL_ROOT)/lib/VC/x64/MD", "lib/%{cfg.system}" }
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

    filter "system:linux"
        includedirs { "src/Shared", "src/Contract", "vendor", "/usr/include", "/usr/local/include" }
        links { "Shared", "crypto", "ssl" }

    filter { "system:windows", "configurations:Debug" }
        includedirs { "src/Shared", "src/Contract", "vendor", "$(OPENSSL_ROOT)/include" }
        libdirs { "$(OPENSSL_ROOT)/lib/VC/x64/MDd" }
        links { "Shared", "libcrypto", "libssl" }

    filter { "system:windows", "configurations:Release" }
        includedirs { "src/Shared", "src/Contract", "vendor", "$(OPENSSL_ROOT)/include" }
        libdirs { "$(OPENSSL_ROOT)/lib/VC/x64/MD" }
        links { "Shared", "libcrypto", "libssl" }

    filter "configurations:Debug"
        defines { "DEBUG" }
        symbols "On"

    filter "configurations:Release"
        defines { "NDEBUG" }
        optimize "On"
