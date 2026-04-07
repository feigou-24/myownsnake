cmake_minimum_required(VERSION 3.10)
project(myownsnake LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 包含目录
include_directories(src/include)

# 收集所有源文件
set(SOURCES
    src/main.cpp
    
    # Core modules
    src/core/GameLoop.cpp
    src/core/StateMachine.cpp
    
    # Systems
    src/systems/TimeSystem.cpp
    src/systems/InputSystem.cpp
    src/systems/RenderSystem.cpp
    
    # Gameplay
    src/gameplay/Snake.cpp
    src/gameplay/Food.cpp
    
    # Persistence
    src/persistence/SaveSystem.cpp
)

# 创建可执行文件
add_executable(myownsnake ${SOURCES})

# 链接 Windows 库
if(WIN32)
    target_link_libraries(myownsnake)
endif()
