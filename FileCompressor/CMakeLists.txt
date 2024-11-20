# Define a versão mínima do CMake
cmake_minimum_required(VERSION 3.10)

# Define o nome do projeto
project(SearchMethodsComparison)

# Define a versão do padrão C++
set(CMAKE_CXX_STANDARD 17)

# Busca todos os arquivos .cpp na pasta atual
file(GLOB SRC_FILES "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")

# Adiciona o executável usando todos os arquivos encontrados
add_executable(SearchMethodsComparison ${SRC_FILES})

# Inclui o diretório atual para que os cabeçalhos sejam encontrados
target_include_directories(SearchMethodsComparison PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
