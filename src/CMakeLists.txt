set (WORLD_SRCS
	Map.cpp
	main.cpp
	Point.cpp
	calc.cpp
)

set (WORLD_HDRS
	Map.hpp
	Point.hpp
	calc.hpp
)

set (GUI_HEADERS
	MainWindow.hpp
  )

set (GUI_SOURCES
	MainWindow.cpp
  )

set (FORMS
	MainWindow.ui
  )

qt5_wrap_cpp (GUI_SOURCES ${GUI_HEADERS})
#qt5_wrap_cpp (MOC_SOURCES ${MOC_HEADERS})
qt5_wrap_ui (FORMS ${FORMS})

#qt5_wrap_cpp (WORLD_SRCS ${WORLD_HDRS})

include_directories (${CMAKE_CURRENT_BINARY_DIR})
add_executable (WORLD ${WORLD_SRCS} ${FORMS} ${GUI_SOURCES})
target_link_libraries (WORLD ${Qt5Widgets_LIBRARIES})
