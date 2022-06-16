add_subdirectory(core)
add_subdirectory(test)

add_library(acafly SHARED
  $<TARGET_OBJECTS:acafly_obj>
)
add_library(acafly_static STATIC
  $<TARGET_OBJECTS:acafly_obj>
)
set_target_properties(acafly_static PROPERTIES
  OUTPUT_NAME acafly
  PUBLIC_HEADER include/AcaFly.h
)
target_link_libraries(acafly ${OPENGL_LIBRARIES} ${GLUT_LIBRARY})
target_link_libraries(acafly_static ${OPENGL_LIBRARIES} ${GLUT_LIBRARY})

# Installation to system-wide library dirs
install(TARGETS acafly acafly_static
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
  PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)
