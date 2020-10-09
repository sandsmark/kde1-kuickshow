/****************************************************************************
** $Id: imlibconfig.cpp,v 1.4 1998/09/22 18:44:10 gis Exp $
**
** KuickData, a class containing/loading/saving  all preferences of KuickShow
**
** Created : 98
**
** Copyright (C) 1998 by Carsten Pfeiffer.  All rights reserved.
**
****************************************************************************/

#include <stdlib.h>

#include "imlibconfig.h"


ImlibConfig::ImlibConfig()
{
  fullScreen     = false;
  shrinkToScreen = true;
  ownPalette     = true;
  fastRemap      = true;
  fastRender  	 = true;
  dither16bit    = false;
  dither8bit     = true;
  maxCache       = 10000;

  gamma          = 256;
  brightness     = 256;
  contrast       = 256;

  gammaFactor      = 10;
  brightnessFactor = 10;
  contrastFactor   = 10;
}


void ImlibConfig::load( KConfig *kc )
{
  kc->setGroup( "ImlibConfiguration" );
  fullScreen = (kc->readEntry( "Fullscreen", "no" ) == "yes");
  shrinkToScreen = ( kc->readEntry( "ShrinkToScreenSize", "yes" ) == "yes" );
  ownPalette  = (kc->readEntry( "UseOwnPalette", "yes" ) == "yes");
  fastRemap   = (kc->readEntry( "FastRemapping", "yes" ) == "yes");
  fastRender  = (kc->readEntry( "FastRendering", "yes" ) == "yes");
  dither16bit = (kc->readEntry( "Dither16Bit", "no" ) == "yes");
  dither8bit  = (kc->readEntry( "Dither8Bit", "yes" ) == "yes");

  maxCache    = kc->readNumEntry( "MaxCacheSize", 10000 );

  gamma       = kc->readNumEntry( "DefaultGamma", 256 );
  brightness  = kc->readNumEntry( "DefaultBrightness", 256 );
  contrast    = kc->readNumEntry( "DefaultContrast", 256 );

  gammaFactor      = abs( kc->readNumEntry( "GammaFactor", 10 ) );
  brightnessFactor = abs( kc->readNumEntry( "BrightnessFactor", 10 ) );
  contrastFactor   = abs( kc->readNumEntry( "ContrastFactor", 10 ) );
}


void ImlibConfig::save( KConfig *kc )
{
  kc->setGroup( "ImlibConfiguration" );
  kc->writeEntry( "Fullscreen", fullScreen ? "yes" : "no" );
  kc->writeEntry( "ShrinkToScreenSize", shrinkToScreen ? "yes" : "no" );
  kc->writeEntry( "UseOwnPalette", ownPalette ? "yes" : "no" );
  kc->writeEntry( "FastRemapping", fastRemap ? "yes" : "no" );
  kc->writeEntry( "FastRendering", fastRender ? "yes" : "no" );
  kc->writeEntry( "Dither16Bit", dither16bit ? "yes" : "no" );
  kc->writeEntry( "Dither8Bit", dither8bit ? "yes" : "no" );
  kc->writeEntry( "MaxCacheSize", maxCache );

  kc->writeEntry( "DefaultGamma", gamma );
  kc->writeEntry( "DefaultBrightness", brightness );
  kc->writeEntry( "DefaultContrast", contrast );

  kc->writeEntry( "GammaFactor", gammaFactor );
  kc->writeEntry( "BrightnessFactor", brightnessFactor );
  kc->writeEntry( "ContrastFactor", contrastFactor );

  kc->sync();
}
