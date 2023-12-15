cmake_minimum_required(VERSION 2.8.12)

project(SharedMemoryCppToPython)

find_package(protobuf CONFIG REQUIRED)

if(protobuf_VERBOSE)
  message(STATUS "Using Protocol Buffers ${protobuf_VERSION}")
endif()

set(CMAKE_INCLUDE_CURRENT_DIR TRUE)

list(APPEND SRCS
    include/SharedMemoryManager.hpp
    # include/mesh.pb.cc
    test.cpp
)
set(PROTOS mesh.proto)


if(protobuf_MODULE_COMPATIBLE) #Legacy Support
    protobuf_generate_cpp(PROTO_SRCS PROTO_HDRS ${${PROTOS}})
    list(APPEND SRCS PROTO_SRCS PROTO_HDRS)
endif()

add_executable(run ${SRCS} ${PROTOS})
target_include_directories(run PUBLIC ${PROTOBUF_INCLUDE_DIRS})
# target_link_libraries(run ${PROTOBUF_LIBRARIES})
target_link_libraries(run protobuf::libprotobuf)
protobuf_generate(TARGET run)


# foreach(example add_person list_people)
#   set(${example}_SRCS ${example}.cc)
#   set(${example}_PROTOS addressbook.proto)

#   #Code Generation
#   if(protobuf_MODULE_COMPATIBLE) #Legacy Support
#     protobuf_generate_cpp(${example}_PROTO_SRCS ${example}_PROTO_HDRS ${${example}_PROTOS})
#     list(APPEND ${example}_SRCS ${${example}_PROTO_SRCS} ${${example}_PROTO_HDRS})
#   endif()

#   #Executable setup
#   set(executable_name ${example}_cpp)
#   add_executable(${executable_name} ${${example}_SRCS} ${${example}_PROTOS})
#   if(protobuf_MODULE_COMPATIBLE) #Legacy mode
#     target_include_directories(${executable_name} PUBLIC ${PROTOBUF_INCLUDE_DIRS})
#     target_link_libraries(${executable_name} ${PROTOBUF_LIBRARIES})
#   else()
#     target_link_libraries(${executable_name} protobuf::libprotobuf)
#     protobuf_generate(TARGET ${executable_name})
#   endif()

# endforeach()