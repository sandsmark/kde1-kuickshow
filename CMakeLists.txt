cmake_minimum_required (VERSION 3.0)

project (kuickshow VERSION 0.2.1)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_BUILD_WITH_INSTALL_RPATH ON)

find_package(KDE1 REQUIRED)
find_package(X11 REQUIRED)
find_package(GIF REQUIRED)
find_package(JPEG REQUIRED)

include_directories (
    ${KDE1_INCLUDE_DIR}
    src
)


include(CMakePackageConfigHelpers)
include(Qt1Macros)
include(KDE1Macros)
include(KDE1InstallDirs)

option(ENABLE_SANITIZERS "Enable runtime sanitizing (for development)")
if (ENABLE_SANITIZERS)
    message("Enabling asan and ubsan")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=undefined")
endif()

if (CMAKE_COMPILER_IS_GNUCXX)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wno-write-strings")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fpermissive -std=c++98 -Wno-write-strings")
    set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -Wl,--no-undefined")
endif()


add_subdirectory(src)
install_icon(src/kuickshow.xpm)
install(FILES src/kuickshow.kdelnk DESTINATION ${KDE1_APPSDIR}/Graphics/)

install(FILES
    pics/logo.gif
    pics/eqx2.gif
    DESTINATION ${KDE1_DATADIR}/kuickshow/pics/
)

install(FILES
    etc/im_palette.pal
    DESTINATION ${KDE1_DATADIR}/kuickshow/
)

install(FILES
    #pics/toolbar/help.xpm # already in kdelibs
    pics/toolbar/ksconfig.xpm
    pics/toolbar/ksexit.xpm
    pics/toolbar/ksslide.xpm
    #pics/toolbar/reload.xpm # already in kdelibs
    pics/toolbar/topic.xpm
    DESTINATION ${KDE1_TOOLBARDIR}
)
