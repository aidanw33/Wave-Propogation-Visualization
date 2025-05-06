# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles/wave-propogation-visualization_autogen.dir/AutogenUsed.txt"
  "CMakeFiles/wave-propogation-visualization_autogen.dir/ParseCache.txt"
  "wave-propogation-visualization_autogen"
  )
endif()
