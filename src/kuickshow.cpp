/****************************************************************************
** $Id: kuickshow.cpp,v 1.15 1998/09/23 20:01:12 gis Exp $
**
** KuickShow - a fast and comfortable image viewer based on Rasterman's Imlib
**
** Created : 98
**
** Copyright (C) 1998 by Carsten Pfeiffer.  All rights reserved.
**
****************************************************************************/

#include <stdio.h>

#include <qdir.h>
#include <qdialog.h>
#include <qglobal.h>
#include <qkeycode.h>
#include <qmsgbox.h>
#include <qstring.h>
#include <qstrlist.h>

#if QT_VERSION >= 140
  #include <qprinter.h>
  #include <qprintdialog.h>
#endif

#include <kapp.h>
#include <kfileinfo.h>
#include <kiconloader.h>
#include <kstatusbar.h>
#include <ktoolbar.h>
#include <kwm.h>

#include "imlibconfig.h"
#include "imlibwidget.h"
#include "kuickshow.h"
#include "version.h"

KuickShow::KuickShow( QString start, const char *name) : KTMainWindow( name )
{
  kdata = new KuickData;
  kdata->load();

  id = 0L;

  initImlib();

  finder = 0L;
  viewer = 0L;
  viewerCount = 0;
  noBrowser = false;
  highlightWorkaround = 0L;
  QString startDir, startFile;

  // ----------- hack to work around whacky kfileinfo -----------
  // parses given filename into path and filename without path
  if ( !start.isEmpty() )
  {
    if ( start.left( 1 ) != "/" ) // relative path -> add prepend current dir
      start = QDir::currentDirPath() + "/" + start;

    if ( start.right( 1 ) == "/" ) // last character is a "/" -> directory
      startDir = start;
    else
    {
      int lastSlash = start.findRev( "/" );
      if ( lastSlash != -1 )
      {
	lastSlash++;
	startDir = start.left( lastSlash );
	startFile = start.right( start.length() - lastSlash );
	KFileInfo fi( startDir.data(), startFile.data() );
	if ( fi.isDir() ) // maybe no trailing / on a given dir
        {
	  startDir  = startDir + startFile;
	  startFile = 0L;
	}
	else if ( !fi.isReadable() )
	{
	  KFileInfo fi( startDir, "" );
	  if ( !fi.isReadable() )
	    startDir = "";
	
	  startFile = "";
	}
      }
    }
  } // start not empty
  // -----------------------------------------------------------

  #define ID_EXIT 	0
  #define ID_CONFIG 	1
  #define ID_SLIDESHOW  2
  #define ID_RELOAD     3
  #define ID_ABOUT 	4
  #define ID_HELP       5
  #define ID_HOMEDIR    6
  #define ID_SHOWHIDDEN 100

  mainWidget = new MainWidget( startDir, kdata, this, "MainWidget" );
  box = mainWidget->getFileBox();
  connect( box, SIGNAL( sigFileSelected( KFileInfo * ) ),
	   this, SLOT( showImage( KFileInfo * ) ));

  connect( box, SIGNAL( sigPrintImage( QString ) ),
	   this, SLOT( printImage( QString ) ) );

  connect( box, SIGNAL( sigDeleteItem( QString ) ),
	   this, SLOT( deleteFile( QString ) ) );
			
  box->connectFileHighlighted( this, SLOT( fileHighlighted( KFileInfo * )) );
  box->connectDirSelected(     this, SLOT( dirSelected( KFileInfo * )) );

  box->installEventFilter( this );


  KConfig *kc = kapp->getConfig();


  tBar = new KToolBar( this, "toolbar" );
  (void) addToolBar( tBar );
  KIconLoader *loader = new KIconLoader;

  tBar->insertButton( loader->loadIcon( "ksexit.xpm" ), ID_EXIT,
		      SIGNAL( clicked() ),
		      this, SLOT( slotQuit() ), true,
		      i18n( "Exit KuickShow" ) );

  tBar->insertSeparator();
  tBar->insertButton( loader->loadIcon( "ksconfig.xpm" ), ID_CONFIG,
		      SIGNAL( clicked() ),
		      this, SLOT( configuration() ), true,
		      i18n( "Configuration" ) );

  tBar->insertButton( loader->loadIcon( "ksslide.xpm" ), ID_SLIDESHOW,
		      SIGNAL( clicked() ),
		      this, SLOT( startSlideShow() ), true,
		      i18n( "Slideshow" ) );

  tBar->insertSeparator();

  tBar->insertButton( loader->loadIcon( "home.xpm" ), ID_HOMEDIR,
		      SIGNAL( clicked() ),
		      box, SLOT( cdHome() ), true,
		      i18n( "Change to Home Directory") );

  tBar->insertButton( loader->loadIcon( "reload.xpm" ), ID_RELOAD,
		      SIGNAL( clicked() ),
		      box, SLOT( reloadDir() ), true,
		      i18n( "Reload Directory" ) );

  tBar->insertButton( loader->loadIcon( "lock.xpm" ), ID_SHOWHIDDEN,
		      SIGNAL( toggled( int ) ),
		      this, SLOT( slotToggleHidden( int ) ), true,
		      i18n("Toggle showing hidden files") );
  tBar->setToggle( ID_SHOWHIDDEN, true );
  kc->setGroup( "SessionSettings" );
  if ( (kc->readBoolEntry("ShowHiddenFiles", false) ) )
    tBar->setButton( ID_SHOWHIDDEN, true );

  tBar->insertSeparator();

  tBar->insertButton( loader->loadIcon( "topic.xpm" ), ID_ABOUT,
		      SIGNAL( clicked() ),
		      this, SLOT( about() ), true,
		      i18n( "About KuickShow" ) );

  tBar->insertButton( loader->loadIcon( "help.xpm" ), ID_HELP,
		      SIGNAL( clicked() ),
		      this, SLOT( help() ), true,
		      i18n( "Help" ) );

  delete loader;

  sBar = new KStatusBar( this, "statusbar" );
  sBar->insertItem( "                          ", 0 );
  sBar->insertItem( "           ", 1 );
#if KDE_VERSION_MAJOR > 0
  setStatusBar( sBar );
#endif

  setView( box );
  box->setFocus();
  setCaption( "KuickShow "KUICKSHOWVERSION );

  QSize s = kc->readSizeEntry( "BrowserSize" );
  if ( s.isNull() || s.isEmpty() )
    resize( 500, 500 ); // default size
  else resize( s );

  if ( !startFile.isEmpty() ) // don't show browser, when image on commandline
  {
    noBrowser = true;
    hide();
  }
  else
  {
    show();
    mainWidget->show();
  }

  if ( !startDir.isEmpty() && !startFile.isEmpty() )
  {
    // I can't highlight startFile, when the browser is not shown, so I do
    // it in the eventhandler, when showing the browser.

    highlightWorkaround = startFile;
    box->setCurrentItem( startFile.data() ); // this doesn't work
    KFileInfo fi( startDir.data(), startFile.data() );
    showImage( &fi );
  }
}

