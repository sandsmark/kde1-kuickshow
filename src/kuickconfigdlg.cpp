#include <qtooltip.h>

#include <kapp.h>

#include "kuickconfigdlg.h"


KuickConfigDialog::KuickConfigDialog( QWidget *parent, const char *name, bool modal ) :
  LogoTabDialog( parent, name, modal, true )
{
  TOPMARGIN   = 20;
  MARGIN      = 10;

  uint items1 = 1;
  uint items2 = 1;

  gbox1 = new QGroupBox( i18n("Settings"), this, "settingsbox" );
  gbox1->adjustSize();
  gbox1->move( TOPMARGIN, TOPMARGIN );
	
  cbFullscreen = new QCheckBox( i18n("Fullscreen mode"), gbox1, "boscreen" );
  cbFullscreen->adjustSize();
  cbFullscreen->move( TOPMARGIN, TOPMARGIN );
  const uint wheight = cbFullscreen->height();

  cbShrinkToScreen = new QCheckBox( i18n("Shrink image to screensize, if larger"),
				    gbox1, "shrinktoscreen" );
  cbShrinkToScreen->adjustSize();
  cbShrinkToScreen->move( TOPMARGIN, TOPMARGIN + items1 * (MARGIN+wheight) );
  items1++;

  cbPreload = new QCheckBox( i18n("Preload next image"), gbox1, "preload");
  cbPreload->adjustSize();
  cbPreload->move( TOPMARGIN, TOPMARGIN + items1 * (MARGIN+wheight) );
  items1++;

  QLabel *l = new QLabel( i18n("Show only files with extension: "), gbox1, "label" );
  l->adjustSize();
  l->move( TOPMARGIN, TOPMARGIN + items1 * (MARGIN+wheight) );
			
  editFilter = new QLineEdit( gbox1, "filteredit" );
  editFilter->move( TOPMARGIN + l->width() + MARGIN, l->y() - 3 );
  editFilter->setFixedHeight( wheight + 3 );
  items1++;

  l = new QLabel( i18n("Slideshow delay (ms): "), gbox1, "slidedelay" );
  l->adjustSize();
  l->move( TOPMARGIN, TOPMARGIN + items1 * (MARGIN + wheight) );

  editSlide = new KIntegerLine( gbox1, "editdelay" );
  editSlide->setGeometry( editFilter->x(), l->y() - 3, 50, wheight + 3 );
  QToolTip::add( editSlide, i18n("default: 3000 = 3 seconds") );
  items1++;

  gbox2 = new QGroupBox( i18n("Quality / Speed"), gbox1, "qualitybox" );
  gbox2->adjustSize();
  gbox2->move( TOPMARGIN, TOPMARGIN + items1 * (MARGIN + wheight) );
  items1++;

  cbFastrender = new QCheckBox( i18n("Fast rendering"), gbox2, "fastrender" );
  cbFastrender->adjustSize();
  cbFastrender->move( TOPMARGIN, TOPMARGIN );

  cbDither16bit = new QCheckBox( i18n("Dither in HiColor (15/16bit) modes"),
				 gbox2, "dither16bit" );
  cbDither16bit->adjustSize();
  cbDither16bit->move( TOPMARGIN, TOPMARGIN + items2 * (MARGIN + wheight) );
  items2++;

  cbDither8bit = new QCheckBox( i18n("Dither in LowColor (<=8bit) modes"),
				gbox2, "dither8bit" );
  cbDither8bit->adjustSize();
  cbDither8bit->move( TOPMARGIN, TOPMARGIN + items2 * (MARGIN + wheight) );
  items2++;

  cbOwnPalette = new QCheckBox( i18n("Use own color palette"),
                                gbox2, "pal");
  cbOwnPalette->move( TOPMARGIN, TOPMARGIN + items2 * (MARGIN + wheight) );
  cbOwnPalette->adjustSize();
  connect( cbOwnPalette, SIGNAL( clicked() ), this, SLOT( useOwnPalette() ) );
  items2++;

  cbRemap = new QCheckBox( i18n("Fast palette remapping"), gbox2, "remap" );
  cbRemap->move( 2*TOPMARGIN, TOPMARGIN + items2 * (MARGIN + wheight) );
  cbRemap->adjustSize();
  items2++;

  l = new QLabel( i18n("Maximum cache size (kB): "), gbox2, "maxcache" );
  l->adjustSize();
  l->move( TOPMARGIN, TOPMARGIN + items2 * (MARGIN + wheight) );

  editMaxCache = new KIntegerLine( gbox2, "editmaxcache" );
  editMaxCache->setGeometry( l->x() + l->width() + MARGIN, l->y() - 3, 60, wheight + 3 );
  QToolTip::add( editMaxCache, i18n("0 = don't limit") );
  items2++;

  setCancelButton();

  cbFullscreen->setFocus();
}

