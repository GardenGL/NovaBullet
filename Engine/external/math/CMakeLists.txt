cmake_minimum_required(VERSION 3.12)

#file(WRITE ${CMAKE_CURRENT_BINARY_DIR}/null.cpp "")

project(Math)

set(MATH_PUBLIC_INCLUDES
include/Math/glmath.hpp include/Math/glmath.cpp

include/Math/Vector2.hpp  include/Math/Vector2.cpp 
include/Math/Vector3.hpp  include/Math/Vector3.cpp 
include/Math/Vector4.hpp  include/Math/Vector4.cpp 
include/Math/Quaternion.hpp  include/Math/Quaternion.cpp 

include/Math/Matrix2x2.hpp  include/Math/Matrix2x2.cpp 
include/Math/Matrix3x3.hpp  include/Math/Matrix3x3.cpp 
include/Math/Matrix4x4.hpp  include/Math/Matrix4x4.cpp 
)

add_library(Math STATIC
	${MATH_PUBLIC_INCLUDES}
)




target_include_directories(Math PUBLIC include)