set (WORLD_SRCS
	main.cpp
	pktnkju.cpp
)

set (WORLD_HDRS
	pktnkju.hpp
)

qt5_wrap_cpp (WORLD_SRCS ${WORLD_HDRS})

add_executable (WORLD ${WORLD_SRCS})
target_link_libraries (WORLD ${Qt5Widgets_LIBRARIES})
