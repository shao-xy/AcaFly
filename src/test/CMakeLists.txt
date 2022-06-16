add_executable(test_singleton
  singleton.cc
)
add_executable(test_drawer
  drawer.cc
)
target_link_libraries(test_drawer acafly)
