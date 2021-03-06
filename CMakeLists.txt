project(ktp-call-ui)

cmake_minimum_required(VERSION 2.8.12)

set(KTP_CALL_UI_VERSION "0.8.80")
set(IS_KTP_INTERNAL_MODULE TRUE)

find_package(ECM 1.3.0 REQUIRED NO_MODULE)
set(CMAKE_MODULE_PATH ${ECM_MODULE_PATH} ${ECM_KDE_MODULE_DIR})

find_package(KF5 REQUIRED COMPONENTS Config Declarative IconThemes I18n Notifications XmlGui KCMUtils)
find_package(Qt5 REQUIRED COMPONENTS Quick Qml WebKitWidgets)
find_package(KTp REQUIRED)
find_package(TelepathyQt5 REQUIRED)
find_package(TelepathyQt5Farstream REQUIRED)
find_package(KTp REQUIRED)
find_package(Qt5GStreamer REQUIRED)
find_package(PkgConfig REQUIRED)

include_directories( ${QTGSTREAMER_INCLUDES} )
add_definitions( ${QTGSTREAMER_DEFINITIONS} )

include(KDEInstallDirs)
include(KDECMakeSettings)
include(KDECompilerSettings)
include(ECMSetupVersion)
include(FeatureSummary)

kde_enable_exceptions()
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${QTGSTREAMER_FLAGS}")

configure_file(version.h.in ${CMAKE_CURRENT_BINARY_DIR}/src/version.h @ONLY)

add_subdirectory(libqtf)
add_subdirectory(libktpcall)
add_subdirectory(src)
