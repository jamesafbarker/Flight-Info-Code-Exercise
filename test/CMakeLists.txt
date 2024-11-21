# Add GoogleTest
enable_testing()
find_package(GTest REQUIRED)

# Set include directories
include_directories(${GTEST_INCLUDE_DIRS} ../include)

# Set Source Files
set(SRC_FILES
    ${CMAKE_SOURCE_DIR}/src/BufferHandler.cpp
    ${CMAKE_SOURCE_DIR}/src/CommunicationProtocol.cpp
    ${CMAKE_SOURCE_DIR}/src/Database.cpp
    ${CMAKE_SOURCE_DIR}/src/FlightInfoLogger.cpp
    ${CMAKE_SOURCE_DIR}/src/FlightInfoData.cpp
    ${CMAKE_SOURCE_DIR}/src/MessageListener.cpp
    ${CMAKE_SOURCE_DIR}/src/PayloadParser.cpp
)
    
# Add the test executable for BufferHandler tests
add_executable(test_bufferhandler
    test_bufferhandler.cpp
    ${SRC_FILES}
)

# Link test executables with GoogleTest and pthread
target_link_libraries(test_bufferhandler ${GTEST_LIBRARIES} pthread)

# Add tests
add_test(NAME BufferHandlerTests COMMAND test_bufferhandler)
