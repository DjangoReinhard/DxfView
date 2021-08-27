#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "dxfcontrol.h"
#include "stepcontrol.h"

#include <QTimer>
#include <QDebug>


void separateLayers(std::map<double, std::vector<DRW_Entity*>> &m,
                    dx_ifaceBlock *block);
void dump(DRW_Entity *e);


MainWindow::MainWindow(QWidget *parent)
 : QMainWindow(parent)
 , ui(new Ui::MainWindow)
 , preView(nullptr)
 , ctrl3D(nullptr) {
  ui->setupUi(this);
  preView = new occ::OpenCascade(this);
  ui->gridLayout_opencascade->addWidget(preView);
  ui->listElements->setSelectionMode(QAbstractItemView::ExtendedSelection);

  connect(ui->actionOpenDXF,     &QAction::triggered, this,    &MainWindow::on_btOpenDXF_clicked);
  connect(ui->actionOpenStep,    &QAction::triggered, this,    &MainWindow::on_btTest2_clicked);

  connect(ui->actionOrthografic, &QAction::triggered, preView, &occ::OpenCascade::switchOrthographic);
  connect(ui->actionTop,         &QAction::triggered, preView, &occ::OpenCascade::setTopView);
  connect(ui->actionFront,       &QAction::triggered, preView, &occ::OpenCascade::setFrontView);
  connect(ui->actionLeft,        &QAction::triggered, preView, &occ::OpenCascade::setLeftView);
  connect(ui->actionBottom,      &QAction::triggered, preView, &occ::OpenCascade::setBottomView);
  connect(ui->actionBack,        &QAction::triggered, preView, &occ::OpenCascade::setBackView);
  connect(ui->actionRight,       &QAction::triggered, preView, &occ::OpenCascade::setRightView);
  connect(ui->actionZoom2Fit,    &QAction::triggered, preView, &occ::OpenCascade::zoom2Fit);

  QTimer *timer = new QTimer(this);

  connect(timer, &QTimer::timeout, this, &MainWindow::refresh);
  timer->start(200);
  }


MainWindow::~MainWindow() {
  delete ui;
  delete preView;
  }


void MainWindow::refresh() {
  preView->redraw();
  }


bool MainWindow::openDxfFile(const QString& filename) {
  ui->cbLayer->clear();
  ui->listElements->clear();

  if (ctrl3D) delete ctrl3D;
  loadInProgress = true;
  ctrl3D = new DxfController(*preView, *this, new dx_data());
  bool ok = ctrl3D->loadFile(filename.toStdString());

  if (!ok) {
     qDebug() << "Error reading file " << filename;
     }
  else {
     qDebug() << "Ok reading file " << filename;
     loadInProgress = false;
     on_cbLayer_index_changed(0); //TODO:
     preView->zoom2Fit();
     }
  return ok;
  }


bool MainWindow::openStepFile(const QString& filename) {
  ui->cbLayer->clear();
  ui->listElements->clear();

  if (ctrl3D) delete ctrl3D;
  loadInProgress = true;
  ctrl3D = new StepController(*preView, *this);
  bool ok = ctrl3D->loadFile(filename.toStdString());

  if (!ok) {
     qDebug() << "Error reading file " << filename;
     }
  else {
     qDebug() << "Ok reading file " << filename;
     loadInProgress = false;
     on_cbLayer_index_changed(0); //TODO:
     preView->zoom2Fit();
     }
  return ok;
  }


void MainWindow::addLayer(double l) {
  ui->cbLayer->addItem(QString::number(l));
  }


void MainWindow::addListEntry(QListWidgetItem* item) {
  ui->listElements->addItem(item);
  }


void MainWindow::on_btOpenDXF_clicked() {
  if (!pfd::settings::available()){
     std::cerr << "Portable File Dialogs are not available on this platform. \n"
                  "On linux install zenity, $ sudo apt-get install zenity\n" << std::endl;
     }
  auto f = pfd::open_file("Choose files to read"
                        , DEFAULT_PATH
                        , { "Dxf Files (.dxf)", "*.dxf",
                            "All Files", "*" }
                        , pfd::opt::none);
  if (f.result().size() > 0)
     openDxfFile(f.result().at(0).c_str()); // This lib can open multiple results.
  }


void MainWindow::on_btTest1_clicked() {
  qDebug() << "Test1 button clicked ...";
  }


void MainWindow::on_btTest2_clicked() {
  if (!pfd::settings::available()){
     std::cerr << "Portable File Dialogs are not available on this platform. \n"
                  "On linux install zenity, $ sudo apt-get install zenity\n" << std::endl;
     }
  auto f = pfd::open_file("Choose files to read"
                        , DEFAULT_PATH
                        , { "Step Files (.stp, .step)", "*.stp, *.step",
                            "All Files", "*" }
                        , pfd::opt::none);
  if (f.result().size() > 0)
     openStepFile(f.result().at(0).c_str());
  }


void MainWindow::on_cbLayer_index_changed(int index) {
  if (loadInProgress) {
     qDebug() << "file loading active ...";
     return;
     }
  if (index < 0) {
     qDebug() << "invalid index ... #";
     return;
     }
  qDebug() << "Combobox layer changed to ... #" << index;
  ui->listElements->clear();
  ctrl3D->setActiveLayer(index);
  }


void MainWindow::on_listElements_itemSelectionChanged() {
#ifdef REDNOSE
  // first set all elements to not selected    
  for (std::map<double, std::vector<dx_Entity*>>::iterator it = dxfData.groupedEntities.begin()
     ; it != dxfData.groupedEntities.end()
     ; ++it) {
      std::vector<dx_Entity*> entities = (*it).second;

      for (unsigned i = 0; i < entities.size(); ++i) {
          dx_Entity *pE = entities.at(i);

          pE->selected = false;
          }
      }
// now remember selection
  QList<QListWidgetItem*> selection = ui->listElements->selectedItems();

  for (int i = 0; i < selection.size(); ++i) {
      ListItem *item = dynamic_cast<ListItem*>(selection[i]);

      item->setSelected(true);
      item->dump();
      }
  drawModel();
#endif
  }


