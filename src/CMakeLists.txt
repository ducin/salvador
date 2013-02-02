INCLUDE(${QT_USE_FILE})

ADD_SUBDIRECTORY(core)

ADD_EXECUTABLE(salvador-console console.cpp)
TARGET_LINK_LIBRARIES(salvador-console SalvadorCore)