cmake_minimum_required(VERSION 3.7)

project(FlightInfoLogger VERSION 1.0)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Include the headers directory
include_directories(include)

# Add source subdirectory
add_subdirectory(src)

# Add test subdirectory
add_subdirectory(test)

# Enable testing 
enable_testing()

# Install service file to system folder
install(TARGETS ${PROJECT_NAME} DESTINATION /usr/bin)
install(FILES ${PROJECT_NAME}.service DESTINATION /etc/systemd/system)