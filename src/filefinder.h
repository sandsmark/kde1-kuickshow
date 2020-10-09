#ifndef FILEFINDER_H
#define FILEFINDER_H

#include <qevent.h>
#include <qlined.h>
#include <qstring.h>

class FileFinder : public QLineEdit
{
  Q_OBJECT

  public:
    FileFinder( QWidget *parent=0, const char *name=0 );
    ~FileFinder();

    QString               contents();

  public slots:

  private:
    void                  focusOutEvent( QFocusEvent * );
    void 		  keyPressEvent( QKeyEvent * );
  
  signals:
    void	          sigDeleteMe();

};

#endif // FILEFINDER_H
