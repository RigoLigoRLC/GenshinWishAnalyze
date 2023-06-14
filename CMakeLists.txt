# CMakeList.txt: GenshinWishAnalyze 的 CMake 项目，在此处包括源代码并定义
# 项目特定的逻辑。
#
cmake_minimum_required (VERSION 3.8)

project ("GenshinWishAnalyze")

# 将源代码添加到此项目的可执行文件。
add_executable (GenshinWishAnalyze
	"main.cpp"
	"GenshinWishAnalyze.h"
	"DataProcessing.cpp"
	"DataTypes.h"
	"InteractiveSession.cpp"
	"GenshinWishAnalyze.manifest"
)

# Add Fmt files
add_subdirectory(fmt)

target_link_libraries(GenshinWishAnalyze
	fmt::fmt-header-only)

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET GenshinWishAnalyze PROPERTY CXX_STANDARD 17)
endif()
