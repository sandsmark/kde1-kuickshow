/****************************************************************************
** $Id: imlibconfig.h,v 1.3 1998/09/22 18:44:11 gis Exp $
**
** Definition of something or other
**
** Created : 979899
**
** Copyright (C) 1998 by Carsten Pfeiffer.  All rights reserved.
**
****************************************************************************/

#ifndef IMBLIBCONFIG_H
#define IMBLIBCONFIG_H

#include <kconfig.h>
typedef void*ImlibData ;

class ImlibConfig
{
public:
  ImlibConfig();
  ~ImlibConfig() {};

  void 		load( KConfig *kc );
  void 		save( KConfig *kc );

  bool 		fullScreen;
  bool 		shrinkToScreen;
  bool 		ownPalette;
  bool 		fastRemap;
  bool 		fastRender;
  bool		dither16bit;
  bool 		dither8bit;

  int		gamma;
  int 		brightness;
  int 		contrast;

  uint          gammaFactor;
  uint          brightnessFactor;
  uint          contrastFactor;
  
  uint          maxCache;
};


#endif
