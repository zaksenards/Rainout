
set(CONTROLLER_BINARY_DIR ${RAINOUT_BINARY_DIR}/controller)
set(CONTROLLER_ASSETS_DIR ${CMAKE_SOURCE_DIR}/demos/controller/assets)
# Rainout final game
add_library(rainout_controller_game SHARED ${CMAKE_SOURCE_DIR}/demos/controller/controller.cpp)
target_include_directories(rainout_controller_game PRIVATE ${RAINOUT_INCLUDES})
target_include_directories(rainout_controller_game PRIVATE ${RAINOUT_CORE_INCLUDES})
target_include_directories(rainout_controller_game PRIVATE ${RAINOUT_INCLUDES})
target_link_libraries(rainout_controller_game rainout_engine)

add_custom_command(
    TARGET rainout_controller_game
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E make_directory ${CONTROLLER_BINARY_DIR}
    COMMAND ${CMAKE_COMMAND} -E copy ${RAINOUT_BINARY_DIR}/Launcher.exe ${CONTROLLER_BINARY_DIR}/Launcher.exe
    COMMAND ${CMAKE_COMMAND} -E copy ${RAINOUT_BINARY_DIR}/rainout_engine.dll ${CONTROLLER_BINARY_DIR}/rainout_engine.dll
    COMMAND ${CMAKE_COMMAND} -E copy ${RAINOUT_BINARY_DIR}/rainout_render.dll ${CONTROLLER_BINARY_DIR}/rainout_render.dll
    COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_BINARY_DIR}/demos/controller/debug/rainout_controller_game.dll ${CONTROLLER_BINARY_DIR}/rainout_game.dll
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${CONTROLLER_ASSETS_DIR} ${CONTROLLER_BINARY_DIR}/assets
)
