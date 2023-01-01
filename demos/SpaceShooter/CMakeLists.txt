
set(SHOOTER_BINARY_DIR ${RAINOUT_BINARY_DIR}/SpaceShooter)
set(SHOOTER_ASSETS_DIR ${CMAKE_SOURCE_DIR}/demos/SpaceShooter/assets)
# Rainout final game
add_library(rainout_shooter_game SHARED ${CMAKE_SOURCE_DIR}/demos/SpaceShooter/shooter.cpp)
target_include_directories(rainout_shooter_game PRIVATE ${RAINOUT_INCLUDES})
target_include_directories(rainout_shooter_game PRIVATE ${RAINOUT_CORE_INCLUDES})
target_include_directories(rainout_shooter_game PRIVATE ${RAINOUT_INCLUDES})
target_link_libraries(rainout_shooter_game rainout_engine)

add_custom_command(
    TARGET rainout_shooter_game
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E make_directory ${SHOOTER_BINARY_DIR}
    COMMAND ${CMAKE_COMMAND} -E copy ${RAINOUT_BINARY_DIR}/Launcher.exe ${SHOOTER_BINARY_DIR}/Launcher.exe
    COMMAND ${CMAKE_COMMAND} -E copy ${RAINOUT_BINARY_DIR}/rainout_engine.dll ${SHOOTER_BINARY_DIR}/rainout_engine.dll
    COMMAND ${CMAKE_COMMAND} -E copy ${RAINOUT_BINARY_DIR}/rainout_render.dll ${SHOOTER_BINARY_DIR}/rainout_render.dll
    COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_BINARY_DIR}/demos/SpaceShooter/debug/rainout_shooter_game.dll ${SHOOTER_BINARY_DIR}/rainout_game.dll
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${SHOOTER_ASSETS_DIR} ${SHOOTER_BINARY_DIR}/assets
)
