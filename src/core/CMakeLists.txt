ADD_LIBRARY(SalvadorCore
  s_abstract_grid.cpp
  s_abstract_machine.cpp
  s_abstract_pointer.cpp
  s_code_grid.cpp
  s_code_image_pointer.cpp
  s_code_machine.cpp
  s_data_grid.cpp
  s_data_image_pointer.cpp
  s_data_machine.cpp
  s_virtual_machine.cpp)

TARGET_LINK_LIBRARIES(SalvadorCore ${QT_LIBRARIES})
