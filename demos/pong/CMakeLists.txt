
set(PONG_BINARY_DIR ${RAINOUT_BINARY_DIR}/pong)
set(PONG_ASSETS_DIR ${CMAKE_SOURCE_DIR}/demos/pong/assets)
# Rainout final game
add_library(rainout_pong_game SHARED ${CMAKE_SOURCE_DIR}/demos/pong/pong.cpp)
target_include_directories(rainout_pong_game PRIVATE ${RAINOUT_INCLUDES})
target_include_directories(rainout_pong_game PRIVATE ${RAINOUT_CORE_INCLUDES})
target_include_directories(rainout_pong_game PRIVATE ${RAINOUT_INCLUDES})
target_link_libraries(rainout_pong_game rainout_engine)

add_custom_command(
    TARGET rainout_pong_game
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E make_directory ${PONG_BINARY_DIR}
    COMMAND ${CMAKE_COMMAND} -E copy ${RAINOUT_BINARY_DIR}/Launcher.exe ${PONG_BINARY_DIR}/Launcher.exe
    COMMAND ${CMAKE_COMMAND} -E copy ${RAINOUT_BINARY_DIR}/rainout_engine.dll ${PONG_BINARY_DIR}/rainout_engine.dll
    COMMAND ${CMAKE_COMMAND} -E copy ${RAINOUT_BINARY_DIR}/rainout_render.dll ${PONG_BINARY_DIR}/rainout_render.dll
    COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_BINARY_DIR}/demos/pong/debug/rainout_pong_game.dll ${PONG_BINARY_DIR}/rainout_game.dll
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${PONG_ASSETS_DIR} ${PONG_BINARY_DIR}/assets
)
