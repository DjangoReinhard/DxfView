#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <opencascade.h>
#include <draw_primitives.h>
#include <abstract3dcontrol.h>
#include "AbstractUIHelper.h"

#include <QMainWindow>
#include <QListWidget>
#include <QString>

#include <vector>
#include "dx_data.h"
#include "abstract3dcontrol.h"


// Dialog file open library, https://github.com/samhocevar/portable-file-dialogs/blob/master/examples/example.cpp
#include <portable-file-dialogs.h>
#if _WIN32
#define DEFAULT_PATH "C:\\"
#else
#define DEFAULT_PATH "~/Documents"
#endif


QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE


class MainWindow: public QMainWindow, AbstractUIHelper
{
  Q_OBJECT
public:
  MainWindow(QWidget *parent = nullptr);
 ~MainWindow();

protected:
  bool openDxfFile(const QString& filename);
  bool openStepFile(const QString& filename);

  void refresh();
  void load_opencascade_primitives();
  virtual void addLayer(double l);
  virtual void addListEntry(QListWidgetItem* item);

private slots:
  void on_btOpenDXF_clicked();
  void on_btTest1_clicked();
  void on_btTest2_clicked();
  void on_cbLayer_index_changed(int);
  void on_listElements_itemSelectionChanged();

private:
  Ui::MainWindow*    ui;
  occ::OpenCascade*  preView;
  Abstract3DControl* ctrl3D;
  bool               loadInProgress;
  double             activeLayer;
  };
#endif // MAINWINDOW_H
