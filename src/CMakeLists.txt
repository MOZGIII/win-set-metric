SET(EXECUTABLE_NAME ${PROJECT_NAME})

SET(LIBRARIES
	iphlpapi
	ws2_32
)

SET(SOURCES
	IfTable2Wrapper.cpp
	IpInterfaceHelper.cpp
	MultibyteString.cpp
)

add_executable(${EXECUTABLE_NAME} main.cpp ${SOURCES})
target_link_libraries(${EXECUTABLE_NAME} ${LIBRARIES})
