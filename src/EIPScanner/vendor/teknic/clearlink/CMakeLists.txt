set(SOURCE_FILES 
        ${CMAKE_CURRENT_LIST_DIR}/BaseAssemblyObject.cpp
        ${CMAKE_CURRENT_LIST_DIR}/ConfigAssemblyObject.cpp
        ${CMAKE_CURRENT_LIST_DIR}/InputAssemblyObject.cpp
        ${CMAKE_CURRENT_LIST_DIR}/OutputAssemblyObject.cpp)
        
target_sources(EIPScanner PUBLIC ${SOURCE_FILES})
target_sources(EIPScanner PUBLIC ${SOURCE_FILES})

add_subdirectory(assembly)