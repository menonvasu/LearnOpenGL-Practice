add_executable(03_Textures main.cpp)
target_link_libraries(03_Textures PRIVATE glad glfw opengl32)
target_include_directories(03_Textures PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}")

add_custom_command(TARGET 03_Textures POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_newer
        "${CMAKE_CURRENT_SOURCE_DIR}/shader.vs"
        "$<TARGET_FILE_DIR:03_Textures>/shader.vs"
    COMMAND ${CMAKE_COMMAND} -E copy_if_newer
        "${CMAKE_CURRENT_SOURCE_DIR}/shader.fs"
        "$<TARGET_FILE_DIR:03_Textures>/shader.fs"
    COMMAND ${CMAKE_COMMAND} -E copy_if_newer
        "${CMAKE_CURRENT_SOURCE_DIR}/container.jpg"
        "$<TARGET_FILE_DIR:03_Textures>/container.jpg"
    COMMAND ${CMAKE_COMMAND} -E copy_if_newer
        "${CMAKE_CURRENT_SOURCE_DIR}/awesomeface.png"
        "$<TARGET_FILE_DIR:03_Textures>/awesomeface.png"
    COMMENT "Copying shaders and textures to target output directory"
)