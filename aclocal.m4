dnl aclocal.m4 generated automatically by aclocal 1.3

dnl Copyright (C) 1994, 1995, 1996, 1997, 1998 Free Software Foundation, Inc.
dnl This Makefile.in is free software; the Free Software Foundation
dnl gives unlimited permission to copy and/or distribute it,
dnl with or without modifications, as long as this notice is preserved.

dnl This program is distributed in the hope that it will be useful,
dnl but WITHOUT ANY WARRANTY, to the extent permitted by law; without
dnl even the implied warranty of MERCHANTABILITY or FITNESS FOR A
dnl PARTICULAR PURPOSE.




AC_DEFUN(AC_FIND_FILE,
[
$3=NO
for i in $2;
do
  for j in $1;
  do
    if test -r "$i/$j"; then
      $3=$i
      break 2
    fi
  done
done
])

AC_DEFUN(AC_PATH_QT_MOC,
[
AC_PATH_PROG(MOC, moc, /usr/bin/moc,
 $QTDIR/bin:$PATH:/usr/bin:/usr/X11R6/bin:/usr/lib/qt/bin:/usr/local/qt/bin)
])

AC_DEFUN(KDE_REPLACE_ROOT,
  $1=`echo "$$1" | sed -e "s#^/#\$\{install_root\}/#"`
)

AC_DEFUN(AC_CREATE_KFSSTND,
[
AC_REQUIRE([AC_CHECK_RPATH])
AC_REQUIRE([AC_CHECK_BOOL])

if test "$1" = "default"; then

  AC_MSG_CHECKING(for KDE paths)

  if test -z "$kde_htmldir"; then
    kde_htmldir="\$(prefix)/share/doc/HTML"
  fi
  if test -z "$kde_appsdir"; then
    kde_appsdir="\$(prefix)/share/applnk"
  fi
  if test -z "$kde_icondir"; then
    kde_icondir="\$(prefix)/share/icons"
  fi
  if test -z "$kde_sounddir"; then
    kde_sounddir="\$(prefix)/share/sounds"
  fi
  if test -z "$kde_datadir"; then
    kde_datadir="\$(prefix)/share/apps"
  fi
  if test -z "$kde_locale"; then
    kde_locale="\$(prefix)/share/locale"
  fi
  if test -z "$kde_cgidir"; then
    kde_cgidir="\$(exec_prefix)/cgi-bin"
  fi
  if test -z "$kde_confdir"; then
    kde_confdir="\$(prefix)/share/config"
  fi
  if test -z "$kde_mimedir"; then
    kde_mimedir="\$(prefix)/share/mimelnk"
  fi
  if test -z "$kde_toolbardir"; then
    kde_toolbardir="\$(prefix)/share/toolbar"
  fi
  if test -z "$kde_wallpaperdir"; then
    kde_wallpaperdir="\$(prefix)/share/wallpapers"
  fi
  if test -z "$kde_bindir"; then
    kde_bindir="\$(exec_prefix)/bin"
  fi
  if test -z "$kde_partsdir"; then
    kde_partsdir="\$(exec_prefix)/parts"
  fi
  AC_MSG_RESULT(defaults)	

else 

AC_CACHE_VAL(kde_cv_all_paths,
[
AC_MSG_CHECKING([for kde headers installed])
AC_LANG_CPLUSPLUS
cat > conftest.$ac_ext <<EOF
#include <stdio.h>
#include "confdefs.h"
#include "config.h.bot"
#include <kapp.h>

int main() {
printf("kde_htmldir=\\"%s\\"\n", KApplication::kde_htmldir().data());
printf("kde_appsdir=\\"%s\\"\n", KApplication::kde_appsdir().data());
printf("kde_icondir=\\"%s\\"\n", KApplication::kde_icondir().data());
printf("kde_sounddir=\\"%s\\"\n", KApplication::kde_sounddir().data());
printf("kde_datadir=\\"%s\\"\n", KApplication::kde_datadir().data());
printf("kde_locale=\\"%s\\"\n", KApplication::kde_localedir().data());
printf("kde_cgidir=\\"%s\\"\n", KApplication::kde_cgidir().data());
printf("kde_confdir=\\"%s\\"\n", KApplication::kde_configdir().data());
printf("kde_mimedir=\\"%s\\"\n", KApplication::kde_mimedir().data());
printf("kde_toolbardir=\\"%s\\"\n", KApplication::kde_toolbardir().data());
printf("kde_wallpaperdir=\\"%s\\"\n", KApplication::kde_wallpaperdir().data());
printf("kde_bindir=\\"%s\\"\n", KApplication::kde_bindir().data());
printf("kde_partsdir=\\"%s\\"\n", KApplication::kde_partsdir().data());
return 0;
}
EOF

if test -n "$kde_libraries"; then
  KDE_TEST_RPATH="-rpath $kde_libraries"
fi

if test -n "$qt_libraries"; then
  KDE_TEST_RPATH="$KDE_TEST_RPATH -rpath $qt_libraries $KDE_EXTRA_RPATH"
fi

ac_compile='${CXX-g++} -c $CXXFLAGS $all_includes $CPPFLAGS conftest.$ac_ext'
if AC_TRY_EVAL(ac_compile); then
  AC_MSG_RESULT(yes)
else
  AC_MSG_ERROR([your system is not able to compile a small KDE application!
Check, if you installed the KDE header files correctly.])
fi

AC_MSG_CHECKING([for kde libraries installed])
ac_link='/bin/sh ./libtool --mode=link ${CXX-g++} -o conftest $CXXFLAGS $all_includes $CPPFLAGS $LDFLAGS $all_libraries conftest.$ac_ext $LIBS -lkdecore -lqt -lXext -lX11 $LIBSOCKET $KDE_TEST_RPATH 1>&5'

if AC_TRY_EVAL(ac_link) && test -s conftest; then 
  AC_MSG_RESULT(yes)
else
  AC_MSG_ERROR([your system fails at linking a small KDE application!
Check, if your compiler is installed correctly and if you have used the
same compiler to compile qt and kdelibs as you did use now])
fi

AC_MSG_CHECKING([for KDE paths])
if eval `./conftest 2>&5`; then
  AC_MSG_RESULT(done)
else
  AC_MSG_RESULT(problems)
fi

./conftest 2> /dev/null >&5 # make an echo for config.log
kde_have_all_paths=yes
AC_LANG_CPLUSPLUS

if test "$kde_have_all_paths" = "yes"; then
kde_cv_all_paths="kde_have_all_paths=\"yes\" \
	kde_htmldir=\"$kde_htmldir\" \
	kde_appsdir=\"$kde_appsdir\" \
	kde_icondir=\"$kde_icondir\" \
	kde_sounddir=\"$kde_sounddir\" \
	kde_datadir=\"$kde_datadir\" \
	kde_locale=\"$kde_locale\" \
	kde_cgidir=\"$kde_cgidir\" \
	kde_confdir=\"$kde_confdir\" \
	kde_mimedir=\"$kde_mimedir\" \
	kde_toolbardir=\"$kde_toolbardir\" \
	kde_wallpaperdir=\"$kde_wallpaperdir\" \
	kde_bindir=\"$kde_bindir\" \
	kde_partsdir=\"$kde_partsdir\""
fi
rm -fr conftest*

])

eval "$kde_cv_all_paths"

if test -z "$kde_htmldir" || test -z "$kde_appsdir" ||
   test -z "$kde_icondir" || test -z "$kde_sounddir" ||
   test -z "$kde_datadir" || test -z "$kde_locale"  ||
   test -z "$kde_cgidir"  || test -z "$kde_confdir" ||
   test -z "$kde_mimedir" || test -z "$kde_toolbardir" ||
   test -z "$kde_wallpaperdir" || test -z "$kde_bindir" ||
   test -z "$kde_partsdir" || test "$kde_have_all_paths" != "yes"; then
  kde_have_all_paths=no
  AC_MSG_ERROR([configure could not run a little KDE program to test the environment. 
Since it had compiled and linked before, it must be a strange problem on your system.
Look at config.log for details. If you are not able to fix this, please contact Stephan Kulow <coolo@kde.org>.])
fi

if test -n "$install_root"; then
  KDE_REPLACE_ROOT(kde_htmldir)
  KDE_REPLACE_ROOT(kde_appsdir)
  KDE_REPLACE_ROOT(kde_icondir)
  KDE_REPLACE_ROOT(kde_sounddir)
  KDE_REPLACE_ROOT(kde_datadir)
  KDE_REPLACE_ROOT(kde_locale)
  KDE_REPLACE_ROOT(kde_cgidir)
  KDE_REPLACE_ROOT(kde_confdir)
  KDE_REPLACE_ROOT(kde_mimedir)
  KDE_REPLACE_ROOT(kde_toolbardir)
  KDE_REPLACE_ROOT(kde_wallpaperdir)
  KDE_REPLACE_ROOT(kde_bindir)
  KDE_REPLACE_ROOT(kde_partsdir)
  AC_SUBST(install_root)
fi

fi

bindir=$kde_bindir

])

AC_DEFUN(AC_SUBST_KFSSTND,
[
AC_SUBST(kde_htmldir)
AC_SUBST(kde_appsdir)
AC_SUBST(kde_icondir)
AC_SUBST(kde_sounddir)
kde_minidir="$kde_icondir/mini"
AC_SUBST(kde_minidir)
AC_SUBST(kde_datadir)
AC_SUBST(kde_locale)
AC_SUBST(kde_cgidir)
AC_SUBST(kde_confdir)
AC_SUBST(kde_mimedir)
AC_SUBST(kde_toolbardir)
AC_SUBST(kde_wallpaperdir)
AC_SUBST(kde_bindir)
AC_SUBST(kde_partsdir)
])

AC_DEFUN(KDE_MISC_TESTS,
[
   AC_LANG_C
   dnl Checks for libraries. 
   AC_CHECK_LIB(compat, main, [LIBCOMPAT="-lcompat"]) dnl for FreeBSD
   AC_SUBST(LIBCOMPAT)
   AC_CHECK_LIB(crypt, main, [LIBCRYPT="-lcrypt"]) dnl for BSD
   AC_SUBST(LIBCRYPT)
   AC_CHECK_KSIZE_T
   AC_CHECK_LIB(dnet, dnet_ntoa, [X_EXTRA_LIBS="$X_EXTRA_LIBS -ldnet"])
   if test $ac_cv_lib_dnet_dnet_ntoa = no; then
      AC_CHECK_LIB(dnet_stub, dnet_ntoa,
        [X_EXTRA_LIBS="$X_EXTRA_LIBS -ldnet_stub"])
   fi
   AC_CHECK_FUNC(gethostbyname)
   if test $ac_cv_func_gethostbyname = no; then
     AC_CHECK_LIB(nsl, gethostbyname, X_EXTRA_LIBS="$X_EXTRA_LIBS -lnsl")
   fi
   AC_CHECK_FUNC(connect)
   if test $ac_cv_func_connect = no; then
      AC_CHECK_LIB(socket, connect, X_EXTRA_LIBS="-lsocket $X_EXTRA_LIBS", ,
        $X_EXTRA_LIBS)
   fi

   AC_CHECK_FUNC(remove)
   if test $ac_cv_func_remove = no; then
      AC_CHECK_LIB(posix, remove, X_EXTRA_LIBS="$X_EXTRA_LIBS -lposix")
   fi
 
   # BSDI BSD/OS 2.1 needs -lipc for XOpenDisplay.
   AC_CHECK_FUNC(shmat)
   if test $ac_cv_func_shmat = no; then
     AC_CHECK_LIB(ipc, shmat, X_EXTRA_LIBS="$X_EXTRA_LIBS -lipc")
   fi

   LIBSOCKET=$X_EXTRA_LIBS
   AC_SUBST(LIBSOCKET)
   AC_SUBST(X_EXTRA_LIBS)
   AC_CHECK_LIB(ucb, killpg, [LIBUCB="-lucb"]) dnl for Solaris2.4
   AC_SUBST(LIBUCB)

   case $host in  dnl this *is* LynxOS specific
   *-*-lynxos* )
        AC_MSG_CHECKING([LynxOS header file wrappers])
        [CFLAGS="$CFLAGS -D__NO_INCLUDE_WARN__"]
        AC_MSG_RESULT(disabled)
        AC_CHECK_LIB(bsd, gethostbyname, [LIBSOCKET="-lbsd"]) dnl for LynxOS
         ;;
    esac

])

