set(SOURCE_FILES 
        ${CMAKE_CURRENT_LIST_DIR}/BaseAssemblyObject.cpp
        ${CMAKE_CURRENT_LIST_DIR}/MotorConfigAssemblyObject.cpp
        ${CMAKE_CURRENT_LIST_DIR}/MotorInputAssemblyObject.cpp
        ${CMAKE_CURRENT_LIST_DIR}/MotorOutputAssemblyObject.cpp)
        
target_sources(EIPScanner PUBLIC ${SOURCE_FILES})
target_sources(EIPScanner PUBLIC ${SOURCE_FILES})

add_subdirectory(assembly)