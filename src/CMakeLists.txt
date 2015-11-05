message(STATUS "Sources preparation")

file(GLOB SERVER_SRC
	"${CMAKE_CURRENT_SOURCE_DIR}/server/*"
	"${CMAKE_CURRENT_SOURCE_DIR}/common/*"
)

message("	-> Prepared : Server sources")

file(GLOB CLIENT_SRC
	"${CMAKE_CURRENT_SOURCE_DIR}/client/*"
	"${CMAKE_CURRENT_SOURCE_DIR}/common/*"
)

message("	-> Prepared : Client sources")

message(STATUS "Sources preparation completed")

include_directories(
	${CMAKE_SOURCE_DIR}/include/client
	${CMAKE_SOURCE_DIR}/include/server
	${CMAKE_SOURCE_DIR}/include/common
)

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)

add_executable(
	${SERVER}
	${SERVER_SRC}
)

add_executable(
	${CLIENT}
	${CLIENT_SRC}
)

target_link_libraries(
	${SERVER}
	${SFML_LIBRARIES}
)

target_link_libraries(
	${CLIENT}
	${SFML_LIBRARIES}
)
