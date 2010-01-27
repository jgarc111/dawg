#Configure for wxWidgets use
FIND_PACKAGE(Boost 1.34.0)
IF(Boost_FOUND)
  INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIRS})
  LINK_DIRECTORIES(${Boost_LIBRARY_DIRS})
  IF(NOT Boost_USE_STATIC_LIBS)
    ADD_DEFINITIONS(-DBOOST_DYN_LINK)
  ENDIF(NOT Boost_USE_STATIC_LIBS)
  SET(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} ${Boost_LIB_DIAGNOSTIC_DEFINITIONS}")
ENDIF(Boost_FOUND)
FIND_PACKAGE(wxWidgets COMPONENTS base core)
IF(wxWidgets_FOUND)
  INCLUDE(${wxWidgets_USE_FILE})

  ADD_EXECUTABLE(dawg-gui WIN32 ${PROJ_MACOSX_BUNDLE}
  	app.cpp frame.cpp page.cpp text.cpp int.cpp double.cpp
  	bool.cpp block.cpp vint.cpp vdouble.cpp vtext.cpp
  	app.h frame.h page.h text.h int.h double.h bool.h block.h vint.h vdouble.h vtext.h
  	xm.h dawgma.xmh
    "${CMAKE_CURRENT_BINARY_DIR}/../config.h"
    )
  TARGET_LINK_LIBRARIES(dawg-gui ${CMAKE_REQUIRED_LIBRARIES} ${wxWidgets_LIBRARIES})
  INSTALL(TARGETS dawg-gui RUNTIME DESTINATION bin ${PROJ_INSTALL_EXTRA_ARGS})
ELSE(wxWidgets_FOUND)
  MESSAGE("wxWidgets not found.  Build of dawg-gui skipped")
ENDIF(wxWidgets_FOUND)

