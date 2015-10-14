message(STATUS "Sources preparation")

set(SERVER_SRC
	${CMAKE_CURRENT_SOURCE_DIR}/server0/download.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/server0/listFiles.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/server0/server0.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/server0/upload.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/common/fileExist.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/common/getFileLength.cpp
)

message("	-> Prepared : Server sources")

set(CLIENT_SRC
	${CMAKE_CURRENT_SOURCE_DIR}/client0/client0.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/client0/download.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/client0/percentageDisplay.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/client0/retrieveFileList.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/client0/serverAnsInterpret.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/client0/setStdcinEcho.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/client0/upload.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/client0/userInputInterpret.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/common/fileExist.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/common/getFileLength.cpp
)

message("	-> Prepared : Client sources")

include_directories(${CMAKE_SOURCE_DIR}/include/)

message(STATUS "Sources preparation completed")

include_directories(
	${CMAKE_SOURCE_DIR}/include
	SYSTEM ${SFML_INCLUDE_DIR}
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
