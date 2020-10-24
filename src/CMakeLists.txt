qt1_wrap_moc(MOC_FILES
    aboutwidget.h
    editdlg.h
    filefinder.h
    fileview.h
    imlibwidget.h
    kfileview.h
    kuickconfigdlg.h
    kuickshow.h
    kurlwidget.h
    logotabdialog.h
    mainwidget.h
)

add_executable(kuickshow1
    aboutwidget.cpp
    editdlg.cpp
    filefinder.cpp
    fileview.cpp
    imlibconfig.cpp
    imlibwidget.cpp
    kfileview.cpp
    kuickdata.cpp
    kuickshow.cpp
    kuickconfigdlg.cpp
    kurlwidget.cpp
    logotabdialog.cpp
    main.cpp
    mainwidget.cpp

    ${MOC_FILES}
)

target_compile_definitions(kuickshow1 PRIVATE VERSION=\"${PROJECT_VERSION}\")

target_link_libraries(kuickshow1
    ${KDE1_KDECORE}
    ${KDE1_KDEUI}
    ${KDE1_KFILE}
    ${KDE1_KFM}
    ${KDE1_KIMGIO}
    Qt::Qt1
    X11::X11
    GIF::GIF
    JPEG::JPEG
)

install(TARGETS kuickshow1 RUNTIME DESTINATION ${KDE1_BINDIR})