AC_DEFUN(K_PATH_X,
[
AC_MSG_CHECKING(for X)
AC_CACHE_VAL(ac_cv_have_x,
[# One or both of the vars are not set, and there is no cached value.
ac_x_includes=NO ac_x_libraries=NO
AC_PATH_X_DIRECT
AC_PATH_X_XMKMF
if test "$ac_x_includes" = NO || test "$ac_x_libraries" = NO; then
  AC_MSG_ERROR([Can't find X includes. Please check your installation and add the correct paths!])
else
  # Record where we found X for the cache.
  ac_cv_have_x="have_x=yes \
                ac_x_includes=$ac_x_includes ac_x_libraries=$ac_x_libraries"
fi])dnl
eval "$ac_cv_have_x"
 
if test "$have_x" != yes; then
  AC_MSG_RESULT($have_x)
  no_x=yes
else
  # If each of the values was on the command line, it overrides each guess.
  test "x$x_includes" = xNONE && x_includes=$ac_x_includes
  test "x$x_libraries" = xNONE && x_libraries=$ac_x_libraries
  # Update the cache value to reflect the command line values.
  ac_cv_have_x="have_x=yes \
                ac_x_includes=$x_includes ac_x_libraries=$x_libraries"
  AC_MSG_RESULT([libraries $x_libraries, headers $x_includes])
fi

if test -z "$x_includes" || test "x$x_includes" = xNONE; then
  X_INCLUDES=""
  x_includes="."; dnl better than nothing :-
 else
  X_INCLUDES="-I$x_includes"
fi

if test -z "$x_libraries" || test "x$x_libraries" = xNONE; then
  X_LDFLAGS=""
  x_libraries="/usr/lib"; dnl better than nothing :-
  all_libraries=""
 else
  X_LDFLAGS="-L$x_libraries"
  all_libraries=$X_LDFLAGS
  
fi

AC_SUBST(X_INCLUDES)
AC_SUBST(X_LDFLAGS)
AC_SUBST(x_libraries)
AC_SUBST(x_includes)
all_includes=$X_INCLUDES
])

AC_DEFUN(KDE_PRINT_QT_PROGRAM,
[
AC_LANG_CPLUSPLUS
cat > conftest.$ac_ext <<EOF
#include "confdefs.h"
#include <qmovie.h>
int main() {
  QMovie m;
  m.setSpeed(20);
  return 0;
}
EOF
])

AC_DEFUN(KDE_CHECK_QT_DIRECT,
[
AC_MSG_CHECKING([if Qt compiles without flags])
AC_CACHE_VAL(kde_cv_qt_direct,
[
ac_LD_LIBRARY_PATH_safe=$LD_LIBRARY_PATH
ac_LIBRARY_PATH="$LIBRARY_PATH"
ac_cxxflags_safe="$CXXFLAGS"
ac_ldflags_safe="$LDFLAGS"
ac_libs_safe="$LIBS"

CXXFLAGS="$CXXFLAGS -I$qt_includes"
LDFLAGS="$X_LDFLAGS"
LIBS="-lqt -lXext -lX11 $LIBSOCKET"
LD_LIBRARY_PATH=
export LD_LIBRARY_PATH
LIBRARY_PATH=
export LIBRARY_PATH

KDE_PRINT_QT_PROGRAM

if AC_TRY_EVAL(ac_link) && test -s conftest; then
  kde_cv_qt_direct="yes"
else
  kde_cv_qt_direct="no"
  echo "configure: failed program was:" >&AC_FD_CC
  cat conftest.$ac_ext >&AC_FD_CC
fi
rm -f conftest*
CXXFLAGS="$ac_cxxflags_safe"
LDFLAGS="$ac_ldflags_safe"
LIBS="$ac_libs_safe"

LD_LIBRARY_PATH="$ac_LD_LIBRARY_PATH_safe"
export LD_LIBRARY_PATH
LIBRARY_PATH="$ac_LIBRARY_PATH"
export LIBRARY_PATH
])

if test "$kde_cv_qt_direct" = "yes"; then
  AC_MSG_RESULT(yes)
  $1
else
  AC_MSG_RESULT(no)
  $2
fi
])

AC_DEFUN(AC_PATH_QT_1_3,
[
AC_REQUIRE([K_PATH_X])

AC_MSG_CHECKING([for QT])
ac_qt_includes=NO ac_qt_libraries=NO
qt_libraries=""
qt_includes=""
AC_ARG_WITH(qt-dir,
    [  --with-qt-dir           where the root of qt is installed ],
    [  ac_qt_includes="$withval"/include
       ac_qt_libraries="$withval"/lib
    ])

AC_ARG_WITH(qt-includes,
    [  --with-qt-includes      where the qt includes are. ],
    [  
       ac_qt_includes="$withval"
    ])
    
kde_qt_libs_given=no

AC_ARG_WITH(qt-libraries,
    [  --with-qt-libraries     where the qt library is installed.],
    [  ac_qt_libraries="$withval"
       kde_qt_libs_given=yes
    ])

if test "$ac_qt_includes" = NO || test "$ac_qt_libraries" = NO; then

AC_CACHE_VAL(ac_cv_have_qt,
[#try to guess qt locations

qt_incdirs="$ac_qt_includes /usr/lib/qt/include /usr/local/qt/include /usr/include/qt /usr/include /usr/X11R6/include/X11/qt $x_includes $QTINC"
test -n "$QTDIR" && qt_incdirs="$QTDIR/include $QTDIR $qt_incdirs"
AC_FIND_FILE(qmovie.h, $qt_incdirs, qt_incdir)
ac_qt_includes="$qt_incdir"

if test ! "$ac_qt_libraries" = "NO"; then
  qt_libdirs="$ac_qt_libraries"
fi

qt_libdirs="$qt_libdirs /usr/lib/qt/lib /usr/X11R6/lib /usr/lib /usr/local/qt/lib /usr/lib/qt $x_libraries $QTLIB"
test -n "$QTDIR" && qt_libdirs="$QTDIR/lib $QTDIR $qt_libdirs"

test=NONE
qt_libdir=NONE
for dir in $qt_libdirs; do
  try="ls -1 $dir/libqt*"
  if test=`eval $try 2> /dev/null`; then qt_libdir=$dir; break; else echo "tried $dir" >&AC_FD_CC ; fi
done

dnl AC_FIND_FILE(libqt.so libqt.so.1.30 libqt.so.1.31 libqt.so.1 libqt.a libqt.sl, $qt_libdirs, qt_libdir)
ac_qt_libraries="$qt_libdir"

ac_cxxflags_safe="$CXXFLAGS"
ac_ldflags_safe="$LDFLAGS"
ac_libs_safe="$LIBS"

CXXFLAGS="$CXXFLAGS -I$qt_incdir"
LDFLAGS="-L$qt_libdir $X_LDFLAGS"
LIBS="$LIBS -lqt -lXext -lX11 $LIBSOCKET"

KDE_PRINT_QT_PROGRAM

if AC_TRY_EVAL(ac_link) && test -s conftest; then
  rm -f conftest*
else
  echo "configure: failed program was:" >&AC_FD_CC
  cat conftest.$ac_ext >&AC_FD_CC
  ac_qt_libraries="NO"
fi
rm -f conftest*
CXXFLAGS="$ac_cxxflags_safe"
LDFLAGS="$ac_ldflags_safe"
LIBS="$ac_libs_safe"

if test "$ac_qt_includes" = NO || test "$ac_qt_libraries" = NO; then
  ac_cv_have_qt="have_qt=no"
  ac_qt_notfound=""
  if test "$ac_qt_includes" = NO; then
    if test "$ac_qt_libraries" = NO; then
      ac_qt_notfound="(headers and libraries)";
    else
      ac_qt_notfound="(headers)";
    fi
  else
    ac_qt_notfound="(libraries)";
  fi

  AC_MSG_ERROR([QT-1.3 $ac_qt_notfound not found. Please check your installation! ]);
else
  have_qt="yes"
fi
])
else
  have_qt="yes"
fi

eval "$ac_cv_have_qt"

if test "$have_qt" != yes; then
  AC_MSG_RESULT([$have_qt]);
else
  ac_cv_have_qt="have_qt=yes \
    ac_qt_includes=$ac_qt_includes ac_qt_libraries=$ac_qt_libraries"
  AC_MSG_RESULT([libraries $ac_qt_libraries, headers $ac_qt_includes])
  
  qt_libraries="$ac_qt_libraries"
  qt_includes="$ac_qt_includes"
fi

if test ! "$kde_qt_libs_given" = "yes"; then
KDE_CHECK_QT_DIRECT(qt_libraries= ,[])
fi

AC_SUBST(qt_libraries)
AC_SUBST(qt_includes)

if test "$qt_includes" = "$x_includes" || test -z "$qt_includes"; then
 QT_INCLUDES="";
else
 QT_INCLUDES="-I$qt_includes"
 all_includes="$QT_INCLUDES $all_includes"
fi

if test "$qt_libraries" = "$x_libraries" || test -z "$qt_libraries"; then
 QT_LDFLAGS=""
else
 QT_LDFLAGS="-L$qt_libraries"
 all_libraries="$QT_LDFLAGS $all_libraries"
fi

AC_SUBST(QT_INCLUDES)
AC_SUBST(QT_LDFLAGS)
AC_PATH_QT_MOC
])

AC_DEFUN(AC_PATH_QT,
[
AC_PATH_QT_1_3
])

AC_DEFUN(AC_BASE_PATH_KDE,
[
AC_REQUIRE([KDE_MISC_TESTS])
AC_REQUIRE([AC_PATH_QT])dnl
AC_MSG_CHECKING([for KDE])

if test "${prefix}" != NONE; then
  kde_includes=${prefix}/include
  ac_kde_includes=$prefix/include

  if test "${exec_prefix}" != NONE; then
    kde_libraries=${exec_prefix}/lib
    ac_kde_libraries=$exec_prefix/lib
  else
    kde_libraries=${prefix}/lib
    ac_kde_libraries=$prefix/lib
  fi
else
  ac_kde_includes=
  ac_kde_libraries=
  kde_libraries=""
  kde_includes=""
fi

AC_CACHE_VAL(ac_cv_have_kde,
[#try to guess kde locations

if test -z "$1"; then

kde_incdirs="$ac_kde_includes /usr/lib/kde/include /usr/local/kde/include /usr/kde/include /usr/include/kde /usr/include /opt/kde/include $x_includes $qt_includes"
test -n "$KDEDIR" && kde_incdirs="$KDEDIR/include $KDEDIR $kde_incdirs"
AC_FIND_FILE(ksock.h, $kde_incdirs, kde_incdir)
ac_kde_includes="$kde_incdir"

if test -n "$ac_kde_includes" && test ! -r "$ac_kde_includes/ksock.h"; then
  AC_MSG_ERROR([
in the prefix, you've chosen, are no kde headers installed. This will fail.
So, check this please and use another prefix!])
fi

kde_libdirs="$ac_kde_libraries /usr/lib/kde/lib /usr/local/kde/lib /usr/kde/lib /usr/lib/kde /usr/lib /usr/X11R6/lib /opt/kde/lib /usr/X11R6/kde/lib"
test -n "$KDEDIR" && kde_libdirs="$KDEDIR/lib $KDEDIR $kde_libdirs"
AC_FIND_FILE(libkdecore.la, $kde_libdirs, kde_libdir)

if test -n "$ac_kde_libraries" && test ! -r "$ac_kde_libraries/libkdecore.la"; then
AC_MSG_ERROR([
in the prefix, you've chosen, are no kde libraries installed. This will fail.
So, check this please and use another prefix!])
fi
ac_kde_libraries="$kde_libdir"

if test "$ac_kde_includes" = NO || test "$ac_kde_libraries" = NO; then
  ac_cv_have_kde="have_kde=no"
else
  ac_cv_have_kde="have_kde=yes \
    ac_kde_includes=$ac_kde_includes ac_kde_libraries=$ac_kde_libraries"
fi

else dnl test -z $1 
  
  ac_cv_have_kde="have_kde=no"

fi
])dnl

eval "$ac_cv_have_kde"

if test "$have_kde" != "yes"; then
 if test "${prefix}" = NONE; then
  ac_kde_prefix="$ac_default_prefix"
 else
  ac_kde_prefix="$prefix"
 fi
 if test "$exec_prefix" = NONE; then
  ac_kde_exec_prefix="$ac_kde_prefix"
  AC_MSG_RESULT([will be installed in $ac_kde_prefix])
 else
  ac_kde_exec_prefix="$exec_prefix"
  AC_MSG_RESULT([will be installed in $ac_kde_prefix and $ac_kde_exec_prefix])
 fi

 kde_libraries="${ac_kde_exec_prefix}/lib"
 kde_includes=${ac_kde_prefix}/include

else
  ac_cv_have_kde="have_kde=yes \
    ac_kde_includes=$ac_kde_includes ac_kde_libraries=$ac_kde_libraries"
  AC_MSG_RESULT([libraries $ac_kde_libraries, headers $ac_kde_includes])
  
  kde_libraries="$ac_kde_libraries"
  kde_includes="$ac_kde_includes"
fi
AC_SUBST(kde_libraries)
AC_SUBST(kde_includes)

if test "$kde_includes" = "$x_includes" || test "$kde_includes" = "$qt_includes" ; then
 KDE_INCLUDES=""
else
 KDE_INCLUDES="-I$kde_includes"
 all_includes="$KDE_INCLUDES $all_includes"
fi

if test "$kde_libraries" = "$x_libraries" || test "$kde_libraries" = "$qt_libraries" ; then
 KDE_LDFLAGS=""
else
 KDE_LDFLAGS="-L$kde_libraries"
 all_libraries="$KDE_LDFLAGS $all_libraries"
fi

AC_SUBST(KDE_LDFLAGS)
AC_SUBST(KDE_INCLUDES)

AC_MSG_CHECKING(for extra includes)
AC_ARG_WITH(extra-includes, [  --with-extra-includes   adds non standard include paths], 
  kde_use_extra_includes="$withval",
  kde_use_extra_includes=NONE
)
if test -n "$kde_use_extra_includes" && \
   test "$kde_use_extra_includes" != "NONE"; then

   ac_save_ifs=$IFS
   IFS=':'
   for dir in $kde_use_extra_includes; do
     all_includes="$all_includes -I$dir"
   done
   IFS=$ac_save_ifs
   kde_use_extra_includes="added"
else
   kde_use_extra_includes="no"
fi

AC_MSG_RESULT($kde_use_extra_includes)

AC_MSG_CHECKING(for extra libs)
AC_ARG_WITH(extra-libs, [  --with-extra-libs       adds non standard library paths], 
  kde_use_extra_libs=$withval,
  kde_use_extra_libs=NONE
)
if test -n "$kde_use_extra_libs" && \
   test "$kde_use_extra_libs" != "NONE"; then

   ac_save_ifs=$IFS
   IFS=':'
   for dir in $kde_use_extra_libs; do
     all_libraries="$all_libraries -L$dir"
     KDE_EXTRA_RPATH="$KDE_EXTRA_RPATH -rpath $dir"
   done
   IFS=$ac_save_ifs
   kde_use_extra_libs="added"
else
   kde_use_extra_libs="no"
fi

AC_MSG_RESULT($kde_use_extra_libs)

AC_SUBST(all_includes)
AC_SUBST(all_libraries)

])

AC_DEFUN(AC_PATH_KDE,
[
  AC_BASE_PATH_KDE
  AC_ARG_ENABLE(path-check, [  --disable-path-check    don't try to find out, where to install],
  [
  if test "$enableval" = "no"; 
    then ac_use_path_checking="default"
    else ac_use_path_checking=""
  fi
  ], [ac_use_path_checking=""]
  )

  AC_ARG_WITH(install-root, [  --with-install-root     the root, where to install to [default=/]],
  [
  if test "$withval" = "no";
    then kde_install_root="";
    else kde_install_root=$withval;
  fi
  ], [kde_install_root=""]
  )
  
  if test -n "$kde_install_root"; then
     install_root="$kde_install_root"
  else
     install_root=
  fi

  AC_CREATE_KFSSTND($ac_use_path_checking)

 AC_SUBST_KFSSTND
])

dnl slightly changed version of AC_CHECK_FUNC(setenv)
AC_DEFUN(AC_CHECK_SETENV,
[AC_MSG_CHECKING([for setenv])
AC_CACHE_VAL(ac_cv_func_setenv,
[AC_LANG_C
AC_TRY_LINK(
dnl Don't include <ctype.h> because on OSF/1 3.0 it includes <sys/types.h>
dnl which includes <sys/select.h> which contains a prototype for
dnl select.  Similarly for bzero.
[#include <assert.h>
]ifelse(AC_LANG, CPLUSPLUS, [#ifdef __cplusplus
extern "C"
#endif
])dnl
[/* We use char because int might match the return type of a gcc2
    builtin and then its argument prototype would still apply.  */
#include <stdlib.h>
], [
/* The GNU C library defines this for functions which it implements
    to always fail with ENOSYS.  Some functions are actually named
    something starting with __ and the normal name is an alias.  */
#if defined (__stub_$1) || defined (__stub___$1)
choke me
#else
setenv("TEST", "alle", 1);
#endif
], eval "ac_cv_func_setenv=yes", eval "ac_cv_func_setenv=no")])

if test "$ac_cv_func_setenv" = "yes"; then
  AC_MSG_RESULT(yes)
  AC_DEFINE_UNQUOTED(HAVE_FUNC_SETENV)
else
  AC_MSG_RESULT(no)
fi
])

AC_DEFUN(AC_CHECK_GETDOMAINNAME,
[
AC_LANG_CPLUSPLUS
save_CXXFLAGS="$CXXFLAGS"
if test "$GCC" = "yes"; then
CXXFLAGS="$CXXFLAGS -pedantic-errors"
fi
AC_MSG_CHECKING(for getdomainname)
AC_CACHE_VAL(ac_cv_func_getdomainname,
[
AC_TRY_COMPILE([
#include <stdlib.h>
#include <unistd.h>
],
[
char buffer[200];
getdomainname(buffer, 200);
],
ac_cv_func_getdomainname=yes,
ac_cv_func_getdomainname=no)
])
AC_MSG_RESULT($ac_cv_func_getdomainname)
if eval "test \"`echo `$ac_cv_func_getdomainname\" = yes"; then
  AC_DEFINE(HAVE_GETDOMAINNAME)
fi
CXXFLAGS="$save_CXXFLAGS"
])

AC_DEFUN(AC_CHECK_GETHOSTNAME,
[
AC_LANG_CPLUSPLUS
save_CXXFLAGS="$CXXFLAGS"
if test "$GCC" = "yes"; then
CXXFLAGS="$CXXFLAGS -pedantic-errors"
fi

AC_MSG_CHECKING([for gethostname])
AC_CACHE_VAL(ac_cv_func_gethostname,
[
AC_TRY_COMPILE([
#include <stdlib.h>
#include <unistd.h>
],
[
char buffer[200];
gethostname(buffer, 200);
],
ac_cv_func_gethostname=yes,
ac_cv_func_gethostname=no)
])
AC_MSG_RESULT($ac_cv_func_gethostname)
if eval "test \"`echo `$ac_cv_func_gethostname\" = yes"; then
  AC_DEFINE(HAVE_GETHOSTNAME)
fi
CXXFLAGS="$save_CXXFLAGS"
])

AC_DEFUN(AC_CHECK_USLEEP,
[
AC_LANG_CPLUSPLUS

AC_MSG_CHECKING([for usleep])
AC_CACHE_VAL(ac_cv_func_usleep,
[
ac_libs_safe="$LIBS"
LIBS="$LIBS $LIBUCB"
AC_TRY_LINK([
#include <stdlib.h>
#include <unistd.h>
],
[
usleep(200);
],
ac_cv_func_usleep=yes,
ac_cv_func_usleep=no)
])
AC_MSG_RESULT($ac_cv_func_usleep)
if eval "test \"`echo `$ac_cv_func_usleep\" = yes"; then
  AC_DEFINE(HAVE_USLEEP)
fi
LIBS="$ac_libs_safe"
])

AC_DEFUN(AC_FIND_GIF,
   [AC_MSG_CHECKING([for giflib])
AC_CACHE_VAL(ac_cv_lib_gif,
[ac_save_LIBS="$LIBS"
LIBS="$all_libraries -lgif -lX11 $LIBSOCKET"
AC_TRY_LINK(dnl
[
#ifdef __cplusplus
extern "C" {
#endif
int GifLastError(void);
#ifdef __cplusplus
}
#endif
/* We use char because int might match the return type of a gcc2
    builtin and then its argument prototype would still apply.  */
],
            [return GifLastError();],
            eval "ac_cv_lib_gif=yes",
            eval "ac_cv_lib_gif=no")
LIBS="$ac_save_LIBS"
])dnl
if eval "test \"`echo $ac_cv_lib_gif`\" = yes"; then
  AC_MSG_RESULT(yes)
  AC_DEFINE_UNQUOTED(HAVE_LIBGIF)
else
  AC_MSG_ERROR(You need giflib23. Please install the kdesupport package)
fi
])

AC_DEFUN(AC_FIND_JPEG,
   [AC_MSG_CHECKING([for jpeglib])
AC_CACHE_VAL(ac_cv_lib_jpeg,
[ac_save_LIBS="$LIBS"
LIBS="$all_libraries -ljpeg -lm"
AC_TRY_LINK(
[/* Override any gcc2 internal prototype to avoid an error.  */
struct jpeg_decompress_struct;
typedef struct jpeg_decompress_struct * j_decompress_ptr;
typedef int size_t;
#ifdef __cplusplus
extern "C" {
#endif
    void jpeg_CreateDecompress(j_decompress_ptr cinfo,
                                    int version, size_t structsize);
#ifdef __cplusplus
}
#endif
/* We use char because int might match the return type of a gcc2
    builtin and then its argument prototype would still apply.  */
],
            [jpeg_CreateDecompress(0L, 0, 0);],
            eval "ac_cv_lib_jpeg=-ljpeg",
            eval "ac_cv_lib_jpeg=no")
LIBS="$ac_save_LIBS"

dnl what to do, if the normal way fails:
if eval "test \"`echo $ac_cv_lib_jpeg`\" = no"; then
	if test -f "$kde_libraries/libjpeg.so"; then
	   test -f ./libjpegkde.so || $LN_S $kde_libraries/libjpeg.so ./libjpegkde.so
	   ac_cv_lib_jpeg="-L\${topdir} -ljpegkde"
	else if test -f "$kde_libraries/libjpeg.sl"; then
	   test -f ./libjpegkde.sl ||$LN_S $kde_libraries/libjpeg.sl ./libjpegkde.sl
	   ac_cv_lib_jpeg="-L\${topdir} -ljpegkde"	
	else if test -f "$kde_libraries/libjpeg.a"; then
	   test -f ./libjpegkde.a || $LN_S $kde_libraries/libjpeg.a ./libjpegkde.a
	   ac_cv_lib_jpeg="-L\${topdir} -ljpegkde"
        else
	  AC_MSG_ERROR([
You need jpeglib6a. Please install the kdesupport package.
If you have already installed kdesupport, you may have an
old libjpeg somewhere. 
In this case copy $KDEDIR/lib/libjpeg* to /usr/lib.
])
	fi
      fi
   fi
fi
])dnl
if eval "test ! \"`echo $ac_cv_lib_jpeg`\" = no"; then
  LIBJPEG="$ac_cv_lib_jpeg"
  AC_SUBST(LIBJPEG)
  AC_MSG_RESULT($ac_cv_lib_jpeg)
  AC_DEFINE_UNQUOTED(HAVE_LIBJPEG)
fi
])

AC_DEFUN(AC_FIND_ZLIB,
[
AC_MSG_CHECKING([for libz])
AC_CACHE_VAL(ac_cv_lib_z,
[ac_save_LIBS="$LIBS"
LIBS="$all_libraries -lz $LIBSOCKET"
AC_TRY_LINK(dnl
[
#include<zlib.h>
],
            [return (zlibVersion() == ZLIB_VERSION); ],
            eval "ac_cv_lib_z='-lz'",
            eval "ac_cv_lib_z=no")
LIBS="$ac_save_LIBS"
])dnl
if eval "test ! \"`echo $ac_cv_lib_z`\" = no"; then
dnl  AC_DEFINE_UNQUOTED(HAVE_LIBZ)
  LIBZ="$ac_cv_lib_z"
  AC_SUBST(LIBZ)
  AC_MSG_RESULT($ac_cv_lib_z)
else
  AC_MSG_RESULT(no)
  LIBZ=""
  AC_SUBST(LIBZ)
fi
])

AC_DEFUN(AC_FIND_TIFF,
[
AC_MSG_CHECKING([for libtiff])

AC_CACHE_VAL(ac_cv_lib_tiff,
[ac_save_LIBS="$LIBS"
LIBS="$all_libraries -ltiff -lX11 $LIBSOCKET $all_includes"
AC_LANG_CPLUSPLUS
AC_TRY_LINK(dnl
[
#include<tiffio.h>
],
            [return (TIFFOpen( "", "r") == 0); ],
            eval "ac_cv_lib_tiff='-ltiff'",
            eval "ac_cv_lib_tiff=no")
LIBS="$ac_save_LIBS"
])dnl
if eval "test ! \"`echo $ac_cv_lib_tiff`\" = no"; then
  AC_DEFINE_UNQUOTED(HAVE_LIBTIFF)
  LIBTIFF="$ac_cv_lib_tiff"
  AC_SUBST(LIBTIFF)
  AC_MSG_RESULT($ac_cv_lib_tiff)
else
  AC_MSG_RESULT(no)
  LIBTIFF=""
  AC_SUBST(LIBTIFF)
fi
])

AC_DEFUN(AC_FIND_PNG,
[
AC_REQUIRE([AC_FIND_ZLIB])
AC_MSG_CHECKING([for libpng])
AC_CACHE_VAL(ac_cv_lib_png,
[ac_save_LIBS="$LIBS"
LIBS="$all_libraries -lpng $LIBZ -lX11 $LIBSOCKET $all_includes"
AC_LANG_CPLUSPLUS
AC_TRY_LINK(dnl
    [
    #include<png.h>
    ],
    [
    png_structp png_ptr = png_create_read_struct(  // image ptr
                PNG_LIBPNG_VER_STRING, 0, 0, 0 );
    return( png_ptr != 0 );
    ],
    eval "ac_cv_lib_png='-lpng $LIBZ'",
    eval "ac_cv_lib_png=no")
    LIBS="$ac_save_LIBS"
])dnl
if eval "test ! \"`echo $ac_cv_lib_png`\" = no"; then
  AC_DEFINE_UNQUOTED(HAVE_LIBPNG)
  LIBPNG="$ac_cv_lib_png"
  AC_SUBST(LIBPNG)
  AC_MSG_RESULT($ac_cv_lib_png)
else
  AC_MSG_RESULT(no)
  LIBPNG=""
  AC_SUBST(LIBPNG)
fi
])

AC_DEFUN(AC_CHECK_BOOL,
[
	AC_MSG_CHECKING([for bool])
        AC_CACHE_VAL(ac_cv_have_bool,
        [
		AC_LANG_CPLUSPLUS
          	AC_TRY_COMPILE([],
                 [bool aBool = true;],
                 [ac_cv_have_bool="yes"],
                 [ac_cv_have_bool="no"])
        ]) dnl end AC_CHECK_VAL
        AC_MSG_RESULT($ac_cv_have_bool)
        if test "$ac_cv_have_bool" = "yes"; then
        	AC_DEFINE(HAVE_BOOL) 
        fi 
])

AC_DEFUN(AC_CHECK_GNU_EXTENSIONS,
[
AC_MSG_CHECKING(if you need GNU extensions)
AC_CACHE_VAL(ac_cv_gnu_extensions,
[
cat > conftest.c << EOF
#include <features.h>

#ifdef __GNU_LIBRARY__
yes
#endif
EOF

if (eval "$ac_cpp conftest.c") 2>&5 |
  egrep "yes" >/dev/null 2>&1; then
  rm -rf conftest*
  ac_cv_gnu_extensions=yes
else
  ac_cv_gnu_extensions=no
fi
])

AC_MSG_RESULT($ac_cv_gnu_extensions)
if test "$ac_cv_gnu_extensions" = "yes"; then
  AC_DEFINE_UNQUOTED(_GNU_SOURCE)
fi
])

AC_DEFUN(AC_CHECK_COMPILERS,
[
  dnl this is somehow a fat lie, but prevents other macros from double checking
  AC_PROVIDE([AC_PROG_CC])
  AC_PROVIDE([AC_PROG_CPP])
  AC_ARG_ENABLE(debug,[  --enable-debug 	  creates debugging code [default=no]],
  [ 
   if test $enableval = "no"; dnl 
     then ac_use_debug_code="no"
     else ac_use_debug_code="yes"
   fi
  ], [ac_use_debug_code="no"])

dnl this was AC_PROG_CC. I had to include it manualy, since I had to patch it
  AC_MSG_CHECKING(for a C-Compiler)
  dnl if there is one, print out. if not, don't matter
  AC_MSG_RESULT($CC) 
 
  if test -z "$CC"; then AC_CHECK_PROG(CC, gcc, gcc) fi
  if test -z "$CC"; then AC_CHECK_PROG(CC, cc, cc, , , /usr/ucb/cc) fi
  if test -z "$CC"; then AC_CHECK_PROG(CC, xlc, xlc) fi
  test -z "$CC" && AC_MSG_ERROR([no acceptable cc found in \$PATH])

  AC_PROG_CC_WORKS
  AC_PROG_CC_GNU

  if test $ac_cv_prog_gcc = yes; then
    GCC=yes
  else
    GCC=
  fi

  if test -z "$CFLAGS"; then
    if test "$ac_use_debug_code" = "yes"; then
      AC_PROG_CC_G
      if test $ac_cv_prog_cc_g = yes; then
        CFLAGS="-g"
      fi
    else
      if test "$GCC" = "yes"; then
        CFLAGS="-O2"
      else
        CFLAGS=""
      fi
    fi

    if test "$GCC" = "yes"; then
     CFLAGS="$CFLAGS -Wall"
    fi

  fi

  if test -z "$LDFLAGS" && test "$ac_use_debug_code" = "no" && test "$GCC" = "yes"; then
     LDFLAGS="-s"
  fi


dnl this is AC_PROG_CPP. I had to include it here, since autoconf checks
dnl dependecies between AC_PROG_CPP and AC_PROG_CC (or is it automake?)

  AC_MSG_CHECKING(how to run the C preprocessor)
  # On Suns, sometimes $CPP names a directory.
  if test -n "$CPP" && test -d "$CPP"; then
    CPP=
  fi
  if test -z "$CPP"; then
  AC_CACHE_VAL(ac_cv_prog_CPP,
  [  # This must be in double quotes, not single quotes, because CPP may get
    # substituted into the Makefile and "${CC-cc}" will confuse make.
    CPP="${CC-cc} -E"
    # On the NeXT, cc -E runs the code through the compiler's parser,
    # not just through cpp.
    dnl Use a header file that comes with gcc, so configuring glibc    
    dnl with a fresh cross-compiler works.
    AC_TRY_CPP([#include <assert.h>
    Syntax Error], ,
    CPP="${CC-cc} -E -traditional-cpp"
    AC_TRY_CPP([#include <assert.h>
    Syntax Error], , CPP=/lib/cpp))
    ac_cv_prog_CPP="$CPP"])dnl
    CPP="$ac_cv_prog_CPP"
  else
    ac_cv_prog_CPP="$CPP"
  fi
  AC_MSG_RESULT($CPP)
  AC_SUBST(CPP)dnl


  AC_MSG_CHECKING(for a C++-Compiler)
  dnl if there is one, print out. if not, don't matter
  AC_MSG_RESULT($CXX) 
 
  if test -z "$CXX"; then AC_CHECK_PROG(CXX, g++, g++) fi
  if test -z "$CXX"; then AC_CHECK_PROG(CXX, CC, CC) fi
  if test -z "$CXX"; then AC_CHECK_PROG(CXX, xlC, xlC) fi
  if test -z "$CXX"; then AC_CHECK_PROG(CXX, DCC, DCC) fi
  test -z "$CXX" && AC_MSG_ERROR([no acceptable C++-compiler found in \$PATH])

  AC_PROG_CXX_WORKS
  AC_PROG_CXX_GNU

  if test $ac_cv_prog_gxx = yes; then
    GXX=yes
  else
    AC_MSG_CHECKING(whether we are using SPARC CC)
    GXX=
    cat > conftest.C << EOF
#ifdef __SUNPRO_CC
   yes;
#endif
EOF

    ac_try="$CXX -E conftest.C"
    if { (eval echo configure:__online__: \"$ac_try\") 1>&5; (eval $ac_try) 2>&5; } | egrep yes >/dev/null 2>&1; then
      ac_cv_prog_CC=yes
    else
      ac_cv_prog_CC=no
    fi
    AC_MSG_RESULT($ac_cv_prog_CC)
  fi

  if test -z "$CXXFLAGS"; then 
    if test "$ac_use_debug_code" = "yes"; then
      AC_PROG_CXX_G
      if test $ac_cv_prog_cxx_g = yes; then
        CXXFLAGS="-g"
      fi
      if test "$ac_cv_prog_CC" = "yes"; then
        CXXFLAGS="$CXXFLAGS -pto"
      fi
    else
      if test "$GXX" = "yes"; then
         CXXFLAGS="-O2"
      else
         if test "$ac_cv_prog_CC" = "yes"; then
            CXXFLAGS="-pto -O2"
         else
            CXXFLAGS=""
         fi
      fi
    fi

    if test "$GXX" = "yes"; then
       CXXFLAGS="$CXXFLAGS -Wall"
    fi
  fi  

])

dnl just a wrapper to clean up configure.in
AC_DEFUN(KDE_PROG_LIBTOOL,
[
AC_REQUIRE([AM_ENABLE_SHARED])
AC_REQUIRE([AM_ENABLE_STATIC])
dnl libtool is only for C, so I must force him
dnl to find the correct flags for C++
ac_save_cc=$CC
ac_save_cflags="$CFLAGS"
CC=$CXX
CFLAGS="$CXXFLAGS"
AM_PROG_LIBTOOL dnl for libraries
CC=$ac_save_cc
CFLAGS="$ac_save_cflags"
])

AC_DEFUN(KDE_DO_IT_ALL,
[
AC_CANONICAL_SYSTEM 
AC_ARG_PROGRAM 
AM_INIT_AUTOMAKE($1, $2)
AM_DISABLE_LIBRARIES
AC_PREFIX_DEFAULT(${KDEDIR:-/usr/local/kde})
AC_CHECK_COMPILERS
KDE_PROG_LIBTOOL
AM_KDE_WITH_NLS
AC_PATH_KDE
])

AC_DEFUN(AC_CHECK_RPATH,
[
AC_MSG_CHECKING(for rpath)
AC_ARG_ENABLE(rpath,
      [  --disable-rpath         do not use the rpath feature of ld],
      USE_RPATH=$enableval, USE_RPATH=yes)
if test -z "$KDE_RPATH" && test "$USE_RPATH" = "yes"; then

  KDE_RPATH="-rpath \$(kde_libraries)"

  if test -n "$qt_libraries"; then
    KDE_RPATH="$KDE_RPATH -rpath \$(qt_libraries)"
  fi
  dnl $x_libraries is set to /usr/lib in case
  if test -n "$X_LDFLAGS"; then 
    KDE_RPATH="$KDE_RPATH -rpath \$(x_libraries)"
  fi
  if test -n "$KDE_EXTRA_RPATH"; then
    KDE_RPATH="$KDE_RPATH \$(KDE_EXTRA_RPATH)"
  fi
fi 
AC_SUBST(KDE_EXTRA_RPATH)
AC_SUBST(KDE_RPATH)
AC_MSG_RESULT($USE_RPATH)
])

dnl Check for the type of the third argument of getsockname
AC_DEFUN(AC_CHECK_KSIZE_T,
[AC_MSG_CHECKING(for the third argument of getsockname)  
AC_LANG_CPLUSPLUS
AC_CACHE_VAL(ac_cv_ksize_t,
[AC_TRY_COMPILE([
#include <sys/types.h>
#include <sys/socket.h>
],[
socklen_t a=0; 
getsockname(0,(struct sockaddr*)0, &a);
],
ac_cv_ksize_t=socklen_t,
ac_cv_ksize_t=)
if test -z "$ac_cv_ksize_t"; then
ac_safe_cxxflags="$CXXFLAGS"
if test "$GCC" = "yes"; then
  CXXFLAGS="-Werror $CXXFLAGS"
fi
AC_TRY_COMPILE([
#include <sys/types.h>
#include <sys/socket.h>
],[
int a=0; 
getsockname(0,(struct sockaddr*)0, &a);
],
ac_cv_ksize_t=int,
ac_cv_ksize_t=size_t)
CXXFLAGS="$ac_safe_cxxflags"
fi
])

if test -z "$ac_cv_ksize_t"; then
  ac_cv_ksize_t=int
fi

AC_MSG_RESULT($ac_cv_ksize_t)
AC_DEFINE_UNQUOTED(ksize_t, $ac_cv_ksize_t)

])


dnl This is a merge of some macros out of the gettext aclocal.m4
dnl since we don't need anything, I took the things we need
AC_DEFUN(AM_KDE_WITH_NLS,
  [AC_MSG_CHECKING([whether NLS is requested])
    AC_LANG_CPLUSPLUS
    dnl Default is enabled NLS
    AC_ARG_ENABLE(nls,
      [  --disable-nls           do not use Native Language Support],
      USE_NLS=$enableval, USE_NLS=yes)
    AC_MSG_RESULT($USE_NLS)
    AC_SUBST(USE_NLS)

    dnl If we use NLS figure out what method
    if test "$USE_NLS" = "yes"; then
      AC_DEFINE(ENABLE_NLS)

      AM_PATH_PROG_WITH_TEST_KDE(MSGFMT, msgfmt, 
         [test -n "`$ac_dir/$ac_word --version 2>&1 | grep 'GNU gettext'`"], msgfmt)
      AC_PATH_PROG(GMSGFMT, gmsgfmt, $MSGFMT)

      if test -z "`$MSGFMT 2>&1 | grep 'GNU gettext'`"; then
        AC_MSG_RESULT([found msgfmt program is not GNU msgfmt; ignore it])
        msgfmt=":"
      fi

      AM_PATH_PROG_WITH_TEST_KDE(XGETTEXT, xgettext,
	[test -z "`$ac_dir/$ac_word -h 2>&1 | grep '(HELP)'`"], :)
      AC_SUBST(MSGFMT)

      dnl Test whether we really found GNU xgettext.
      if test "$XGETTEXT" != ":"; then
	dnl If it is no GNU xgettext we define it as : so that the
	dnl Makefiles still can work.
	if $XGETTEXT --omit-header /dev/null 2> /dev/null; then
	  : ;
	else
	  AC_MSG_RESULT(
	    [found xgettext programs is not GNU xgettext; ignore it])
	  XGETTEXT=":"
	fi
      fi
     AC_SUBST(XGETTEXT)
    fi

  ])

# Search path for a program which passes the given test.
# Ulrich Drepper <drepper@cygnus.com>, 1996.

# serial 1
# Stephan Kulow: I appended a _KDE against name conflicts

dnl AM_PATH_PROG_WITH_TEST_KDE(VARIABLE, PROG-TO-CHECK-FOR,
dnl   TEST-PERFORMED-ON-FOUND_PROGRAM [, VALUE-IF-NOT-FOUND [, PATH]])
AC_DEFUN(AM_PATH_PROG_WITH_TEST_KDE,
[# Extract the first word of "$2", so it can be a program name with args.
set dummy $2; ac_word=[$]2
AC_MSG_CHECKING([for $ac_word])
AC_CACHE_VAL(ac_cv_path_$1,
[case "[$]$1" in
  /*)
  ac_cv_path_$1="[$]$1" # Let the user override the test with a path.
  ;;
  *)
  IFS="${IFS= 	}"; ac_save_ifs="$IFS"; IFS="${IFS}:"
  for ac_dir in ifelse([$5], , $PATH, [$5]); do
    test -z "$ac_dir" && ac_dir=.
    if test -f $ac_dir/$ac_word; then
      if [$3]; then
	ac_cv_path_$1="$ac_dir/$ac_word"
	break
      fi
    fi
  done
  IFS="$ac_save_ifs"
dnl If no 4th arg is given, leave the cache variable unset,
dnl so AC_PATH_PROGS will keep looking.
ifelse([$4], , , [  test -z "[$]ac_cv_path_$1" && ac_cv_path_$1="$4"
])dnl
  ;;
esac])dnl
$1="$ac_cv_path_$1"
if test -n "[$]$1"; then
  AC_MSG_RESULT([$]$1)
else
  AC_MSG_RESULT(no)
fi
AC_SUBST($1)dnl
])


# Check whether LC_MESSAGES is available in <locale.h>.
# Ulrich Drepper <drepper@cygnus.com>, 1995.
 
# serial 1
 
AC_DEFUN(AM_LC_MESSAGES,
  [if test $ac_cv_header_locale_h = yes; then
    AC_CACHE_CHECK([for LC_MESSAGES], am_cv_val_LC_MESSAGES,
      [AC_TRY_LINK([#include <locale.h>], [return LC_MESSAGES],
       am_cv_val_LC_MESSAGES=yes, am_cv_val_LC_MESSAGES=no)])
    if test $am_cv_val_LC_MESSAGES = yes; then
      AC_DEFINE(HAVE_LC_MESSAGES)
    fi
  fi])
 
dnl From Jim Meyering.
dnl FIXME: migrate into libit.

AC_DEFUN(AM_FUNC_OBSTACK,
[AC_CACHE_CHECK([for obstacks], am_cv_func_obstack,
 [AC_TRY_LINK([#include "obstack.h"],
	      [struct obstack *mem;obstack_free(mem,(char *) 0)],
	      am_cv_func_obstack=yes,
	      am_cv_func_obstack=no)])
 if test $am_cv_func_obstack = yes; then
   AC_DEFINE(HAVE_OBSTACK)
 else
   LIBOBJS="$LIBOBJS obstack.o"
 fi
])

dnl From Jim Meyering.  Use this if you use the GNU error.[ch].
dnl FIXME: Migrate into libit

AC_DEFUN(AM_FUNC_ERROR_AT_LINE,
[AC_CACHE_CHECK([for error_at_line], am_cv_lib_error_at_line,
 [AC_TRY_LINK([],[error_at_line(0, 0, "", 0, "");],
              am_cv_lib_error_at_line=yes,
	      am_cv_lib_error_at_line=no)])
 if test $am_cv_lib_error_at_line = no; then
   LIBOBJS="$LIBOBJS error.o"
 fi
 AC_SUBST(LIBOBJS)dnl
])

# Macro to add for using GNU gettext.
# Ulrich Drepper <drepper@cygnus.com>, 1995.

# serial 1
# Stephan Kulow: I put a KDE in it to avoid name conflicts

AC_DEFUN(AM_KDE_GNU_GETTEXT,
  [AC_REQUIRE([AC_PROG_MAKE_SET])dnl
   AC_REQUIRE([AC_PROG_RANLIB])dnl
   AC_REQUIRE([AC_HEADER_STDC])dnl
   AC_REQUIRE([AC_C_INLINE])dnl
   AC_REQUIRE([AC_TYPE_OFF_T])dnl
   AC_REQUIRE([AC_TYPE_SIZE_T])dnl
   AC_REQUIRE([AC_FUNC_ALLOCA])dnl
   AC_REQUIRE([AC_FUNC_MMAP])dnl
   AC_REQUIRE([AM_KDE_WITH_NLS])dnl
   AC_CHECK_HEADERS([argz.h limits.h locale.h nl_types.h malloc.h string.h \
unistd.h values.h alloca.h])
   AC_CHECK_FUNCS([getcwd munmap putenv setenv setlocale strchr strcasecmp \
__argz_count __argz_stringify __argz_next stpcpy])

   AM_LC_MESSAGES

   if test "x$CATOBJEXT" != "x"; then
     if test "x$ALL_LINGUAS" = "x"; then
       LINGUAS=
     else
       AC_MSG_CHECKING(for catalogs to be installed)
       NEW_LINGUAS=
       for lang in ${LINGUAS=$ALL_LINGUAS}; do
         case "$ALL_LINGUAS" in
          *$lang*) NEW_LINGUAS="$NEW_LINGUAS $lang" ;;
         esac
       done
       LINGUAS=$NEW_LINGUAS
       AC_MSG_RESULT($LINGUAS)
     fi

     dnl Construct list of names of catalog files to be constructed.
     if test -n "$LINGUAS"; then
       for lang in $LINGUAS; do CATALOGS="$CATALOGS $lang$CATOBJEXT"; done
     fi
   fi

  ])

AC_DEFUN(AC_HAVE_XPM,
 [AC_REQUIRE_CPP()dnl

 test -z "$XPM_LDFLAGS" && XPM_LDFLAGS=
 test -z "$XPM_INCLUDE" && XPM_INCLUDE=

 AC_ARG_WITH(xpm, [  --without-xpm           disable color pixmap XPM tests],
	xpm_test=$withval, xpm_test="yes")
 if test "x$xpm_test" = xno; then
   ac_cv_have_xpm=no
 else
   AC_MSG_CHECKING(for XPM)
   AC_CACHE_VAL(ac_cv_have_xpm,
   [
    AC_LANG_C
    ac_save_ldflags="$LDFLAGS"
    ac_save_cflags="$CFLAGS"
    LDFLAGS="$LDFLAGS $XPM_LDFLAGS $all_libraries -lXpm -lX11 -lXext $LIBSOCKET"
    CFLAGS="$CFLAGS $X_INCLUDES"
    test ! -z "$XPM_INCLUDE" && CFLAGS="-I$XPM_INCLUDE $CFLAGS"
    AC_TRY_LINK([#include <X11/xpm.h>],[],
	ac_cv_have_xpm="yes",ac_cv_have_xpm="no")
    LDFLAGS="$ac_save_ldflags"
    CFLAGS="$ac_save_cflags"
   ])dnl
 
  if test "$ac_cv_have_xpm" = no; then
    AC_MSG_RESULT(no)
    XPM_LDFLAGS=""
    XPMINC=""
    $2
  else
    AC_DEFINE(HAVE_XPM)
    if test "$XPM_LDFLAGS" = ""; then
       XPMLIB="-lXpm"
    else
       XPMLIB="-L$XPM_LDFLAGS -lXpm"
    fi
    if test "$XPM_INCLUDE" = ""; then
       XPMINC=""
    else
       XPMINC="-I$XPM_INCLUDE"
    fi
    AC_MSG_RESULT(yes)
    $1
  fi
 fi
 AC_SUBST(XPMINC)
 AC_SUBST(XPMLIB)
]) 

AC_DEFUN(AC_HAVE_GL,
 [AC_REQUIRE_CPP()dnl

 test -z "$GL_LDFLAGS" && GL_LDFLAGS=
 test -z "$GL_INCLUDE" && GL_INCLUDE=

 AC_ARG_WITH(gl, [  --without-gl            disable 3D GL modes],
	gl_test=$withval, gl_test="yes")
 if test "x$gl_test" = xno; then
   ac_cv_have_gl=no
 else
   AC_MSG_CHECKING(for GL)
   AC_CACHE_VAL(ac_cv_have_gl,
   [
    AC_LANG_C
    ac_save_ldflags="$LDFLAGS"
    ac_save_cflags="$CFLAGS"
    LDFLAGS="$LDFLAGS $GL_LDFLAGS $all_libraries -lMesaGL -lMesaGLU -lX11 -lXext -lm $LIBSOCKET"
    CFLAGS="$CFLAGS $X_INCLUDES"
    test ! -z "$GL_INCLUDE" && CFLAGS="-I$GL_INCLUDE $CFLAGS"
    AC_TRY_LINK([],[],
	ac_cv_have_gl="yes",ac_cv_have_gl="no")
    LDFLAGS="$ac_save_ldflags"
    CFLAGS="$ac_save_cflags"
   ])dnl
 
  if test "$ac_cv_have_gl" = no; then
    AC_MSG_RESULT(no)
    GL_LDFLAGS=""
    GLINC=""
    $2
  else
    AC_DEFINE(HAVE_GL)
    if test "$GL_LDFLAGS" = ""; then
       GLLIB="-lMesaGL -lMesaGLU"
    else
       GLLIB="-L$GL_LDFLAGS -lMesaGL -lMesaGLU"
    fi
    if test "$GL_INCLUDE" = ""; then
       GLINC=""
    else
       GLINC="-I$GL_INCLUDE"
    fi
    AC_MSG_RESULT(yes)
    $1
  fi
 fi
 AC_SUBST(GLINC)
 AC_SUBST(GLLIB)
]) 

 dnl PAM pam
 
 dnl Should test for PAM (Pluggable Authentication Modules)
 AC_DEFUN(AC_PATH_PAM_DIRECT,
 [
 test -z "$pam_direct_test_library" && pam_direct_test_library=pam
 test -z "$pam_direct_test_include" && pam_direct_test_include=security/pam_appl.h
 
   for ac_dir in               \
                               \
     /usr/local/include        \
     /usr/include              \
     /usr/unsupported/include  \
     /opt/include              \
     /usr/pam/include          \
     /usr/local/pam/include    \
     /usr/lib/pam/include      \
 			      \
     $extra_include            \
     ; \
   do
     if test -r "$ac_dir/$pam_direct_test_include"; then
       no_pam= ac_pam_includes=$ac_dir
       break
     fi
   done
 
 # First see if replacing the include by lib works.
 for ac_dir in `echo "$ac_pam_includes" | sed s/include/lib/` \
                           \
     /lib                  \
     /usr/lib              \
     /usr/local/lib        \
     /usr/unsupported/lib  \
     /lib/security         \
     /usr/security/lib     \
     $extra_lib            \
     ; \
 do
   for ac_extension in a so sl; do
     if test -r $ac_dir/lib${pam_direct_test_library}.$ac_extension; then
       no_pam= ac_pam_libraries=$ac_dir
       break 2
     fi
   done
 done
])

AC_DEFUN(AC_PATH_PAM,
 [AC_REQUIRE_CPP()dnl

  kde_save_LIBS="$LIBS"
  LIBS="$LIBS -ldl"
  AC_CHECK_LIB(pam_misc, main, [PAM_MISC_LIB="-lpam_misc"])
  LIBS="$kde_save_LIBS"

 AC_MSG_CHECKING(for PAM)
 AC_ARG_WITH(pam, [  --with-pam              disable Pluggable Authentication Modules],
  [
    if test "x$withval" = "xyes"; then
      no_pam=
    else
      no_pam=yes
    fi
  ], no_pam=yes
 )

 if test ! "$no_pam" = yes; then

 AC_CACHE_VAL(ac_cv_path_pam,
 [
 ac_pam_includes=NONE
 ac_pam_libraries=NONE
 if test -z "$pam_libraries"; then
   pam_libraries=NONE
 fi
 if test -z "$pam_includes"; then
   pam_includes=NONE
 fi

 AC_PATH_PAM_DIRECT
 
 test "x$pam_includes" = xNONE && pam_includes=$ac_pam_includes
 test "x$pam_libraries" = xNONE && pam_libraries=$ac_pam_libraries
 
 if test ! "x$pam_includes" = xNONE && test ! "x$pam_libraries" = xNONE; then
   ac_pam_libs="-lpam $PAM_MISC_LIB -ldl"
   ac_cv_path_pam="no_pam= ac_pam_includes=$ac_pam_includes ac_pam_libraries=$ac_pam_libraries ac_pam_libs=\"$ac_pam_libs\""
 else
   ac_cv_path_pam="no_pam=yes"
 fi
 ])

 eval "$ac_cv_path_pam"
 
 fi

 if test "$no_pam" = yes; then
   AC_MSG_RESULT(no)
 else
   AC_DEFINE(HAVE_PAM)
   PAMLIBS="$ac_pam_libs"
   test "x$pam_includes" = xNONE && pam_includes=$ac_pam_includes
   test "x$pam_libraries" = xNONE && pam_libraries=$ac_pam_libraries
   AC_MSG_RESULT([libraries $pam_libraries, headers $pam_includes])
 fi
 
 if test "x$pam_libraries" != x && test "x$pam_libraries" != xNONE ; then
     PAMLIBPATHS="-L$pam_libraries"
 fi
 if test "x$pam_includes" != x && test "x$pam_includes" != xNONE ; then
     PAMINC="-I$pam_includes"
 fi
 
 AC_SUBST(PAMINC)
 AC_SUBST(PAMLIBS)
 AC_SUBST(PAMLIBPATHS)

]) 

AC_DEFUN(KDE_CHECK_LIBDL,
[
AC_CHECK_LIB(dl, dlopen, [
LIBDL="-ldl"
ac_cv_have_dlfcn=yes
])

AC_CHECK_LIB(dld, shl_unload, [
LIBDL="-ldld"
ac_cv_have_shload=yes
])

AC_SUBST(LIBDL)
])

AC_DEFUN(KDE_CHECK_DLOPEN,
[
KDE_CHECK_LIBDL
AC_CHECK_HEADERS(dlfcn.h dl.h)
if test "$ac_cv_header_dlfcn_h" = "no"; then
  ac_cv_have_dlfcn=no
fi

if test "$ac_cv_header_dl_h" = "no"; then
  ac_cv_have_shload=no
fi

enable_dlopen=no
AC_ARG_ENABLE(dlopen,
[  --disable-dlopen        link staticly [default=no]] ,
[if test "$enableval" = yes; then
  enable_dlopen=yes
fi],
enable_dlopen=yes)

# override the user's opinion, if we know it better ;)
if test "$ac_cv_have_dlfcn" = "no" && test "$ac_cv_have_shload" = "no"; then
  enable_dlopen=no
fi

if test "$ac_cv_have_dlfcn" = "yes"; then
  AC_DEFINE_UNQUOTED(HAVE_DLFCN)
fi

if test "$ac_cv_have_shload" = "yes"; then
  AC_DEFINE_UNQUOTED(HAVE_SHLOAD)
fi

if test "$enable_dlopen" = no ; then
  test -n "$1" && eval $1
else
  test -n "$2" && eval $2
fi

])

AC_DEFUN(KDE_CHECK_DYNAMIC_LOADING,
[
KDE_CHECK_DLOPEN(libtool_enable_shared=no, libtool_enable_static=no)
KDE_PROG_LIBTOOL
AC_MSG_CHECKING([dynamic loading])
eval "`egrep '^build_libtool_libs=' libtool`"
if test "$build_libtool_libs" = "yes" && test "$enable_dlopen" = "yes"; then
  dynamic_loading=yes
  AC_DEFINE_UNQUOTED(HAVE_DYNAMIC_LOADING)
else
  dynamic_loading=no
fi
AC_MSG_RESULT($dynamic_loading)
if test "$dynamic_loading" = "yes"; then
  $1
else
  $2
fi
])

AC_DEFUN(KDE_ADD_INCLUDES,
[
if test -z "$1"; then 
  test_include="Pix.h"
else
  test_include="$1"
fi

AC_MSG_CHECKING([for libg++ ($test_include)])

AC_CACHE_VAL(kde_cv_libgpp_includes,
[
kde_cv_libgpp_includes=no

   for ac_dir in               \
                               \
     /usr/include/g++          \
     /usr/include              \
     /usr/unsupported/include  \
     /opt/include              \
     $extra_include            \
     ; \
   do
     if test -r "$ac_dir/$test_include"; then
       kde_cv_libgpp_includes=$ac_dir
       break
     fi
   done
])

AC_MSG_RESULT($kde_cv_libgpp_includes)
if test "$kde_cv_libgpp_includes" != "no"; then
  all_includes="-I$kde_cv_libgpp_includes $all_includes"
fi
])
])


AC_DEFUN(KDE_CHECK_MICO,
[
AC_REQUIRE([KDE_CHECK_LIBDL])
AC_MSG_CHECKING(for MICO)
AC_ARG_WITH(micodir,
  [  --with-micodir=micodir  where mico is installed ],
  kde_micodir=$withval,
  kde_micodir=/usr/local
)
AC_MSG_RESULT($kde_micodir)
if test ! -r  $kde_micodir/include/CORBA.h; then
  AC_MSG_ERROR([No CORBA.h found, specify another micodir])
fi

MICO_INCLUDES=-I$kde_micodir/include
AC_SUBST(MICO_INCLUDES)
MICO_LDFLAGS=-L$kde_micodir/lib
AC_SUBST(MICO_LDFLAGS)

AC_MSG_CHECKING([for MICO version])
AC_CACHE_VAL(kde_cv_mico_version,
[
AC_LANG_C
cat >conftest.$ac_ext <<EOF
#include <stdio.h>
#include <mico/version.h>
int main() { 
    
   printf("MICO_VERSION=%s\n",MICO_VERSION); 
   return (0); 
}
EOF
ac_compile='${CC-gcc} $CFLAGS $MICO_INCLUDES conftest.$ac_ext -o conftest'
if AC_TRY_EVAL(ac_compile); then
  if eval `./conftest 2>&5`; then
    kde_cv_mico_version=$MICO_VERSION
  else
    AC_MSG_ERROR([your system is not able to execute a small application to
    find MICO version! Check $kde_micodir/include/mico/version.h])
  fi 
else
  AC_MSG_ERROR([your system is not able to compile a small application to
  find MICO version! Check $kde_micodir/include/mico/version.h])
fi
])

dnl installed MICO version
mico_v_maj=`echo $kde_cv_mico_version | sed -e 's/^\(.*\)\..*\..*$/\1/'`
mico_v_mid=`echo $kde_cv_mico_version | sed -e 's/^.*\.\(.*\)\..*$/\1/'`
mico_v_min=`echo $kde_cv_mico_version | sed -e 's/^.*\..*\.\(.*\)$/\1/'`

dnl required MICO version
req_v_maj=`echo $1 | sed -e 's/^\(.*\)\..*\..*$/\1/'`
req_v_mid=`echo $1 | sed -e 's/^.*\.\(.*\)\..*$/\1/'`
req_v_min=`echo $1 | sed -e 's/^.*\..*\.\(.*\)$/\1/'` 

if test "$mico_v_maj" -lt "$req_v_maj" || \
   ( test "$mico_v_maj" -eq "$req_v_maj" && \
        test "$mico_v_mid" -lt "$req_v_mid" ) || \
   ( test "$mico_v_mid" -eq "$req_v_mid" && \
        test "$mico_v_min" -lt "$req_v_min" )

then
  AC_MSG_ERROR([found MICO version $kde_cv_mico_version but version $1 \
at least is required. You should upgrade MICO.])
else
  AC_MSG_RESULT([$kde_cv_mico_version (minimum version $1, ok)])
fi

LIBMICO="-lmico$kde_cv_mico_version $LIBDL"
AC_SUBST(LIBMICO)
IDL=$kde_micodir/bin/idl
AC_SUBST(IDL)
])


AC_DEFUN(KDE_CHECK_MINI_STL,
[
AC_REQUIRE([KDE_CHECK_MICO])

AC_MSG_CHECKING(if we use mico's mini-STL)
AC_CACHE_VAL(kde_cv_have_mini_stl,
[
AC_LANG_CPLUSPLUS
kde_save_cxxflags="$CXXFLAGS"
CXXFLAGS="$CXXFLAGS $MICO_INCLUDES"
AC_TRY_COMPILE(
[
#include <mico/config.h>
],
[
#ifdef HAVE_MINI_STL
#error "nothing"
#endif
],
kde_cv_have_mini_stl=no,
kde_cv_have_mini_stl=yes)
CXXFLAGS="$kde_save_cxxflags"
])


AC_MSG_RESULT($kde_cv_have_mini_stl)
if test "$kde_cv_have_mini_stl" = "yes"; then
  AC_DEFINE_UNQUOTED(HAVE_MINI_STL)
fi
])

])


AC_DEFUN(KDE_CHECK_LIBPTHREAD,
[
AC_CHECK_LIB(pthread, main, [LIBPTHREAD="-lpthread"], LIBPTHREAD= )
AC_SUBST(LIBPTHREAD)
])

AC_DEFUN(KDE_TRY_LINK_PYTHON,
[
AC_CACHE_VAL(kde_cv_try_link_python_$1,
[
kde_save_cxxflags="$CXXFLAGS"
CXXFLAGS="$CXXFLAGS $PYTHONINC"
kde_save_libs="$LIBS"
LIBS="$LIBS $LIBPYTHON $2 $LIBDL"
kde_save_ldflags="$LDFLAGS"
LDFLAGS="$LDFLAGS $PYTHONLIB"

AC_TRY_LINK(
[
#include <Python.h>
],[
	PySys_SetArgv(1, 0);
],
	[kde_cv_try_link_python_$1=yes],
	[kde_cv_try_link_python_$1=no]
)
CXXFLAGS="$kde_save_cxxflags"
LIBS="$kde_save_libs"
LDFLAGS="$kde_save_ldflags"
])

if test "$kde_cv_try_link_python_$1" = "yes"; then
  $3
else
  $4
fi

])

AC_DEFUN(KDE_CHECK_PYTHON,
[
AC_REQUIRE([KDE_CHECK_LIBDL])
AC_REQUIRE([KDE_CHECK_LIBPTHREAD])
if test -z "$1"; then 
  version="1.5"
else
  version="$1"
fi

AC_MSG_CHECKING([for Python$version])

AC_ARG_WITH(pythondir, 
[  --with-pythondir=pythondir   use python installed in pythondir ],
[
  ac_python_dir=$withval
], ac_python_dir=/usr/local
)

python_incdirs="$ac_python_dir/include/python$version /usr/include/python$version /usr/local/include/python$version /usr/local/include"
AC_FIND_FILE(Python.h, $python_incdirs, python_incdir)
if test ! -r $python_incdir/Python.h; then
  AC_MSG_ERROR(Python.h not found.)
fi

PYTHONINC=-I$python_incdir

python_libdirs="$ac_python_dir/lib/python$version/config /usr/lib/python$version/config /usr/local/python$version/config"
AC_FIND_FILE(libpython$version.a, $python_libdirs, python_libdir)
if test ! -r $python_libdir/libpython$version.a; then
  AC_MSG_ERROR(libpython$version.a not found.)
fi

PYTHONLIB=-L$python_libdir
LIBPYTHON=-lpython$version

AC_MSG_RESULT(header $python_incdir library $python_libdir)

dnl Note: this test is very weak
AC_MSG_CHECKING(if an Python application links)
KDE_TRY_LINK_PYTHON(normal, "", AC_MSG_RESULT(yes),
 [
    AC_MSG_RESULT(no)
    AC_MSG_CHECKING(if Python depends on -lpthread)
    KDE_TRY_LINK_PYTHON(pthread, "$LIBPTHREAD",
    [  
       AC_MSG_RESULT(yes)
       LIBPYTHON="$LIBPYTHON $LIBPTHREAD $LIBDL"
    ],
    [
       AC_MSG_RESULT(no)
       AC_MSG_WARN([it seems, Python depends on another library. 
Pleae use "make LIBPTYHON='-lpyhon$version -lotherlib'" to fix this
and contact the authors to let them know about this problem])
    ])
 ]) 

AC_SUBST(PYTHONINC)
AC_SUBST(PYTHONLIB)
AC_SUBST(LIBPYTHON)

])


AC_DEFUN(KDE_CHECK_STL_SGI,
[
    AC_MSG_CHECKING([if STL implementation is SGI like])
    AC_CACHE_VAL(kde_cv_stl_type_sgi,
    [
      AC_TRY_COMPILE([
#include <string>
],[
int main()
{
  string astring="Hallo Welt.";
  astring.erase(, 6); // now astring is "Welt"
  return 0;
};
], kde_cv_stl_type_sgi=yes,
   kde_cv_stl_type_sgi=no)
])

   AC_MSG_RESULT($kde_cv_stl_type_sgi)

   if test "$kde_cv_stl_type_sgi" = "yes"; then
	AC_DEFINE_UNQUOTED(HAVE_SGI_STL) 
   fi
])

AC_DEFUN(KDE_CHECK_STL_HP,
[
    AC_MSG_CHECKING([if STL implementation is HP like])
    AC_CACHE_VAL(kde_cv_stl_type_hp,
    [
      AC_TRY_COMPILE([
#include <string>
],[
int main()
{
  string astring="Hello World";
  astring.remove(0, 6); // now astring is "World"
  return 0;
};
], kde_cv_stl_type_hp=yes,
   kde_cv_stl_type_hp=no)
])
   AC_MSG_RESULT($kde_cv_stl_type_hp)

   if test "$kde_cv_stl_type_hp" = "yes"; then
	AC_DEFINE_UNQUOTED(HAVE_HP_STL) 
   fi
])

AC_DEFUN(KDE_CHECK_STL,
[
    KDE_CHECK_STL_SGI
    
    if test "$kde_cv_stl_type_sgi" = "no"; then
       KDE_CHECK_STL_HP

       if test "$kde_cv_stl_type_hp" = "no"; then
         AC_MSG_ERROR("no known STL type found")
       fi
    fi

])

# serial 24 AM_PROG_LIBTOOL
AC_DEFUN(AM_PROG_LIBTOOL,
[AC_REQUIRE([AM_ENABLE_SHARED])dnl
AC_REQUIRE([AM_ENABLE_STATIC])dnl
AC_REQUIRE([AC_CANONICAL_HOST])dnl
AC_REQUIRE([AC_PROG_RANLIB])dnl
AC_REQUIRE([AC_PROG_CC])dnl
AC_REQUIRE([AM_PROG_LD])dnl
AC_REQUIRE([AM_PROG_NM])dnl
AC_REQUIRE([AC_PROG_LN_S])dnl
dnl
# Always use our own libtool.
LIBTOOL='$(SHELL) $(top_builddir)/libtool'
AC_SUBST(LIBTOOL)dnl

# Check for any special flags to pass to ltconfig.
libtool_flags=
test "$enable_shared" = no && libtool_flags="$libtool_flags --disable-shared"
test "$enable_static" = no && libtool_flags="$libtool_flags --disable-static"
test "$silent" = yes && libtool_flags="$libtool_flags --silent"
test "$ac_cv_prog_gcc" = yes && libtool_flags="$libtool_flags --with-gcc"
test "$ac_cv_prog_gnu_ld" = yes && libtool_flags="$libtool_flags --with-gnu-ld"

# Some flags need to be propagated to the compiler or linker for good
# libtool support.
case "$host" in
*-*-irix6*)
  # Find out which ABI we are using.
  echo '[#]line __oline__ "configure"' > conftest.$ac_ext
  if AC_TRY_EVAL(ac_compile); then
    case "`/usr/bin/file conftest.o`" in
    *32-bit*)
      LD="${LD-ld} -32"
      ;;
    *N32*)
      LD="${LD-ld} -n32"
      ;;
    *64-bit*)
      LD="${LD-ld} -64"
      ;;
    esac
  fi
  rm -rf conftest*
  ;;

*-*-sco3.2v5*)
  # On SCO OpenServer 5, we need -belf to get full-featured binaries.
  CFLAGS="$CFLAGS -belf"
  ;;
esac

# Actually configure libtool.  ac_aux_dir is where install-sh is found.
CC="$CC" CFLAGS="$CFLAGS" CPPFLAGS="$CPPFLAGS" \
LD="$LD" NM="$NM" RANLIB="$RANLIB" LN_S="$LN_S" \
${CONFIG_SHELL-/bin/sh} $ac_aux_dir/ltconfig \
$libtool_flags --no-verify $ac_aux_dir/ltmain.sh $host \
|| AC_MSG_ERROR([libtool configure failed])
])

# AM_ENABLE_SHARED - implement the --enable-shared flag
# Usage: AM_ENABLE_SHARED[(DEFAULT)]
#   Where DEFAULT is either `yes' or `no'.  If omitted, it defaults to
#   `yes'.
AC_DEFUN(AM_ENABLE_SHARED_EX,
[define([AM_ENABLE_SHARED_DEFAULT], ifelse($1, no, no, yes))dnl
AC_PROVIDE(AM_ENABLE_SHARED)
AC_ARG_ENABLE(shared,
changequote(<<, >>)dnl
<<  --enable-shared         build shared libraries [default=>>AM_ENABLE_SHARED_DEFAULT]
changequote([, ])dnl
[  --enable-shared=PKGS    only build shared libraries if the current package
                          appears as an element in the PKGS list],
[p=${PACKAGE-default}
case "$enableval" in
yes) enable_shared=yes ;;
no) enable_shared=no ;;
*)
  enable_shared=no
  # Look at the argument we got.  We use all the common list separators.
  IFS="${IFS= 	}"; ac_save_ifs="$IFS"; IFS="${IFS}:,"
  for pkg in $enableval; do
    if test "X$pkg" = "X$p"; then
      enable_shared=yes
    fi
  done
  IFS="$ac_save_ifs"
  ;;
esac],
enable_shared=AM_ENABLE_SHARED_DEFAULT)dnl
])

AC_DEFUN(AM_ENABLE_SHARED,
[define([AM_ENABLE_SHARED_DEFAULT], ifelse($1, no, no, yes))dnl
AC_ARG_ENABLE(shared,
changequote(<<, >>)dnl
<<  --enable-shared         build shared libraries [default=>>AM_ENABLE_SHARED_DEFAULT],
changequote([, ])dnl
[
if test "$enableval" = no; then
  enable_shared=no
else
  enable_shared=yes
fi
],
enable_shared=AM_ENABLE_SHARED_DEFAULT)dnl
])


# AM_DISABLE_SHARED - set the default shared flag to --disable-shared
AC_DEFUN(AM_DISABLE_SHARED,
[AM_ENABLE_SHARED(no)])

# AM_DISABLE_STATIC - set the default static flag to --disable-static
AC_DEFUN(AM_DISABLE_STATIC,
[AM_ENABLE_STATIC(no)])

# AM_ENABLE_STATIC - implement the --enable-static flag
# Usage: AM_ENABLE_STATIC[(DEFAULT)]
#   Where DEFAULT is either `yes' or `no'.  If omitted, it defaults to
#   `yes'.
AC_DEFUN(AM_ENABLE_STATIC_EX,
[define([AM_ENABLE_STATIC_DEFAULT], ifelse($1, no, no, yes))dnl
AC_PROVIDE(AM_ENABLE_STATIC)
AC_ARG_ENABLE(static,
changequote(<<, >>)dnl
<<  --enable-static         build static libraries [default=>>AM_ENABLE_STATIC_DEFAULT]
changequote([, ])dnl
[  --enable-static=PKGS    only build shared libraries if the current package
                          appears as an element in the PKGS list],
[p=${PACKAGE-default}
case "$enableval" in
yes) enable_static=yes ;;
no) enable_static=no ;;
*)
  enable_static=no
  # Look at the argument we got.  We use all the common list separators.
  IFS="${IFS= 	}"; ac_save_ifs="$IFS"; IFS="${IFS}:,"
  for pkg in $enableval; do
    if test "X$pkg" = "X$p"; then
      enable_static=yes
    fi
  done
  IFS="$ac_save_ifs"
  ;;
esac],
enable_static=AM_ENABLE_STATIC_DEFAULT)dnl
])

AC_DEFUN(AM_ENABLE_STATIC,
[define([AM_ENABLE_STATIC_DEFAULT], ifelse($1, no, no, yes))dnl
AC_ARG_ENABLE(static,
changequote(<<, >>)dnl
<<  --enable-static         build static libraries [default=>>AM_ENABLE_STATIC_DEFAULT],
changequote([, ])dnl
[if test "$enableval" = no; then
  enable_static=no
else
  enable_static=yes
fi],
enable_static=AM_ENABLE_STATIC_DEFAULT)dnl
])

AC_DEFUN(AM_DISABLE_LIBRARIES,
[
AC_PROVIDE([AM_ENABLE_STATIC])
AC_PROVIDE([AM_ENABLE_SHARED])
enable_static=no
enable_shared=no
])

# AM_PROG_LD - find the path to the GNU or non-GNU linker
AC_DEFUN(AM_PROG_LD,
[AC_ARG_WITH(gnu-ld,
[  --with-gnu-ld           assume the C compiler uses GNU ld [default=no]],
test "$withval" = no || with_gnu_ld=yes, with_gnu_ld=no)
AC_REQUIRE([AC_PROG_CC])
ac_prog=ld
if test "$ac_cv_prog_gcc" = yes; then
  # Check if gcc -print-prog-name=ld gives a path.
  AC_MSG_CHECKING([for ld used by GCC])
  ac_prog=`($CC -print-prog-name=ld) 2>&5`
  case "$ac_prog" in
  # Accept absolute paths.
  /* | [A-Za-z]:\\*)
    test -z "$LD" && LD="$ac_prog"
    ;;
  "")
    # If it fails, then pretend we aren't using GCC.
    ac_prog=ld
    ;;
  *)
    # If it is relative, then search for the first ld in PATH.
    with_gnu_ld=unknown
    ;;
  esac
elif test "$with_gnu_ld" = yes; then
  AC_MSG_CHECKING([for GNU ld])
else
  AC_MSG_CHECKING([for non-GNU ld])
fi
AC_CACHE_VAL(ac_cv_path_LD,
[if test -z "$LD"; then
  IFS="${IFS= 	}"; ac_save_ifs="$IFS"; IFS="${IFS}:"
  for ac_dir in $PATH; do
    test -z "$ac_dir" && ac_dir=.
    if test -f "$ac_dir/$ac_prog"; then
      ac_cv_path_LD="$ac_dir/$ac_prog"
      # Check to see if the program is GNU ld.  I'd rather use --version,
      # but apparently some GNU ld's only accept -v.
      # Break only if it was the GNU/non-GNU ld that we prefer.
      if "$ac_cv_path_LD" -v 2>&1 < /dev/null | egrep '(GNU|with BFD)' > /dev/null; then
	test "$with_gnu_ld" != no && break
      else
        test "$with_gnu_ld" != yes && break
      fi
    fi
  done
  IFS="$ac_save_ifs"
else
  ac_cv_path_LD="$LD" # Let the user override the test with a path.
fi])
LD="$ac_cv_path_LD"
if test -n "$LD"; then
  AC_MSG_RESULT($LD)
else
  AC_MSG_RESULT(no)
fi
test -z "$LD" && AC_MSG_ERROR([no acceptable ld found in \$PATH])
AC_SUBST(LD)
AM_PROG_LD_GNU
])

AC_DEFUN(AM_PROG_LD_GNU,
[AC_CACHE_CHECK([if the linker ($LD) is GNU ld], ac_cv_prog_gnu_ld,
[# I'd rather use --version here, but apparently some GNU ld's only accept -v.
if $LD -v 2>&1 </dev/null | egrep '(GNU|with BFD)' 1>&5; then
  ac_cv_prog_gnu_ld=yes
else
  ac_cv_prog_gnu_ld=no
fi])
])

# AM_PROG_NM - find the path to a BSD-compatible name lister
AC_DEFUN(AM_PROG_NM,
[AC_MSG_CHECKING([for BSD-compatible nm])
AC_CACHE_VAL(ac_cv_path_NM,
[case "$NM" in
/* | [A-Za-z]:\\*)
  ac_cv_path_NM="$NM" # Let the user override the test with a path.
  ;;
*)
  IFS="${IFS= 	}"; ac_save_ifs="$IFS"; IFS="${IFS}:"
  for ac_dir in /usr/ucb /usr/ccs/bin $PATH /bin; do
    test -z "$ac_dir" && ac_dir=.
    if test -f $ac_dir/nm; then
      # Check to see if the nm accepts a BSD-compat flag.
      # Adding the `sed 1q' prevents false positives on HP-UX, which says:
      #   nm: unknown option "B" ignored
      if ($ac_dir/nm -B /dev/null 2>&1 | sed '1q'; exit 0) | egrep /dev/null >/dev/null; then
        ac_cv_path_NM="$ac_dir/nm -B"
      elif ($ac_dir/nm -p /dev/null 2>&1 | sed '1q'; exit 0) | egrep /dev/null >/dev/null; then
        ac_cv_path_NM="$ac_dir/nm -p"
      else
        ac_cv_path_NM="$ac_dir/nm"
      fi
      break
    fi
  done
  IFS="$ac_save_ifs"
  test -z "$ac_cv_path_NM" && ac_cv_path_NM=nm
  ;;
esac])
NM="$ac_cv_path_NM"
AC_MSG_RESULT([$NM])
AC_SUBST(NM)
])

# my own additions to KDE's version
#
# checking for Imlib...

AC_DEFUN(AC_FIND_IMLIB_CONFIG,
   [AC_MSG_CHECKING([for "imlib-config"])

imlib_config_given=NO
ac_imlib_config=""

AC_ARG_WITH(imlib-config,
        [  --with-imlib-config     directory where \"imlib-config\" lies ],
        [  ac_imlib_config="$withval/imlib-config"
           imlib_config_given=yes
        ])

if test "$imlib_config_given" = "yes"; then
  if test ! -r $ac_imlib_config; then
    AC_MSG_RESULT(wrong file specified)
    ac_imlib_config=""
  else
    AC_MSG_RESULT($ac_imlib_config)
    LIB_IMLIB=`$ac_imlib_config --libs`
    AC_SUBST(LIB_IMLIB)
  fi
else
  ac_imlib_config=`which imlib-config`
  if test -z "$ac_imlib_config"; then
    AC_MSG_RESULT(no)
  else
    dummy=`echo "$ac_imlib_config" | grep '/imlib-config'`
    if test -z "$dummy"; then
      AC_MSG_RESULT(no)
      ac_imlib_config=""
    else
      LIB_IMLIB=`$ac_imlib_config --libs`
      imlib_config=`echo "$LIB_IMLIB" | grep lImlib`
      if test -z "$imlib_config"; then
        AC_MSG_RESULT(no)
        ac_imlib_config=""
      else
        AC_SUBST(LIB_IMLIB)
        AC_MSG_RESULT($ac_imlib_config)
      fi
    fi
  fi
fi

])

AC_DEFUN(AC_FIND_IMLIB,
   [AC_MSG_CHECKING([whether Imlib is installed properly])

imlib_includes_given=NO
imlib_libs_given=NO

AC_ARG_WITH(imlib-libraries,
        [  --with-imlib-libraries  where the Imlib library is installed ],
        [  ac_imlib_libraries="$withval"
           imlib_libs_given=yes
        ])

AC_ARG_WITH(imlib-includes,
        [  --with-imlib-includes   where the Imlib includes are ],
        [ ac_imlib_includes="$withval"
	  imlib_includes_given=yes
        ])

if test "$imlib_includes_given" = "yes"; then
  CXXFLAGS="$CXXFLAGS -I$ac_imlib_includes"
fi

if test "$imlib_libs_given" = "yes"; then
  LDFLAGS="$LDFLAGS -L$ac_imlib_libraries"
fi

AC_CACHE_VAL(ac_cv_lib_imlib,
[ac_save_LIBS="$LIBS"
LIBS="-lImlib -lgif $LIBJPEG $LIBTIFF $LIBPNG -lm $all_libraries -lXext -lX11 $LIBSOCKET"

AC_LANG_CPLUSPLUS
AC_TRY_LINK(dnl
[
#ifdef __cplusplus
extern "C" {
#endif
#include <Imlib.h>
ImlibInitParams par; /* this one is needed and it's only in versions >= 1.5 */
#ifdef __cplusplus
}
#endif
],
	[],
            eval "ac_cv_lib_imlib=yes",
            eval "ac_cv_lib_imlib=no")
LIBS="$ac_save_LIBS"
])dnl
if eval "test \"`echo $ac_cv_lib_imlib`\" = yes"; then
  AC_MSG_RESULT(yes)
  LIB_IMLIB="-lImlib -lgif $LIBJPEG $LIBTIFF $LIBPNG -lm"
  AC_SUBST(LIB_IMLIB)
else
  AC_MSG_ERROR(You need Imlib >= 1.5. You can get it from http://www.labs.redhat.com/imlib/)
fi
])

# Do all the work for Automake.  This macro actually does too much --
# some checks are only needed if your package does certain things.
# But this isn't really a big deal.

# serial 1

dnl Usage:
dnl AM_INIT_AUTOMAKE(package,version, [no-define])

AC_DEFUN(AM_INIT_AUTOMAKE,
[AC_REQUIRE([AM_PROG_INSTALL])
PACKAGE=[$1]
AC_SUBST(PACKAGE)
VERSION=[$2]
AC_SUBST(VERSION)
dnl test to see if srcdir already configured
if test "`cd $srcdir && pwd`" != "`pwd`" && test -f $srcdir/config.status; then
  AC_MSG_ERROR([source directory already configured; run "make distclean" there first])
fi
ifelse([$3],,
AC_DEFINE_UNQUOTED(PACKAGE, "$PACKAGE")
AC_DEFINE_UNQUOTED(VERSION, "$VERSION"))
AC_REQUIRE([AM_SANITY_CHECK])
AC_REQUIRE([AC_ARG_PROGRAM])
dnl FIXME This is truly gross.
missing_dir=`cd $ac_aux_dir && pwd`
AM_MISSING_PROG(ACLOCAL, aclocal, $missing_dir)
AM_MISSING_PROG(AUTOCONF, autoconf, $missing_dir)
AM_MISSING_PROG(AUTOMAKE, automake, $missing_dir)
AM_MISSING_PROG(AUTOHEADER, autoheader, $missing_dir)
AM_MISSING_PROG(MAKEINFO, makeinfo, $missing_dir)
AC_REQUIRE([AC_PROG_MAKE_SET])])


# serial 1

AC_DEFUN(AM_PROG_INSTALL,
[AC_REQUIRE([AC_PROG_INSTALL])
test -z "$INSTALL_SCRIPT" && INSTALL_SCRIPT='${INSTALL_PROGRAM}'
AC_SUBST(INSTALL_SCRIPT)dnl
])

#
# Check to make sure that the build environment is sane.
#

AC_DEFUN(AM_SANITY_CHECK,
[AC_MSG_CHECKING([whether build environment is sane])
# Just in case
sleep 1
echo timestamp > conftestfile
# Do `set' in a subshell so we don't clobber the current shell's
# arguments.  Must try -L first in case configure is actually a
# symlink; some systems play weird games with the mod time of symlinks
# (eg FreeBSD returns the mod time of the symlink's containing
# directory).
if (
   set X `ls -Lt $srcdir/configure conftestfile 2> /dev/null`
   if test "[$]*" = "X"; then
      # -L didn't work.
      set X `ls -t $srcdir/configure conftestfile`
   fi
   if test "[$]*" != "X $srcdir/configure conftestfile" \
      && test "[$]*" != "X conftestfile $srcdir/configure"; then

      # If neither matched, then we have a broken ls.  This can happen
      # if, for instance, CONFIG_SHELL is bash and it inherits a
      # broken ls alias from the environment.  This has actually
      # happened.  Such a system could not be considered "sane".
      AC_MSG_ERROR([ls -t appears to fail.  Make sure there is not a broken
alias in your environment])
   fi

   test "[$]2" = conftestfile
   )
then
   # Ok.
   :
else
   AC_MSG_ERROR([newly created file is older than distributed files!
Check your system clock])
fi
rm -f conftest*
AC_MSG_RESULT(yes)])

dnl AM_MISSING_PROG(NAME, PROGRAM, DIRECTORY)
dnl The program must properly implement --version.
AC_DEFUN(AM_MISSING_PROG,
[AC_MSG_CHECKING(for working $2)
# Run test in a subshell; some versions of sh will print an error if
# an executable is not found, even if stderr is redirected.
# Redirect stdin to placate older versions of autoconf.  Sigh.
if ($2 --version) < /dev/null > /dev/null 2>&1; then
   $1=$2
   AC_MSG_RESULT(found)
else
   $1="$3/missing $2"
   AC_MSG_RESULT(missing)
fi
AC_SUBST($1)])

# Like AC_CONFIG_HEADER, but automatically create stamp file.

AC_DEFUN(AM_CONFIG_HEADER,
[AC_PREREQ([2.12])
AC_CONFIG_HEADER([$1])
dnl When config.status generates a header, we must update the stamp-h file.
dnl This file resides in the same directory as the config header
dnl that is generated.  We must strip everything past the first ":",
dnl and everything past the last "/".
AC_OUTPUT_COMMANDS(changequote(<<,>>)dnl
ifelse(patsubst(<<$1>>, <<[^ ]>>, <<>>), <<>>,
<<test -z "<<$>>CONFIG_HEADERS" || echo timestamp > patsubst(<<$1>>, <<^\([^:]*/\)?.*>>, <<\1>>)stamp-h<<>>dnl>>,
<<am_indx=1
for am_file in <<$1>>; do
  case " <<$>>CONFIG_HEADERS " in
  *" <<$>>am_file "*<<)>>
    echo timestamp > `echo <<$>>am_file | sed -e 's%:.*%%' -e 's%[^/]*$%%'`stamp-h$am_indx
    ;;
  esac
  am_indx=`expr "<<$>>am_indx" + 1`
done<<>>dnl>>)
changequote([,]))])

