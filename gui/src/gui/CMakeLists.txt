#Configure for wxWidgets use
FIND_PACKAGE(wxWidgets COMPONENTS base core)
IF(wxWidgets_FOUND)
  INCLUDE(${wxWidgets_USE_FILE})

  ADD_EXECUTABLE(dawg-gui WIN32 ${PROJ_MACOSX_BUNDLE}
  	app.cpp frame.cpp text.cpp page.cpp
  	app.h frame.h page.h text.h
  	xm.h dawgma.xmh 
    "${CMAKE_CURRENT_BINARY_DIR}/../config.h"
    )
  TARGET_LINK_LIBRARIES(dawg-gui ${CMAKE_REQUIRED_LIBRARIES} ${wxWidgets_LIBRARIES})
  INSTALL(TARGETS dawg-gui RUNTIME DESTINATION bin ${PROJ_INSTALL_EXTRA_ARGS})
ELSE(wxWidgets_FOUND)
  MESSAGE("wxWidgets not found.  Build of dawg-gui skipped")
ENDIF(wxWidgets_FOUND)

