%VULKAN_SDK%\Bin32\glslc.exe shader.vert -o vert.spv
%VULKAN_SDK%\Bin32\glslc.exe test.vert -o test.spv
%VULKAN_SDK%\Bin32\glslc.exe shader.frag -o frag.spv

%VULKAN_SDK%\Bin32\glslc.exe skyboxF.frag -o skyboxF.spv
%VULKAN_SDK%\Bin32\glslc.exe skyboxV.vert -o skyboxV.spv

%VULKAN_SDK%\Bin32\glslc.exe PBR_test.frag -o PBR_test.spv

%VULKAN_SDK%\Bin32\glslc.exe offscreen.vert -o offscreen.vert.spv

pause