KuickShow::~KuickShow()
{
  saveSettings();

  if ( viewer ) viewer->close( false );
  if ( id )     delete id;
  if ( kdata )  delete kdata;
  kapp->quit();
}


void KuickShow::viewerDeleted()
{
  viewer = 0L;
  viewerCount--;
  if ( noBrowser && viewerCount == 0 )
    delete this;
  else
  {
    setActiveWindow();
    box->setFocus();
  }
}


void KuickShow::fileHighlighted( KFileInfo *fi )
{
  QString size;
  size.sprintf( " %.1f kB", (float) fi->size()/1024 );
  sBar->changeItem( size, 0 );
  sBar->changeItem( box->filename( fi ), 1 );
}

// I can't change the filesize, as the KFileInfo pointer is undefined :o((
void KuickShow::dirSelected( KFileInfo * )
{
  sBar->changeItem( box->directory(), 1 );
}

void KuickShow::showImage( KFileInfo *fi )
{
  if ( isImage( fi ) )
  {
    viewer = new ImlibWidget( 0L, kdata->idata, id, 0L );
    viewerCount++;
    connect( viewer, SIGNAL( destroyed() ), this, SLOT( viewerDeleted() ) );
    connect( viewer, SIGNAL( sigBadImage(const char *) ),
	     this, SLOT( messageCantLoadImage(const char*) ) );
    connect( viewer, SIGNAL( sigPrintImage( ImlibImage *, QString ) ),
	     this, SLOT( printImage( ImlibImage *, QString ) ));

    viewer->setPopupMenu( true );
    viewer->installEventFilter( this );
    if ( !viewer->showNextImage( box->filename( fi ) ) )
      viewer->close( false ); // couldn't load image, close window
    else
    {
      viewer->show();
      KWM::activate( viewer->winId() );
      viewer->setFocus();

      // DND stuff
      KDNDDropZone *dropZone = new KDNDDropZone( viewer , DndURL);
      connect( dropZone, SIGNAL( dropAction( KDNDDropZone *) ),
	       this, SLOT( dropEvent( KDNDDropZone * ) ));

      if ( kdata->preloadImage )
      {
        KFileInfo *fi_ = box->next( false ); // don't move cursor
        if ( isImage( fi_ ) )
          viewer->preloadImage( box->filename( fi_ ) ); // preload next image
      }
    } // viewer created successfully
  } // isImage
}

