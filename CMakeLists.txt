CMAKE_MINIMUM_REQUIRED(VERSION 3.16)

PROJECT(Loctopus)


SET(CMAKE_C_STANDARD 11)
SET(CMAKE_C_STANDARD_REQUIRED ON)

# Use if there are also .c files not only .h files
ADD_LIBRARY(core
	libs/command.c
	libs/parser.c
	libs/file.c
)
TARGET_INCLUDE_DIRECTORIES(core PUBLIC ${CMAKE_SOURCE_DIR}/libs)

# Use if there are only .h files no .c files
#ADD_LIBRARY(core INTERFACE)
#TARGET_INCLUDE_DIRECTORIES(core INTERFACE ${CMAKE_SOURCE_DIR}/libs)

ADD_EXECUTABLE(run main.c)
TARGET_LINK_LIBRARIES(run PRIVATE core)
