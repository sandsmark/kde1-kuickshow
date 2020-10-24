/***************************************************************************
** $Id: imlibwidget.cpp,v 1.17 1998/09/24 16:26:55 gis Exp $
**
** ImlibWidget: maps an Xlib window with Imlib's contents on a QWidget
**		 can zoom and scroll images inside the QWidget
**
** Created : 98
**
** Copyright (C) 1998 by Carsten Pfeiffer.  All rights reserved.
**
****************************************************************************/

#include <stdlib.h>

#include <qcolor.h>
#include <qdrawutl.h>
#include <qkeycode.h>
#include <qmsgbox.h>
#include <qobject.h>
#include <qpalette.h>
#include <qpainter.h>
#include <qpen.h>
#include <qpixmapcache.h>

#include <kapp.h>
#include <kfiledialog.h>
#include <kwm.h>

#include "imlibwidget.h"
#include "effects.h"

#if 0
ImlibWidget::ImlibWidget( const char *filename, ImlibConfig *_idata, QWidget *parent, const char *name ) :
  QWidget( parent, name )
{
  idata = _idata;
  deleteImlibConfig = false;
  deleteImlibData   = true;
  disp = kapp->getDisplay();

  if ( !idata ) // if no imlib configuration was given, create one ourself
  {
    idata = new ImlibConfig;
    deleteImlibConfig = true;
  }

  ImlibInitParams par;

  // PARAMS_PALETTEOVERRIDE taken out because of segfault in imlib :o(
  par.flags = ( PARAMS_REMAP |
		PARAMS_FASTRENDER | PARAMS_HIQUALITY | PARAMS_DITHER |
		PARAMS_IMAGECACHESIZE | PARAMS_PIXMAPCACHESIZE );

  par.paletteoverride = idata->ownPalette ? 1 : 0;
  par.remap           = idata->fastRemap ? 1 : 0;
  par.fastrender      = idata->fastRender ? 1 : 0;
  par.hiquality       = idata->dither16bit ? 1 : 0;
  par.dither          = idata->dither8bit ? 1 : 0;
  uint maxcache       = idata->maxCache;
  if ( maxcache != 0 ) // 0 = no limit
  {
    par.imagecachesize  = maxcache * 1024;
    par.pixmapcachesize = maxcache * 1024;
  }

  //id = Imlib_init_with_params( disp, &par );


  init( filename, id );
}
#endif


ImlibWidget::ImlibWidget( const char *filename, ImlibConfig *_idata, QWidget *parent, const char *name ) :
  QWidget( parent, name )
{
  if ( !_idata )
    close( false );

  idata = _idata;
  brightness = 0;
  contrast = 0;
  gamma = 1.1;

#if 0
  deleteImlibConfig = false;
  deleteImlibData   = false;
#endif

  disp = kapp->getDisplay();
  init( filename );
}


void ImlibWidget::init( const char *filename )
{
    QPixmapCache::setCacheLimit(65535); // 64MB ish
  p           = 0L;
  im          = 0L;
  viewerMenu  = 0L;
  transWidget = 0L;
  w = h = 1; // > 0 for XCreateWindow
  isFullscreen = false;
  shiftPressed = false;
  desktopWidth = QApplication::desktop()->width();
  desktopHeight= QApplication::desktop()->height();

  setPalette( QPalette( QColor( black ) ) );
  setBackgroundMode( PaletteBackground );

#if 0
  id = _id;
  mod = imlib_create_color_modifier();
#endif

  win = XCreateSimpleWindow(disp, winId(), 0,0,w,h,0,0,0);

  if ( filename )
    if ( !showNextImage( filename ) )
      close( false );

  setFullscreen( idata->fullScreen );
}

ImlibWidget::~ImlibWidget()
{
  setPopupMenu( false );
#if 0
  if ( p ) Imlib_free_pixmap( id, p );
  if ( im ) Imlib_destroy_image( id, im );
  if ( deleteImlibData ) delete id;
#endif
  if ( win ) XDestroyWindow( disp, win );
  if ( deleteImlibConfig ) delete idata;
}

