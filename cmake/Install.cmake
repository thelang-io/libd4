#
# Copyright (c) Aaron Delasy
# Licensed under the MIT License
#

include(GNUInstallDirs)

if (MINGW OR UNIX)
  configure_file(${PROJECT_NAME}.pc.in ${PROJECT_NAME}.pc @ONLY)

  install(DIRECTORY include/ DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}")
  install(FILES LICENSE DESTINATION "${CMAKE_INSTALL_DOCDIR}")
  install(FILES "${PROJECT_BINARY_DIR}/${PROJECT_NAME}.pc" DESTINATION "${CMAKE_INSTALL_LIBDIR}/pkgconfig")
  install(TARGETS d4 LIBRARY DESTINATION "${CMAKE_INSTALL_LIBDIR}")
endif ()
