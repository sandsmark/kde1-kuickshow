#include <qdir.h>
#include <qstring.h>

#include <kapp.h>
#include <kimgio.h>

#include "kuickshow.h"


int main(int argc, char **argv)
{
  KApplication app( argc, argv, "kuickshow" );
  kimgioRegister();

  QString start = "";
  if ( argc >= 2 )
    start = argv[1];

  if ( app.isRestored() )
    RESTORE( KuickShow )
  else
  {
    KuickShow *k = new KuickShow( start, "kuickshow" );
    app.setMainWidget( k );
  }

  return app.exec();
}