bool ImlibWidget::loadImageInternal( char *file, bool cacheOnly )
{
  puts(file);
  uint myW, myH;

  QPixmap *myIm = QPixmapCache::find(file);
  if (!myIm || myIm->isNull()) {
      puts("not in cache");
      myIm = new QPixmap;
      myIm->load(file);
      if (myIm->isNull()) {
          printf("failed to load %s\n", file);
          return false;
      }
      QPixmapCache::insert(file, myIm);
  } else {
      puts("Cache hit");
  }
  if (cacheOnly) {
      return true;
  }

#if 0
  Imlib_Image myIm = imlib_load_image_immediately( file );
  if ( !myIm ) return false; // couldn't load file, probably wrong format

  imlib_context_set_image(myIm);

  mod.brightness = idata->brightness;
  mod.contrast = idata->contrast;
  mod.gamma = idata->gamma;

  // only set image modifier if image is not already cached
  // otherwise cache would be lost
  if ( myIm != imCache )
      imlib_context_set_color_modifier(mod);

  myW = myIm->rgb_width;
  myH = myIm->rgb_height;
#endif
  myW = myIm->width();
  myH = myIm->height();

  if ( idata->shrinkToScreen )
  { // eventually set width and height to the best/max possible screen size
    if ( myW > desktopWidth )
    {
      float ratio = (float) myW / (float) myH;
      myW = desktopWidth;
      myH = (int) ((float) myW / ratio);
    }

    // not "else", as the previously calculated "h" might be larger than screen
    if ( myH > desktopHeight )
    {
      float ratio = (float) myW / (float) myH;
      myH = desktopHeight;
      myW = (int) ((float) myH * ratio);
    }
  }

  im = myIm;
  w  = myW;
  h  = myH;

  return true;
}


bool ImlibWidget::loadImage( const char *filename )
{
  bool success = false;
  char *file = (char *) filename;

  success = loadImageInternal( file );

  if ( success ) currentFilename = file;
  return success;
}

bool ImlibWidget::preloadImage( const char *filename )
{
  char *file = (char *) filename;

  bool success = loadImageInternal( file, true );
  return success;
}


void ImlibWidget::setFullscreen( bool enable )
{
  xpos = 0; ypos = 0;
  if ( enable && !isFullscreen ) // set Fullscreen
  {
    // old, broken maximize
setGeometry( 0, 0, desktopWidth, desktopHeight );
        KWM::setDecoration( winId(), KWM::noDecoration );
    //    setGeometry( 0, 0, desktopWidth, desktopHeight );

    // kview-style maximize - breaks auto-fullscreen on startup :o(
//    move( frameGeometry().x() - geometry().x(),
//	  frameGeometry().y() - geometry().y() );
//    resize( qApp->desktop()->size() );
    // --------------------------------------------
    
    if ( cw == w && ch == h ) // almostCenterImage() doesn't catch this one
      XMoveWindow( disp, win, 0, 0 );
  }

  else if ( !enable && isFullscreen ) // go into window mode
  {
    resize( w, h );
    move( 0, 0 ); // necessary for kview-style maximize

    KWM::setDecoration( winId(), KWM::normalDecoration );
    XMoveWindow( disp, win, 0, 0 );
    setCaption( currentFilename );
  }

  isFullscreen = enable;
}


void ImlibWidget::setPopupMenu( bool enable )
{
  if ( enable && !viewerMenu )
  {
    viewerMenu = new QPopupMenu;

    brightnessMenu = new QPopupMenu;
    brightnessMenu->insertItem( i18n("+    b"), this, SLOT( moreBrightness() ) );
    brightnessMenu->insertItem( i18n("-    B"), this, SLOT( lessBrightness() ) );

    contrastMenu = new QPopupMenu;
    contrastMenu->insertItem( i18n("+    c"), this, SLOT( moreContrast() ) );
    contrastMenu->insertItem( i18n("-    C"), this, SLOT( lessContrast() ) );

    gammaMenu = new QPopupMenu;
    gammaMenu->insertItem( i18n("+    g"), this, SLOT( moreGamma() ) );
    gammaMenu->insertItem( i18n("-    G"), this, SLOT( lessGamma() ) );

    itemViewerZoomIn = viewerMenu->insertItem( i18n("Zoom in"), this,
					       SLOT( zoomIn() ) );
    itemViewerZoomOut = viewerMenu->insertItem( i18n("Zoom out"), this,
						SLOT( zoomOut() ) );
    viewerMenu->insertSeparator();
    itemRotate90    = viewerMenu->insertItem( i18n("Rotate 90°"), this,
					      SLOT( rotate90() ) );
    itemRotate270   = viewerMenu->insertItem( i18n("Rotate -90°"), this,
					      SLOT( rotate270() ) );
    viewerMenu->insertSeparator();
    itemViewerFlipH = viewerMenu->insertItem( i18n("Flip horizontally"), this,
					      SLOT( flipHoriz() ) );
    itemViewerFlipV = viewerMenu->insertItem( i18n("Flip vertically"), this,
					      SLOT( flipVert() ) );
    viewerMenu->insertSeparator();
    viewerMenu->insertItem( i18n("Brightness"), brightnessMenu );
    viewerMenu->insertItem( i18n("Contrast"), contrastMenu );
    viewerMenu->insertItem( i18n("Gamma"), gammaMenu );
    viewerMenu->insertSeparator();
    itemViewerPrint = viewerMenu->insertItem( i18n("Print image..."), this,
					      SLOT( printImage() ) );
    itemViewerSave = viewerMenu->insertItem( i18n("Save as..."), this,
					      SLOT( saveImage() ) );
  }
  else if ( !enable && viewerMenu )
  {
    delete viewerMenu;
    viewerMenu = 0L;
  }
}


