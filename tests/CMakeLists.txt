aux_source_directory(. TEST_SRC_LIST)

foreach (TEST_SRC ${TEST_SRC_LIST})
  get_filename_component(TEST_EXE_NAME ${TEST_SRC} NAME_WE)
  if(TEST_EXE_NAME MATCHES "^test_[a-z]+[0-9]?$")
    add_executable(${TEST_EXE_NAME} ${TEST_SRC})
    target_link_libraries(${TEST_EXE_NAME} ${LINK_LIB_LIST})
  else()
    message(STATUS "检查命名是否正确 ${TEST_EXE_NAME} ${TEST_SRC}")
  endif()

endforeach()