KuickConfigDialog::~KuickConfigDialog()
{
}


void KuickConfigDialog::getConfig( QString &filter, uint &delay, bool &fullscreen,
				   bool &shrink, bool &preload, bool &remap,
				   bool &ownPalette,
				   bool &fastrender, bool &dither16bit,
				   bool &dither8bit, uint &maxCache )
{
  filter      = editFilter->text();
  delay       = (uint) editSlide->value();
  fullscreen  = cbFullscreen->isChecked();
  shrink      = cbShrinkToScreen->isChecked();
  preload     = cbPreload->isChecked();
  remap       = cbRemap->isChecked();
  ownPalette  = cbOwnPalette->isChecked();
  fastrender  = cbFastrender->isChecked();
  dither16bit = cbDither16bit->isChecked();
  dither8bit  = cbDither8bit->isChecked();

  maxCache    = (uint) editMaxCache->value();
}

void KuickConfigDialog::setConfig( QString filter, uint delay, bool fullscreen,
				   bool shrink, bool preload, bool remap,
				   bool ownPalette,
				   bool fastrender, bool dither16bit, bool dither8bit, uint maxCache )
{
  editFilter->setText( filter );
  editSlide->setValue( delay );
  cbFullscreen->setChecked( fullscreen );
  cbShrinkToScreen->setChecked( shrink );
  cbPreload->setChecked( preload );
  cbRemap->setChecked( remap );
  cbOwnPalette->setChecked( ownPalette );
  cbFastrender->setChecked( fastrender );
  cbDither16bit->setChecked( dither16bit );
  cbDither8bit->setChecked( dither8bit );
  editMaxCache->setValue( maxCache );

  useOwnPalette(); // enable/disable remap-checkbox
}


void KuickConfigDialog::resetDefaults()
{
  editFilter->setText( "*.jpg *.gif *.xpm *.ppm *.pgm *.png *.eim *.tiff");
  editSlide->setValue( 3000 );
  cbFullscreen->setChecked( false );
  cbShrinkToScreen->setChecked( true );
  cbPreload->setChecked( true );
  cbOwnPalette->setChecked( false );
  cbRemap->setChecked( true );
  cbFastrender->setChecked( true );
  cbDither16bit->setChecked( false );
  cbDither8bit->setChecked( true );
  editMaxCache->setValue( 10000 );

  useOwnPalette();
}


void KuickConfigDialog::useOwnPalette()
{
  cbRemap->setEnabled( cbOwnPalette->isChecked() );
}


void KuickConfigDialog::resizeEvent( QResizeEvent *e )
{
  LogoTabDialog::resizeEvent( e );
  gbox1->resize( width() - 2*TOPMARGIN, height() - 4*TOPMARGIN );
  gbox2->resize( width() - 4*TOPMARGIN, 195 );
  editFilter->resize( gbox2->width() - editFilter->x() + TOPMARGIN, editFilter->height() );
}

#include "kuickconfigdlg.moc"
