set(SOURCE_FILES 
        ${CMAKE_CURRENT_LIST_DIR}/clearlink/AttributeBaseObject.cpp
        ${CMAKE_CURRENT_LIST_DIR}/clearlink/SDMotorConfigObject.cpp
        ${CMAKE_CURRENT_LIST_DIR}/clearlink/SDMotorInputObject.cpp
        ${CMAKE_CURRENT_LIST_DIR}/clearlink/SDMotorOutputObject.cpp
        ${CMAKE_CURRENT_LIST_DIR}/clearlink/utils/BaseAssemblyData.cpp
        # ${CMAKE_CURRENT_LIST_DIR}/clearlink/utils/IOInputData.cpp
        )
        
target_sources(EIPScanner PUBLIC ${SOURCE_FILES})
target_sources(EIPScanner PUBLIC ${SOURCE_FILES})