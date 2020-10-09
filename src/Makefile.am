# this 10 paths are KDE specific. Use them:
# kde_htmldir       Where your docs should go to. (contains lang subdirs)
# kde_appsdir       Where your application file (.kdelnk) should go to. 
# kde_icondir       Where your icon should go to.
# kde_minidir       Where your mini icon should go to.
# kde_datadir       Where you install application data. (Use a subdir)
# kde_locale        Where translation files should go to.(contains lang subdirs)
# kde_cgidir        Where cgi-bin executables should go to.
# kde_confdir       Where config files should go to.
# kde_mimedir       Where mimetypes should go to.
# kde_toolbardir    Where general toolbar icons should go to.
# kde_wallpaperdir  Where general wallpapers should go to.

# just set the variable
APPSDIR = $(kde_appsdir)/Graphics
# set the include path for X, qt and KDE
INCLUDES= @all_includes@
# claim, which subdirectories you want to install
# SUBDIRS =

####### This part is very kuickshow specific
# you can add here more. This one gets installed 
bin_PROGRAMS = 	kuickshow

# Which sources should be compiled for kuickshow.
kuickshow_SOURCES = aboutwidget.cpp editdlg.cpp filefinder.cpp fileview.cpp \
		imlibconfig.cpp \
		imlibwidget.cpp kfileview.cpp \
		kuickdata.cpp \
		kuickshow.cpp \
		kuickconfigdlg.cpp kurlwidget.cpp \
		logotabdialog.cpp main.cpp mainwidget.cpp

kuickshow_METASOURCES = USE_AUTOMOC

# the library search path
kuickshow_LDFLAGS = @all_libraries@ @KDE_RPATH@

# the libraries to link against. Be aware of the order. First the libraries,
# that depend on the following ones.
kuickshow_LDADD  = $(LIB_IMLIB) \
	-lkfile -lkfm -lkdeui -lkdecore -lqt -lXext -lX11 $(LIBSOCKET)     

# this option you can leave out. Just, if you use "make dist", you need it
noinst_HEADERS = aboutwidget.h editdlg.h filefinder.h fileview.h imlibconfig.h \
		imlibwidget.cpp kfileview.h \
		kuickconfigdlg.h \
		kuickdata.h \
		kuickshow.h kurlwidget.h \
		logotabdialog.h mainwidget.h

# if you "make distclean", this files get removed. If you want to remove
# them while "make clean", use CLEANFILES
DISTCLEANFILES = $(BUILTSOURCES) gmon.out *.moc.cpp *.moc.o

# make messages.po. Move this one to ../po/ and "make merge" in po
messages:
	$(XGETTEXT) -C -ki18n $(kuickshow_SOURCES) && mv messages.po ../po/kuickshow.pot

# just install datas here. Use install-exec-data for scripts and etc.
# the binary itself is already installed from automake
# use mkinstalldirs, not "install -d"
# don't install a list of file. Just one file per install.
# if you have more of them, create a subdirectory with an extra Makefile 
install-data-local: 
	$(mkinstalldirs) $(APPSDIR)
	$(INSTALL_DATA) kuickshow.kdelnk $(APPSDIR)
	$(mkinstalldirs) $(kde_icondir)
	$(INSTALL_DATA) kuickshow.xpm $(kde_icondir)
	$(mkinstalldirs) $(kde_minidir)
	$(INSTALL_DATA) mini-kuickshow.xpm $(kde_minidir)/kuickshow.xpm

# remove ALL you have installed in install-data-local or install-exec-local
uninstall-local:
	-rm -f $(APPSDIR)/kuickshow.kdelnk
	-rm -f $(kde_icondir)/kuickshow.xpm
	-rm -f $(kde_minidir)/kuickshow.xpm
	-rm -rf $(kde_datadir)/kuickshow
