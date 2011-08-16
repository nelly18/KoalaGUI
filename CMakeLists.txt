set (PROJECT_OUTPUT_NAME KoalaGUI)
project(KoalaGUI)

cmake_minimum_required( VERSION 2.6 )

INCLUDE(FindQt4)
find_package( Qt4 REQUIRED )
set (QT_USE_QTSCRIPT 1)
include( ${QT_USE_FILE})
add_definitions(-DUNICODE)

if (WIN32)
include_directories (C:/qwt-6.0.0/src)
set (QWT6_LIB C:/qwt-6.0.0/lib/libqwtd.a)
endif (WIN32)

if (UNIX)
include_directories (/usr/include/qwt6)
set (QWT6_LIB -lqwt6)
endif (UNIX)

include_directories(
${CMAKE_CURRENT_BINARY_DIR}
)

################################################################
# src
################################################################

set (src_SRC
main.cpp
mainwindow.cpp
serialgate.cpp
proximitysensorpainter.cpp
sensor.cpp
analogsensorgraph.cpp
colorpalettedialog.cpp
analoghistogram.cpp
speedcontrol.cpp
pidregulator.cpp
inputsoutputstab.cpp
console.cpp
batterycharge.cpp
statusbarwidget.cpp
script.cpp
scripttab.cpp
analogvaluesloader.cpp
)

set (src_HEADERS
mainwindow.h
proximitysensorpainter.h
sensor.h
analogsensorgraph.h
colorpalettedialog.h
speedcontrol.h
pidregulator.h
inputsoutputstab.h
console.h
batterycharge.h
statusbarwidget.h
script.h
scripttab.h
analogvaluesloader.h
)

set (src_UI
mainwindow.ui
colorpalettedialog.ui
form.ui
)

################################################################
# all
################################################################
set(
	SOURCES
	${src_SRC}
)

set(
	HEADERS
	${src_HEADERS}
)

set(
	UI
	${src_UI}
)

qt4_wrap_ui( UI_HEADERS ${UI} )

qt4_wrap_cpp( MOC_SOURCES ${HEADERS} )

set( RESOURCES Icons.qrc )

qt4_add_resources( QRC_SOURCES ${RESOURCES} )

add_executable( ${PROJECT_OUTPUT_NAME} ${SOURCES} ${MOC_SOURCES} ${QRC_SOURCES} ${UI_HEADERS} ${rc_RC})

target_link_libraries( ${PROJECT_OUTPUT_NAME}
${QT_LIBRARIES}
${QWT6_LIB}
)
