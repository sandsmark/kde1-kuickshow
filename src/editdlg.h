#ifndef __EDITDLG_H
#define __EDITDLG_H

#include <qdialog.h>
#include <qlined.h>

class EditDialog : public QDialog
{
  Q_OBJECT

  public:
  
    EditDialog::EditDialog( QString text=0, const char *editText=0, 
                            const char *caption=0, QWidget *parent=0, 
                            const char *name=0, bool modal=false );

    const char *text() { return le->text(); }
    
  private:
  
    QLineEdit *le;

};


#endif // __EDITDLG_H
