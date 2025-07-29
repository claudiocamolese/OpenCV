cmake_minimum_required(VERSION 3.10)
project(DynamicOpenCVExample)

# Trova OpenCV
find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

# Specifica il file da compilare (es. -DTARGET_SRC=Chapter04/03.cpp)
set(TARGET_SRC "" CACHE STRING "Path al file sorgente da compilare (relativo al root)")

# Errore se non specificato
if (NOT TARGET_SRC)
    message(FATAL_ERROR "❌ Devi specificare il file da compilare con -DTARGET_SRC=Chapter04/03.cpp")
endif()

# Nome eseguibile e directory sorgente
get_filename_component(EXEC_NAME ${TARGET_SRC} NAME_WE)     # es: 03
get_filename_component(SRC_DIR ${TARGET_SRC} PATH)          # es: Chapter04

# Directory output dell'eseguibile
set(OUTPUT_PATH ${CMAKE_BINARY_DIR}/${SRC_DIR})

# Crea l'eseguibile
add_executable(${EXEC_NAME} ${TARGET_SRC})

# Imposta la directory di output dell'eseguibile
set_target_properties(${EXEC_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${OUTPUT_PATH}
)

# Collega le librerie OpenCV
target_link_libraries(${EXEC_NAME} ${OpenCV_LIBS})

# Messaggi informativi
message(STATUS "✅ File da compilare: ${TARGET_SRC}")
message(STATUS "📦 Nome eseguibile: ${EXEC_NAME}")
message(STATUS "📁 Directory output: ${OUTPUT_PATH}")