void ImlibWidget::renderImage( uint w, uint h, bool dontMove )
{
  xpos = 0;
  ypos = 0;

  QApplication::setOverrideCursor( waitCursor );

#if 0
  if ( p ) Imlib_free_pixmap( id, p );
  Imlib_render( id, im, w, h);

  p = Imlib_move_image( id, im);
#endif
  if (p) {
      delete p;
  }
  p = new QPixmap(*im);
  p->resize(w, h);
  if (p->isNull()) {
      puts("no image");
      return;
  }
  if (contrast != 0) {
      adjustContrast(*p, contrast);
  }
  if (brightness != 0) {
      adjustBrightness(*p, brightness/100.);
  }

  XSetWindowBackgroundPixmap( disp, win, p->handle());
  XClearWindow( disp, win );


  if ( !dontMove )
  {
    if ( isFullscreen )
      centerImage();
    else XMoveWindow( disp, win, 0, 0 );
  }

  XResizeWindow( disp, win, w, h );

  QApplication::restoreOverrideCursor();
}

void ImlibWidget::showImage()
{
  XMapWindow( disp, win );
  XSync( disp, False );
}


void ImlibWidget::scrollImage( int x, int y, bool restrict )
{
  xpos += x;
  ypos += y;

  uint cwlocal = cw;
  uint chlocal = ch;

  if ( isFullscreen || cw > desktopWidth )
    cwlocal = desktopWidth;

  if ( isFullscreen || ch > desktopHeight )
    chlocal = desktopHeight;

  if ( restrict ) // don't allow scrolling in certain cases
  {
    if ( x != 0 ) // restrict x-movement
    {
      if ( w <= cwlocal )
	xpos -= x; // restore previous position
      else if ( (xpos <= 0) && (xpos + w <= cwlocal) )
	xpos = cwlocal - w;
      else if ( (xpos + w >= cwlocal) && xpos >= 0 )
	xpos = 0;
    }

    if ( y != 0 ) // restrict y-movement
    {
      if ( h <= chlocal )
	ypos -= y;
      else if ( (ypos <= 0) && (ypos + h <= chlocal) )
	ypos = chlocal - h;
      else if ( (ypos + h >= chlocal) && ypos >= 0 )
	ypos = 0;
    }
  }
  XMoveWindow( disp, win, xpos, ypos );
  XClearArea( disp, win, xpos, ypos, w, h, false );
  showImage();
}


void ImlibWidget::changeBrightness( int factor, bool rerender )
{
  if ( factor == 0 )
    return;

  if (factor < 0 && brightness <= -100) {
      return;
  }
  if (factor > 0 && brightness >= 200) {
      return;
  }

  brightness += factor;
  if (brightness < -100) {
      brightness = -100;
  } else if (brightness > 200) {
      brightness = 200;
  }

  if ( rerender )
  {
    renderImage( w, h );
    showImage();
  }
}

void ImlibWidget::changeContrast( int factor, bool rerender )
{
  if ( factor == 0 )
    return;


  if (factor < 0 && contrast <= -50) {
      return;
  }
  if (factor > 0 && contrast >= 255) {
      return;
  }

  contrast += factor;
  if (contrast < -50) {
      contrast = -50;
  } else if (contrast > 255) {
      contrast = 255;
  }

  printf("contrast: %d\n", contrast);
  if ( rerender )
  {
    renderImage( w, h );
    showImage();
  }
}

