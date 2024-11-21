set(SOURCES
    main.cpp
    BufferHandler.cpp
    Database.cpp
    FlightInfoData.cpp
    FlightInfoLogger.cpp
    CommunicationProtocol.cpp
    MessageListener.cpp
    PayloadParser.cpp
)

include_directories(${CMAKE_SOURCE_DIR}/include)

add_executable(${PROJECT_NAME} ${SOURCES})

install(TARGETS ${PROJECT_NAME} DESTINATION ${CMAKE_INSTALL_PREFIX}/bin)