cmake_minimum_required(VERSION 3.10)  # Define a versão mínima do CMake necessária

project(HellDefenderRE C)  # Define o nome do projeto e especifica que é um projeto em C

set(CMAKE_C_STANDARD 99)  # Define o padrão da linguagem C como C99

include_directories(include)  # Adiciona o diretório 'include/' aos paths de headers
include_directories(libraries/raylib/src)  # Adiciona os headers da Raylib (localizados em 'libraries/raylib/src')

add_subdirectory(libraries/raylib)  # Adiciona a Raylib como subdiretório (ela será compilada junto com seu projeto)

file(GLOB_RECURSE SOURCES "src/*.c")  # Procura recursivamente todos os arquivos .c na pasta 'src/' e guarda na variável SOURCES

add_executable(HellDefender ${SOURCES})  # Cria o executável 'HellDefender' a partir dos arquivos fonte encontrados

# Linka bibliotecas diferentes dependendo do sistema operacional
if(WIN32)
    target_link_libraries(HellDefender raylib winmm gdi32)  # No Windows, linka com Raylib, winmm (áudio) e gdi32 (gráficos)
elseif(APPLE)
    target_link_libraries(HellDefender raylib m)  # No macOS, linka com Raylib e a biblioteca matemática
else()
    target_link_libraries(HellDefender raylib m pthread dl rt GL)  # No Linux, linka com Raylib e bibliotecas essenciais
endif()

# Copia a pasta 'assets' para o mesmo diretório do executável após a compilação
add_custom_command(TARGET HellDefender POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/assets $<TARGET_FILE_DIR:HellDefender>/assets
)

# Cria o alvo personalizado 'run' que compila e executa o jogo com 'make run'
add_custom_target(run
    COMMAND HellDefender  # Comando para rodar o jogo
    DEPENDS HellDefender  # Garante que o jogo esteja compilado antes de rodar
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}  # Define o diretório de trabalho como o diretório de build
)