void KuickShow::startSlideShow()
{
  if ( box->hasFiles() ) // we have some images at all
  {
    KFileInfo *fi = box->firstFile();

    oldSlideName = box->filename( fi );
    showImage( fi );
    QTimer::singleShot( kdata->slideDelay, this, SLOT( nextSlide() ) );
  }
}

void KuickShow::nextSlide()
{
  if ( !viewer ) return;
  QString slideName = box->filename( box->next() );
  if ( slideName == oldSlideName )
  {
    viewer->close( false );
    return;
  }
  viewer->showNextImage( slideName.data() );
  oldSlideName = slideName;
  QTimer::singleShot( kdata->slideDelay, this, SLOT( nextSlide() ) );
}


void KuickShow::printImage( QString filename )
{
  ImlibImage *im = Imlib_load_image( id, filename.data() );
  printImage( im, filename );
  Imlib_destroy_image( id, im );
}


void KuickShow::printImage( ImlibImage *im, QString )
{
#if QT_VERSION < 140
  debug("KuickShow: Printing only available with Qt >= 1.40" );
  return;

#else

  QString printCmd, printerName;

  QPrinter p;
  if ( !QPrintDialog::getPrinterSetup( &p ) )
    return;

  // map Qt's options to imlibs'
  int pagesize  = PAGE_SIZE_A4;	// default value: Din A4
  int colormode = 0; 		// default value: grayscale
  int copies    = 1;		// just print one copy
  bool ofile    = false;        // don't output as file

  QPrinter::PageSize ps = p.pageSize();

  if ( ps == QPrinter::A4 )
    pagesize = PAGE_SIZE_A4;

  else if ( ps == QPrinter::Letter )
    pagesize = PAGE_SIZE_LETTER;

  else if ( ps == QPrinter::Legal )
    pagesize = PAGE_SIZE_LEGAL;

  else if ( ps == QPrinter::Executive )
    pagesize = PAGE_SIZE_EXECUTIVE;

  if ( p.colorMode() == QPrinter::Color )
    colormode = 1;

  copies      = p.numCopies();
  printCmd    = p.printProgram();
  printerName = p.printerName();
  ofile       = p.outputToFile();

  ImlibSaveInfo info;

  info.page_size      = pagesize;
  info.color          = colormode;
  info.scaling        = 1024; // how to save in original size, without scaling?
  info.xjustification = 512;  // center
  info.yjustification = 512;  // center

  QString tmpName;
  if ( ofile ) // user just wants to print to file
    tmpName = p.outputFileName();
  else
    tmpName = tmpnam( NULL );

  if ( Imlib_save_image( id, im, tmpName.data(), &info ) == 0 )
  {
    debug(i18n("KuickShow: Couldn't print image.")); // FIXME, show messagebox
    return;
  }

  if ( ofile ) // done, user just wanted that postscript file
    return;

  // finally print the postscript file
  QString cmdline = printCmd + " -P\"" + printerName + "\" " + tmpName;
  debug("KuickShow: print commandline: %s", cmdline.data() );
  for ( int i=0; i < copies; i++ ) // hack, better use a switch in lpr...
    system( cmdline.data() );

#endif // QT_140
}


