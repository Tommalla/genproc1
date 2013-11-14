set (WORLD_SRCS
	main.cpp
	pkt.cpp
	calc.cpp
)

set (WORLD_HDRS
	pkt.hpp
	calc.hpp
)

qt5_wrap_cpp (WORLD_SRCS ${WORLD_HDRS})

add_executable (WORLD ${WORLD_SRCS})
target_link_libraries (WORLD ${Qt5Widgets_LIBRARIES})