void ImlibWidget::changeGamma( int factor, bool rerender )
{
  if ( factor == 0 )
    return;

  //mod.gamma += idata->gammaFactor * (int) factor;
  //setImageModifier();

  if ( rerender )
  {
    renderImage( w, h );
    showImage();
  }
}


void ImlibWidget::zoomImage( float factor )
{
  float wf, hf;

  wf = (float) w * factor;
  hf = (float) h * factor;

  w = (uint) wf;
  h = (uint) hf;

  paintImage();
  showImage();
}


void ImlibWidget::flipImage( bool horizontally )
{
#if 0
  imlib_context_set_image(im);
  if ( horizontally )
      imlib_image_flip_horizontal();
  else
      imlib_image_flip_vertical();

  renderImage( w, h );
  showImage();
#endif
}

void ImlibWidget::rotate( int d )
{
#if 0
  imlib_context_set_image(im);
  //idk
  double angle = 0;
  if (d == -1) {
      angle = 270
  } else if (d == 1) {
      angle = 90;
  }
  imlib_rotate_image_from_buffer(im, angle);


  paintImage();
  showImage();
#endif
}


void ImlibWidget::printImage()
{
  emit sigPrintImage( im, currentFilename );
}


void ImlibWidget::paintImage()
{
  renderImage( w, h );

  if ( !isFullscreen )
    resize( w, h );
}

void ImlibWidget::centerImage()
{
  if ( w == cw && h == ch )
  {
    xpos = ypos = 0;
    XMoveWindow( disp, win, 0, 0 );
  }
  else almostCenterImage();
}

void ImlibWidget::almostCenterImage()
{
  // only centers if image is different size, as current window
  // use centerImage() instead. This is to avoid flickering,
  // as almostCenterImage() is called from resizeEvent().
  if ( w != cw || h != ch )
  {
    xpos = cw/2 - w/2;
    ypos = ch/2 - h/2;

    XMoveWindow( disp, win, xpos, ypos );
  }
}


bool ImlibWidget::showNextImage( const char *filename )
{
  if ( !loadImage( filename ) )
  {
    emit sigBadImage( filename );
    return false;
  }
  else
  {
    paintImage();
    if ( !isFullscreen) setCaption( filename );
    showImage();
    return true;
  }
}


void ImlibWidget::saveImage()
{
  QString file;
  QString filter = "*.gif *.jpeg *.jpg *.png *.tiff *.xpm *.eim *.ppm";
  file = KFileDialog::getSaveFileName( currentFilename.data(), filter.data() );
  if ( !file.isEmpty() )
  {
#if 0
    imlib_context_set_image(im);
    imlib_apply_color_modifier();
    Imlib_Load_Error err;
    imlib_save_image_with_error_return(file.data(), &err);
#endif
    if ( !im->save(file, "png") ) // todo hardcode
    {
      QString tmp = i18n("Couldn't save the file,\n");
      tmp += i18n("maybe this disk is full, or you don't\n");
      tmp += i18n("have write permissions to the file.");
      QMessageBox::warning( this, i18n("File saving failed"), tmp );
    }
  }
}


void ImlibWidget::resizeEvent( QResizeEvent * )
{
  cw  = width();
  ch  = height();

  almostCenterImage();
}


void ImlibWidget::keyPressEvent( QKeyEvent *e )
{
  shiftPressed = ( e->key() == 4128 ); // Shift key

  switch ( e->key() )
  {
  case Key_Escape 	: close( false );
    break;
  case Key_Up 		: scrollImage( 0, 10 );
    break;
  case Key_Down 	: scrollImage( 0, -10 );
    break;
  case Key_Left 	: scrollImage( 10, 0 );
    break;
  case Key_Right 	: scrollImage( -10, 0 );
    break;
  case Key_Plus 	: zoomIn();
    break;
  case Key_Minus 	: zoomOut();
    break;
  case Key_Asterisk    	: flipHoriz();
    break;
  case Key_Slash 	: flipVert();
    break;
  case Key_7 		: rotate270(); // 90 degrees counterclockwise
    break;
  case Key_9 		: rotate90();  // 90 degrees clockwise
    break;
  case Key_B 		: if ( e->state() & ShiftButton ) lessBrightness();
                          else              		  moreBrightness();
    break;
  case Key_C 		: if ( e->state() & ShiftButton ) lessContrast();
                          else              		  moreContrast();
    break;
  case Key_G 		: if ( e->state() & ShiftButton ) lessGamma();
                          else             		  moreGamma();
    break;
  case Key_S            : if ( e->state() & ControlButton ) saveImage();
    break;


  default 		: e->ignore();
  }

  e->accept();
}