void KuickShow::dropEvent( KDNDDropZone *dropZone )
{
  QStrList &urlList = dropZone->getURLList();
  QString filename;

  QString url = urlList.first();
  if (url.right(1) == "/") // we don't want directories!
  {
    QString tmp( i18n("You can't drop directories\n" ) );
    tmp += i18n("onto the imageviewer!\n\n");
    QMessageBox::warning(this, i18n("KuickShow Drop Error"), tmp );
    return;
  }

  else // we got anything other than a directory
  {
    // cut url-prefix "file:"
    if (url.left(5) == "file:")
    {
      filename = url.right( (int) url.length() - 5);
      ImlibWidget *widget = (ImlibWidget *) (dropZone->getWidget() );
      widget->showNextImage( filename );
    }
    else
    {
      QString tmp( i18n("You can only drop local files\n") );
      tmp += i18n("onto the imageviewer!\n\n");
      QMessageBox::warning(this, i18n("KuickShow Drop Error"), tmp );
    }
  }
  if ( urlList.count() > 1 )
  {
    QString tmp( i18n("You can't drop multiple files!\n") );
    tmp += i18n("I only took the first one.\n\n");
    QMessageBox::warning(this, i18n("KuickShow Drop Error"), tmp );
  }
}


bool KuickShow::eventFilter( QObject *o, QEvent *e )
{
  bool ret = false;
  QKeyEvent *k = 0L;

  if ( e->type() == Event_KeyPress )
  {
    k = (QKeyEvent *) e;
    if ( (k->key() == Key_Q) && (k->state() & ControlButton) )
    {
      k->accept();
      saveSettings();
      //      kapp->quit(); // delete this or kapp->quit produce a segfault :o(
      exit(0);
    }
  }

  if ( o->isA( "ImlibWidget" ) )
  {
    QString img = "";
    KFileInfo *fi = 0L;
    KFileInfo *fi_next = 0L;

    if ( e->type() == Event_KeyPress )
    {
      switch (k->key())
      {
      case Key_F1:
	help();
	break;

      case Key_Home:
	fi = box->firstFile();
	break;

      case Key_End:
	fi = box->last();
	break;

      case Key_PageUp:
	fi = box->prev();
	if ( !isImage( fi ) )
	  fi = box->next();
	else
	  fi_next = box->prev( false ); // don't move cursor
	break;

      case Key_PageDown:
	fi = box->next();
	fi_next = box->next( false ); // don't move cursor
	break;

      case Key_Enter:
	fi = box->current();
	break;

      case Key_Return:
      {
	k->accept();
	ImlibWidget *iw = (ImlibWidget *)o;
	iw->setFullscreen( !iw->isFullscreen );
	return true; // don't pass keyEvent
      }

      case Key_Delete:
      {
	QString currentFile = box->filename( box->current() );
        if ( ! (k->state() & ShiftButton) )
	{
	  QString tmp = i18n( "Really delete the file\n\n" );
	  tmp += currentFile;
	  tmp += i18n( " ?\n" );
	  int button = QMessageBox::warning( this, i18n( "Delete file?" ), tmp,
					     i18n( "OK" ), i18n( "Cancel" ),
					     0L, 0, 1 );
	  if ( button == 1 ) return true;
	}
	
	// try to unlink file
	deleteFile( box->filename( box->current() ).data() );

	// next image
	fi = box->current();
	if ( !isImage( fi ) )
	  fi = box->next();
	
	break;
      }

      case Key_Space:
      {
	if ( noBrowser )
	{
	  noBrowser = false;
	  show();
	  if ( !highlightWorkaround.isEmpty() )
	  {  // highlight the file!
	    box->setCurrentItem( highlightWorkaround.data() );
	    highlightWorkaround = 0L;
	  }
	}
	
	else // hide the browser
	{
	  hide();
	  noBrowser =  true;
	}
	return true; // don't pass keyEvent
      } // Space

      default:
	fi = 0L;
      }

      if ( isImage( fi ) )
      {
	k->accept();
	
	// always remember the filename when switching
	if ( !highlightWorkaround.isEmpty() && noBrowser )
	  highlightWorkaround = fi->fileName();
	
	ImlibWidget *iw = (ImlibWidget *) o;
	iw->showNextImage( box->filename( fi ).data() );

	if ( kdata->preloadImage )
	  if ( isImage( fi_next ) ) // preload next image
	    iw->preloadImage( box->filename( fi_next ).data() );
	
	ret = true; // don't pass keyEvent
      }
      else
	ret = false; // no image, pass keyEvent
    } // keyPressEvent on ImlibWidget

  } // isA ImlibWidget


  else if ( o->isA( "FileView" ) )
  {
    if ( e->type() == Event_KeyPress )
    {
      if ( k->key() == Key_F1 ) help();
      else if ( (k->key() == Key_Space) && viewer ) // only if a viewer is active!
      {
	hide();
	noBrowser =  true;
	return true; // don't pass keyEvenent
      }

      else if ( k->key() == Key_Delete )
      {
	QString currentFile = box->filename( box->current() );
        if ( ! (k->state() & ShiftButton) )
	{
	  QString tmp = i18n( "Really delete the file\n\n" );
	  tmp += currentFile;
	  tmp += i18n( " ?\n" );
	  int button = QMessageBox::warning( this, i18n( "Delete file?" ), tmp,
					     i18n( "OK" ), i18n( "Cancel" ),
					     0L, 0, 1 );
	  if ( button == 1 ) return true;
	}
	
	// try to unlink file
	deleteFile( box->filename( box->current() ).data() );
      }

      else if ( isascii( k->key() ) && k->key() != (int) CTRL &&
		k->state() != ControlButton )
      {
	if ( finder )
	  return false; // pass keyEvent

	finder = new FileFinder( this );
	finder->move( sBar->width() - finder->width(),
		      sBar->y() + sBar->height() - finder->height() );
	connect( finder, SIGNAL( sigDeleteMe() ), this, SLOT( deleteFinder() ));
	connect( finder, SIGNAL( textChanged( const char * ) ),
		 box, SLOT( fileCompletion( const char * ) ));
	finder->show();
	finder->setFocus();
	QString s;
	s.sprintf( "%c", k->ascii() );
	finder->setText( s.data() );
	k->accept();
	ret = true; // don't pass event
      }
    }
  }
  return ret;
}