void ListItem::dump() const {
  DRW_Entity *e = rE.entity;

  switch (rE.entity->type()) {
    case DRW::E3DFACE:
         std::cout << "\t>>> entity type:    E3DFace" << std::endl;
         break;
    case DRW::ARC: {
//       std::cout << "entity type: Arc" << std::endl;
         DRW_Coord c   = ((DRW_Arc*) e)->basePoint;
         double    r   = ((DRW_Arc*) e)->radious;
         double    sa  = ((DRW_Arc*) e)->staangle;
         double    ea  = ((DRW_Arc*) e)->endangle;
         int       ccw = ((DRW_Arc*) e)->isccw;

         std::cout << std::fixed << "arc: (" << c.x << "/" << c.y << "/" << c.z
                   << ") with radius: " << r << "  start-angle: " << sa
                   << "  end-angle: " << ea << "  dir: " << (ccw ? "ccw" : "cw")
                   << std::endl;
         } break;
    case DRW::BLOCK:
         std::cout << "\t>>> entity type:    Block" << std::endl;
         break;
    case DRW::CIRCLE: {
//       std::cout << "entity type: Circle" << std::endl;
         DRW_Coord c = ((DRW_Circle*) e)->basePoint;
         double r = ((DRW_Circle*) e)->radious;

         std::cout << std::fixed << "circle: (" << c.x << "/" << c.y << "/" << c.z
                   << ") with radius: " << r << std::endl;
         } break;
    case DRW::DIMENSION:
         std::cout << "\t>>> entity type:    Dimension" << std::endl;
         break;
    case DRW::DIMALIGNED:
         std::cout << "\t>>> entity type:    DimAligned" << std::endl;
         break;
    case DRW::DIMLINEAR:
         std::cout << "\t>>> entity type:    DimLinear" << std::endl;
         break;
    case DRW::DIMRADIAL:
         std::cout << "\t>>> entity type:    DimRadial" << std::endl;
         break;
    case DRW::DIMDIAMETRIC:
         std::cout << "\t>>> entity type:    DimDiametric" << std::endl;
         break;
    case DRW::DIMANGULAR:
         std::cout << "\t>>> entity type:    DimAngular" << std::endl;
         break;
    case DRW::DIMANGULAR3P:
         std::cout << "\t>>> entity type:    DimAngular3P" << std::endl;
         break;
    case DRW::DIMORDINATE:
         std::cout << "\t>>> entity type:    DimOrdinate" << std::endl;
         break;
    case DRW::ELLIPSE:
         std::cout << "\t>>> entity type:    Ellipse" << std::endl;
         break;
    case DRW::HATCH:
         std::cout << "\t>>> entity type:    Hatch" << std::endl;
         break;
    case DRW::IMAGE:
         std::cout << "\t>>> entity type:    Image" << std::endl;
         break;
    case DRW::INSERT:
         std::cout << "\t>>> entity type:    Insert" << std::endl;
         break;
    case DRW::LEADER:
         std::cout << "\t>>> entity type:    Leader" << std::endl;
         break;
    case DRW::LINE: {
//       std::cout << "entity type: Line" << std::endl;
         DRW_Coord start = ((DRW_Line*) e)->basePoint;
         DRW_Coord end   = ((DRW_Line*) e)->secPoint;

         if (start.z != end.z) {
            std::cout << std::fixed << "\t\tinvalid line from (" << start.x << "/"
                      << start.y << "/" << start.z << ")   to =>   (" << end.x
                      << "/" << end.y << "/" << end.z << ")" << std::endl;
            }
         else {
            std::cout << std::fixed << "line from (" << start.x << "/" << start.y
                      << "/" << start.z << ")   to =>   (" << end.x << "/" << end.y
                      << "/" << end.z << ")" << std::endl;
            }
         } break;
    case DRW::LWPOLYLINE:
         std::cout << "\t>>> entity type:    LWPolyLine" << std::endl;
         break;
    case DRW::MTEXT:
         std::cout << "\t>>> entity type:    MText" << std::endl;
         break;
    case DRW::POINT:
         std::cout << "\t>>> entity type:    Point" << std::endl;
         break;
    case DRW::POLYLINE:
         std::cout << "\t>>> entity type:    PolyLine" << std::endl;
         break;
    case DRW::RAY:
         std::cout << "\t>>> entity type:    Ray" << std::endl;
         break;
    case DRW::SOLID:
         std::cout << "\t>>> entity type:    Solid" << std::endl;
         break;
    case DRW::SPLINE:
         std::cout << "\t>>> entity type:    Spline" << std::endl;
         break;
    case DRW::TEXT:
         std::cout << "\t>>> entity type:    Text" << std::endl;
         break;
    case DRW::TRACE:
         std::cout << "\t>>> entity type:    Trace" << std::endl;
         break;
    case DRW::UNDERLAY:
         std::cout << "\t>>> entity type:    Underlay" << std::endl;
         break;
    case DRW::VERTEX:
         std::cout << "\t>>> entity type:    Vertex" << std::endl;
         break;
    case DRW::VIEWPORT:
         std::cout << "\t>>> entity type:    ViewPort" << std::endl;
         break;
    case DRW::XLINE:
         std::cout << "\t>>> entity type:    XLine" << std::endl;
         break;
    default:
         std::cout << "\t<<< unknown Entity encountered!!!" << std::endl;
         break;
    }
  }
