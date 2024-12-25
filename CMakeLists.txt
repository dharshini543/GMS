cmake_minimum_required(VERSION 3.16)

project(GMS LANGUAGES C)

add_executable(GMS main.c
    billing.h
    billing.c
    cart.h
    cart.c
    enum.h
    file_operations.h
    file_operations.c
    inventory.h
    inventory.c
    report.h
    report.c
    sorting.h
    sorting.c
    start.h
    start.c
    user.h
    user.c



)

include(GNUInstallDirs)
install(TARGETS GMS
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