bool KuickShow::isImage( KFileInfo *fi )
{
  // check mimetype, isReadable...
  // isReadable doesn't work currently, because of broken KFileInfo
  if ( !fi )
    return false;
  return ( fi->isFile() );
}


void KuickShow::configuration()
{
  dialog = new KuickConfigDialog( 0L, "dialog", false );
  dialog->resize( 540, 450 );
  dialog->setCaption( i18n("KuickShow configuration") );
  dialog->setIcon( kapp->getMiniIcon() );
  ImlibConfig *idata = kdata->idata;
  dialog->setConfig( kdata->fileFilter, kdata->slideDelay, idata->fullScreen,
		     idata->shrinkToScreen, kdata->preloadImage,
		     idata->fastRemap, idata->ownPalette,
		     idata->fastRender, idata->dither16bit,
		     idata->dither8bit, idata->maxCache );

  connect( dialog, SIGNAL( applyButtonPressed() ),
	   this, SLOT( slotConfigApplied() ) );
  connect( dialog, SIGNAL( cancelButtonPressed() ),
	   this, SLOT( slotConfigRejected() ) );

  tBar->setItemEnabled( ID_CONFIG, false );
  dialog->show();
}

void KuickShow::slotConfigApplied()
{
  ImlibConfig *idata = kdata->idata;
  dialog->getConfig( kdata->fileFilter, kdata->slideDelay, idata->fullScreen,
		     idata->shrinkToScreen, kdata->preloadImage,
		     idata->fastRemap, idata->ownPalette,
		     idata->fastRender, idata->dither16bit,
		     idata->dither8bit , idata->maxCache );
  initImlib();
  kdata->save();

  if ( kdata->fileFilter != (QString) box->nameFilter() )
  {  // reload directory contents if filefilter changed
    box->setNameFilter( kdata->fileFilter );
    box->reloadDir();
  }

  delete dialog;
  tBar->setItemEnabled( ID_CONFIG, true );
}


void KuickShow::slotConfigRejected()
{
  delete dialog;
  tBar->setItemEnabled( ID_CONFIG, true );
}

void KuickShow::about()
{
  aboutWidget = new AboutWidget( 0L, "about" );
  aboutWidget->resize( 350, 350 );
  QWidget *d = QApplication::desktop();
  aboutWidget->move( d->width()/2  - aboutWidget->width()/2,
		     d->height()/2 - aboutWidget->height()/2 );
  aboutWidget->show();
}

void KuickShow::help()
{
  kapp->invokeHTMLHelp( "kuickshow/index.html", "" );
}

void KuickShow::slotToggleHidden( int id )
{
  if ( id == ID_SHOWHIDDEN )
  {
    box->slotToggleHidden();
  }
}


