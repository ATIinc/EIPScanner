set(SOURCE_FILES 
        ${CMAKE_CURRENT_LIST_DIR}/BaseAssemblyObject.cpp
        ${CMAKE_CURRENT_LIST_DIR}/MotorInputAssemblyObject.cpp

        ${CMAKE_CURRENT_LIST_DIR}/AttributeBaseObject.cpp
        ${CMAKE_CURRENT_LIST_DIR}/SDMotorConfigObject.cpp
        ${CMAKE_CURRENT_LIST_DIR}/SDMotorInputObject.cpp
        ${CMAKE_CURRENT_LIST_DIR}/SDMotorOutputObject.cpp)
        
target_sources(EIPScanner PUBLIC ${SOURCE_FILES})
target_sources(EIPScanner PUBLIC ${SOURCE_FILES})

add_subdirectory(assembly)