void ImlibWidget::keyReleaseEvent( QKeyEvent *e )
{
  if ( e->key() == 4128 ) // Shift-key released
  {
    setCursor( arrowCursor );
    if ( transWidget )
    {
      delete transWidget;
      transWidget = 0L;
    }
  }

  shiftPressed = false; // on any key, set shiftPressed to false
  e->accept();
}

void ImlibWidget::mousePressEvent( QMouseEvent *e )
{
  xmove = e->x(); // for moving the image with the mouse
  ymove = e->y();

  xzoom = xmove;  // for zooming with the mouse
  yzoom = ymove;

  xposPress = xmove;
  yposPress = ymove;

  if ( shiftPressed )
    setCursor( crossCursor ); // need a "hand-cursor"


  if ( viewerMenu && e->button() == RightButton )
    viewerMenu->popup( mapToGlobal( e->pos() ) );
}

void ImlibWidget::mouseMoveEvent( QMouseEvent *e )
{
  if ( shiftPressed )
  {
    if ( !transWidget )
    {
      transWidget = new QWidget( this );
      transWidget->resize( size() );
      transWidget->setBackgroundMode( NoBackground );
      transWidget->show();
    }

    transWidget->hide();
    QPainter p( transWidget );
    p.eraseRect( transWidget->rect() );
    transWidget->show();

    int width  = e->x() - xposPress;
    int height = e->y() - yposPress;

    if ( width < 0 )
    {
      width = abs( width );
      xzoom = e->x();
    }

    if ( height < 0 )
    {
      height = abs( height );
      yzoom = e->y();
    }

    QColor white( "white" );
    QPen pen( white, 1, DashLine );
    p.setPen( pen );     // for drawing white dashed line
    p.drawRect( xzoom, yzoom, width, height );
    p.setPen( DotLine ); // defaults to black dotted line pen
    p.drawRect( xzoom, yzoom, width, height );
    p.flush();
  }

  else // move the image
  {
    // scrolling with mouse
    uint xtmp = e->x();
    uint ytmp = e->y();
    scrollImage( xtmp - xmove, ytmp - ymove );
    xmove = xtmp;
    ymove = ytmp;
  }
}

void ImlibWidget::mouseReleaseEvent( QMouseEvent *e )
{
  if ( transWidget )
  { // destroy the transparent widget, used for showing the rectangle (zoom)
    delete transWidget;
    transWidget = 0L;
  }

  if ( !shiftPressed ) // only proceed if shift-Key is still pressed!
    return;

  int neww, newh, topX, topY, botX, botY;
  float factor, factorx, factory;

  setCursor( arrowCursor );

  // zoom into the selected area
  uint x = e->x();
  uint y = e->y();

  if ( xposPress > x )
  {
    topX = x;
    botX = xposPress;
  }
  else
  {
    topX = xposPress;
    botX = x;
  }

  if ( yposPress > y )
  {
    topY = y;
    botY = yposPress;
  }
  else
  {
    topY = yposPress;
    botY = y;
  }

  neww = botX - topX;
  newh = botY - topY;

  factorx = (float) cw / (float) neww;
  factory = (float) ch / (float) newh;

  if ( factorx < factory ) // use the smaller factor
    factor = factorx;
  else factor = factory;

  if ( (uint) factor > 10 )
  {
    debug("KuickShow: Scaling at a factor larger than 10 (here %i) is not recommended... aborting", (int) factor);
    return;
  }

  w = (uint) ( factor * (float) w );
  h = (uint) ( factor * (float) h );

  int xtmp = - (int) (factor * abs(xpos - topX) );
  int ytmp = - (int) (factor * abs(ypos - topY) );

  // if image has different ratio (width/height), center it
  int xcenter = (cw - (int) (neww * factor)) / 2;
  int ycenter = (ch - (int) (newh * factor)) / 2;

  xtmp += xcenter;
  ytmp += ycenter;

  // renderImage resets xpos and ypos to 0!
  renderImage( w, h, true );

  xpos = xtmp; ypos = ytmp;

  XMoveWindow( disp, win, xpos, ypos );
  scrollImage( 1, 1, true ); // unrestricted scrolling

  // reset shift-key flag (keyReleaseEvent doesn't seem to catch them all
  shiftPressed = false;
}

void ImlibWidget::closeEvent( QCloseEvent *e )
{
  e->accept();
  delete this;
}

#include "imlibwidget.moc"