bool KuickShow::deleteFile( QString file )
{
  if ( unlink( file.data() ) < 0 )
  {
    QString tmp = i18n( "Sorry, I can't delete the file\n\n" );
    tmp += file + "\n\n";
    tmp += i18n( "A more robust filemanagement will be\n" );
    tmp += i18n( "available, later.\n" );
    QMessageBox::critical( this, i18n( "Delete failed" ), tmp );
    return false;
  }

  box->removeItem( box->current() );
  return true;
}


// ------ sessionmanagement - load / save current directory -----
void KuickShow::readProperties( KConfig *kc )
{
  QString dir = kc->readEntry( "CurrentDirectory" );
  if ( !dir.isEmpty() )
  {
    KFileInfo fi( dir );
    if ( fi.isReadable() )
      box->enterDir( dir.data() );
  }
}

void KuickShow::saveProperties( KConfig *kc )
{
  kc->writeEntry( "CurrentDirectory", box->directory().data() );
}
// --------------------------------------------------------------

void KuickShow::saveSettings()
{
  KConfig *kc = kapp->getConfig();

  kc->setGroup("SessionSettings");
  kc->writeEntry( "BrowserSize", size() );
  kc->writeEntry( "ShowHiddenFiles", box->showsHidden() );
  kc->sync();
}


void KuickShow::messageCantLoadImage( const char *filename )
{
  QString tmp = i18n("Sorry, I can't load the image\n\"");
  tmp += filename;
  tmp += i18n("\"\nMaybe it has a wrong format or your Imlib\n");
  tmp += i18n("is not installed properly.");
  QMessageBox::warning( 0, i18n("Image Error"), tmp.data() );
}

void KuickShow::deleteFinder()
{
  delete finder;
  finder = 0L;
  box->setFocus();
}


void KuickShow::initImlib()
{
  ImlibConfig *idata = kdata->idata;
  ImlibInitParams par;
  initImlibParams( idata, &par );

  id = Imlib_init_with_params( kapp->getDisplay(), &par );
  if ( !id )
  {
    initImlibParams( idata, &par );

    debug("*** KuickShow: Whoops, can't initialize imlib, trying my own palettefile now.");
    QString paletteFile = kapp->kde_datadir() + "/kuickshow/im_palette.pal";
    par.palettefile = paletteFile.data();
    par.flags |= PARAMS_PALETTEFILE;

    debug("Palettefile: %s", par.palettefile );

    id = Imlib_init_with_params( kapp->getDisplay(), &par );

    if ( !id )
    {
      QString tmp = i18n("Can't initialize \"Imlib\".\n");
      tmp += i18n("Start kuickshow on the commandline and look\n");
      tmp += i18n("out for some error messages.\n");
      tmp += i18n("I will quit now.");
      QMessageBox::critical( this, i18n("Fatal Imlib error"), tmp.data() );

      delete kdata;
      exit(1);
    }
  }
}


void KuickShow::initImlibParams( ImlibConfig *idata, ImlibInitParams *par )
{
  par->flags = ( PARAMS_REMAP |
		 PARAMS_FASTRENDER | PARAMS_HIQUALITY | PARAMS_DITHER |
		 PARAMS_IMAGECACHESIZE | PARAMS_PIXMAPCACHESIZE );
	
  par->paletteoverride = idata->ownPalette ? 1 : 0;
  par->remap           = idata->fastRemap ? 1 : 0;
  par->fastrender      = idata->fastRender ? 1 : 0;
  par->hiquality       = idata->dither16bit ? 1 : 0;
  par->dither          = idata->dither8bit ? 1 : 0;
  uint maxcache        = idata->maxCache;

  if ( maxcache != 0 ) // 0 = no limit
  {
    par->imagecachesize  = maxcache * 1024;
    par->pixmapcachesize = maxcache * 1024;
  }
}


void KuickShow::resizeEvent( QResizeEvent *e )
{
  mainWidget->resize( width(), height() );
  KTMainWindow::resizeEvent( e );

#if KDE_VERSION_MAJOR <= 0
  mainWidget->resize( width(), height() - sBar->height() );
  sBar->resize( width(), sBar->height() );
  sBar->move( 0, mainWidget->y() + mainWidget->height() );
#endif
}

void KuickShow::closeEvent( QCloseEvent * )
{
  delete this;
}
