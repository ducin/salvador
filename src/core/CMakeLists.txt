ADD_LIBRARY(SalvadorCore
  sabstractgrid.cpp
  sabstractmachine.cpp
  sabstractpointer.cpp
  scodegrid.cpp
  scodeimagepointer.cpp
  scodemachine.cpp
  sdatagrid.cpp
  sdataimagepointer.cpp
  sdatamachine.cpp
  svirtualmachine.cpp)

TARGET_LINK_LIBRARIES(SalvadorCore ${QT_LIBRARIES})
