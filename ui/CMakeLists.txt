add_library(ui_lib MainApp.cpp MainApp.h command.h types.h types.cpp)

target_link_libraries(ui_lib ncurses)