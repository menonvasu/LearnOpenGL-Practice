add_executable(02_Shaders main.cpp)

target_link_libraries(02_Shaders PRIVATE glad glfw opengl32)

add_custom_command(TARGET 02_Shaders POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${CMAKE_CURRENT_SOURCE_DIR}/shader.vs"
        "$<TARGET_FILE_DIR:02_Shaders>/shader.vs"
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${CMAKE_CURRENT_SOURCE_DIR}/shader.fs"
        "$<TARGET_FILE_DIR:02_Shaders>/shader.fs"
    COMMENT "Copying shaders to target output directory"
)