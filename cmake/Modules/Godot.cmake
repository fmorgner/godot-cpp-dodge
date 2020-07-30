function(godot_register_library TARGET)
    if(DEFINED ${PROJECT_NAME}_GODOT_LIBRARIES)
        if(${TARGET} IN_LIST ${${PROJECT_NAME}_GODOT_LIBRARIES})
            message(FATAL_ERROR "Library ${TARGET} has already been registered")
        endif()
    endif()

    if(NOT DEFINED ${PROJECT_NAME}_${TARGET}_GODOT_RESOURCE_ID)
        set(${PROJECT_NAME}_${TARGET}_GODOT_RESOURCE_ID "10000")
    endif()

    message(STATUS "Godot: Registering library ${TARGET}")

    math(EXPR ${PROJECT_NAME}_${TARGET}_GODOT_RESOURCE_ID "${${PROJECT_NAME}_${TARGET}_GODOT_RESOURCE_ID} + 1")
    set(${PROJECT_NAME}_${TARGET}_GODOT_RESOURCE_ID ${${PROJECT_NAME}_${TARGET}_GODOT_RESOURCE_ID} PARENT_SCOPE)

    list(APPEND ${PROJECT_NAME}_GODOT_LIBRARIES TARGET)
    set(${PROJECT_NAME}_GODOT_LIBRARIES ${${PROJECT_NAME}_GODOT_LIBRARIES} PARENT_SCOPE)

    set(${TARGET}_GODOT_LIBRARY "${TARGET}.gdnlib")
    set(${TARGET}_GODOT_CONFIGURATION "")

    ### [general] Section
    string(APPEND ${TARGET}_GODOT_CONFIGURATION "[general]\n\n")
    string(APPEND ${TARGET}_GODOT_CONFIGURATION "singleton=false\n")
    string(APPEND ${TARGET}_GODOT_CONFIGURATION "load_once=true\n")
    string(APPEND ${TARGET}_GODOT_CONFIGURATION "symbol_prefix=\"godot_\"\n")
    string(APPEND ${TARGET}_GODOT_CONFIGURATION "reloadable=true\n")
    string(APPEND ${TARGET}_GODOT_CONFIGURATION "\n")

    ### [entry] Sections
    string(APPEND ${TARGET}_GODOT_CONFIGURATION "[entry]\n\n")
    string(APPEND ${TARGET}_GODOT_CONFIGURATION "X11.64=\"res://bin/linux/lib${TARGET}.so\"\n")
    string(APPEND ${TARGET}_GODOT_CONFIGURATION "Windows.64=\"res://bin/windows/lib${TARGET}.dll\"\n")
    string(APPEND ${TARGET}_GODOT_CONFIGURATION "OSX.64=\"res://bin/osx/lib${TARGET}.dylib\"\n")
    string(APPEND ${TARGET}_GODOT_CONFIGURATION "\n")

    ### [dependencies] Sections
    string(APPEND ${TARGET}_GODOT_CONFIGURATION "[dependencies]\n\n")
    string(APPEND ${TARGET}_GODOT_CONFIGURATION "X11.64=[ ]\n")
    string(APPEND ${TARGET}_GODOT_CONFIGURATION "Windows.64=[ ]\n")
    string(APPEND ${TARGET}_GODOT_CONFIGURATION "OSX.64=[ ]\n")
    
    file(WRITE "${PROJECT_BINARY_DIR}/${TARGET}.gdnlib" ${${TARGET}_GODOT_CONFIGURATION})
    install(FILES "${PROJECT_BINARY_DIR}/${TARGET}.gdnlib"
        DESTINATION "bin"
    )
endfunction()

function(godot_register_class TARGET CLASS)
    if(NOT ${TARGET} IN_LIST ${${PROJECT_NAME}_GODOT_LIBRARIES})
        message(FATAL_ERROR "Library ${TARGET} that has not been registered")
    endif()

    if(DEFINED ${PROJECT_NAME}_${TARGET}_GODOT_CLASSES)
        if(${CLASS} IN_LIST ${${PROJECT_NAME}_${TARGET}_GODOT_CLASSES})
            message(FATAL_ERROR "Class ${CLASS} in ${TARGET} has already been registered")
        endif()
    endif()

    message(STATUS "Godot: Registering class ${CLASS} in ${TARGET}")

    set(CLASS_CONFIGURATION "")

    ### [gdresource] Section
    string(APPEND CLASS_CONFIGURATION "[gd_resource type=\"NativeScript\" load_steps=2 format=2]\n")
    string(APPEND CLASS_CONFIGURATION "\n")

    ### [ext_resource] Section
    string(APPEND CLASS_CONFIGURATION "[ext_resource path=\"res://bin/${TARGET}.gdnlib\" type=\"GDNativeLibrary\" id=${${PROJECT_NAME}_${TARGET}_GODOT_RESOURCE_ID}]\n")
    string(APPEND CLASS_CONFIGURATION "\n")

    ### [resource] Section
    string(APPEND CLASS_CONFIGURATION "[resource]\n\n")
    string(APPEND CLASS_CONFIGURATION "resource_name = \"${TARGET}\"\n")
    string(APPEND CLASS_CONFIGURATION "class_name = \"${CLASS}\"\n")
    string(APPEND CLASS_CONFIGURATION "library = ExtResource( ${${PROJECT_NAME}_${TARGET}_GODOT_RESOURCE_ID} )\n")
    string(APPEND CLASS_CONFIGURATION "\n")

    file(WRITE "${PROJECT_BINARY_DIR}/${TARGET}_${CLASS}.gdns" ${CLASS_CONFIGURATION})
    install(FILES "${PROJECT_BINARY_DIR}/${TARGET}_${CLASS}.gdns"
        DESTINATION "bin"
    )
endfunction()