$VULKAN_SDK/bin/glslc shader.vert -o vert.spv
$VULKAN_SDK/bin/glslc test.vert -o test.spv
$VULKAN_SDK/bin/glslc shader.frag -o frag.spv

$VULKAN_SDK/bin/glslc skyboxF.frag -o skyboxF.spv
$VULKAN_SDK/bin/glslc skyboxV.vert -o skyboxV.spv

$VULKAN_SDK/bin/glslc PBR_test.frag -o PBR_test.spv

$VULKAN_SDK/bin/glslc offscreen.vert -o offscreen.vert.spv