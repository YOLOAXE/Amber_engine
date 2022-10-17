"%VULKAN_SDK%\Bin\glslc.exe" shader.vert -o vert.spv
"%VULKAN_SDK%\Bin\glslc.exe" shader.frag -o frag.spv
"%VULKAN_SDK%\Bin\glslc.exe" skybox_vs.vert -o skybox_vs.spv
"%VULKAN_SDK%\Bin\glslc.exe" skybox_fs.frag -o skybox_fs.spv
pause

