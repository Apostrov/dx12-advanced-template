workspace "Advanced technics"
   configurations { "Debug", "Release" }
   language "C++"
   architecture "x64"
   systemversion "latest"
   toolset "v141"
   optimize "Speed"
   links { "d3d12", "dxgi", "d3dcompiler" }
   filter("configurations:Debug")
      defines({ "DEBUG" })
      symbols("On")
      optimize("Off")
      targetdir ("bin/debug")
   filter("configurations:Release")
      defines({ "NDEBUG" })
      symbols("On")
      targetdir ("bin/release")

   project "DX12 window"
      kind "WindowedApp"
      entrypoint "WinMainCRTStartup"
      includedirs { "src" }
      includedirs { "libs/D3DX12" }
      includedirs { "libs/tinyobjloader" }
      includedirs { "libs/stb" }
      files { "src/dx12_labs.h" }
      files { "src/renderer.h", "src/renderer.cpp"}
      files { "libs/tinyobjloader/tiny_obj_loader.h"}
      files { "libs/stb/stb_image.h" }
      --files { "src/model_loader.h", "src/model_loader.cpp"}
      files { "src/win32_window.h", "src/win32_window.cpp"}
      files { "src/win32_window_main.cpp" }
      postbuildcommands {
         "{COPY} shaders/**.hlsl \"%{cfg.buildtarget.directory}\"",
         "{COPY} models/**.obj \"%{cfg.buildtarget.directory}\"",
         "{COPY} models/**.mtl \"%{cfg.buildtarget.directory}\"",
         "{COPY} models/**.jpg \"%{cfg.buildtarget.directory}\"",
         "{COPY} models/**.png \"%{cfg.buildtarget.directory}\""
       }