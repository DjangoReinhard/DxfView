#ifndef OPENCASCADE_H
#define OPENCASCADE_H

#include <QWidget>
#include <QMouseEvent>
#include <QWheelEvent>
#include <QKeyEvent>
#include <QGuiApplication>

#include <AIS_InteractiveContext.hxx>
#include <OpenGl_GraphicDriver.hxx>
#include <V3d_View.hxx>
#include <Aspect_Handle.hxx>
#include <Aspect_DisplayConnection.hxx>
#include <Graphic3d_GraphicDriver.hxx>

#include <QGLWidget>
#ifdef _WIN32
#include <WNT_Window.hxx>
#else
#undef None
#include <Xw_Window.hxx>
#endif

#include <BRepPrimAPI_MakeSphere.hxx>
#include <BRepPrimAPI_MakeCone.hxx>
#include <BRepPrimAPI_MakeTorus.hxx>
#include <BRepPrimAPI_MakeBox.hxx>
#include <AIS_Shape.hxx>
#include <TDF_Label.hxx>

//show xyz axis
#include <Geom_Axis2Placement.hxx>
#include <AIS_Trihedron.hxx>

#include <draw_primitives.h>
#include <variable.h>

#define gp_Euler gp_Pnt // Used as universal toolset.


namespace occ {
class OpenCascade: public QGLWidget
{
  Q_OBJECT

public:
  explicit OpenCascade(QWidget *parent = nullptr);

//  bool readStepfile(const std::string &theStepName);
//  void visit(const TDF_Label &theLabel);
  void show_3d_interactive_box();

  void show_shape(Handle(AIS_Shape) ashape); //
  void set_shape_selected(Handle(AIS_Shape) ashape);
  void clear_selection();
  void redraw();
  void update_jointpos(double j0,
                       double j1,
                       double j2,
                       double j3,
                       double j4,
                       double j5);
  void get_selections();
  void delete_selections();
  void erase_all();

  unsigned int selected_contour = 0;

public slots:
  // View
  void switchOrthographic();
  void setFrontView();
  void setBackView();
  void setLeftView();
  void setRightView();
  void setTopView();
  void setBottomView();

  void zoom2Fit();

protected:
  enum CurrentAction3d
  {
    CurAction3d_Nothing,
    CurAction3d_DynamicPanning,
    CurAction3d_DynamicZooming,
    CurAction3d_DynamicRotation
    };
  void setOrthographic();
  void setPerspective();

  void paintEvent(QPaintEvent*);
  void resizeEvent(QResizeEvent*);
  void mousePressEvent(QMouseEvent *event);
  void mouseReleaseEvent(QMouseEvent *event);
  void mouseMoveEvent(QMouseEvent *event);
  void wheelEvent(QWheelEvent *event);

private:
  void m_initialize_context(); //
  Handle(AIS_InteractiveContext)  m_context;//
  Handle(V3d_Viewer)              m_viewer;//
  Handle(V3d_View)                m_view;//
  Handle(Graphic3d_GraphicDriver) m_graphic_driver;//
  Handle(AIS_InteractiveObject)   m_aisViewCube;//

  // Xyz axis sign.
  Handle(Geom_Axis2Placement)     axis;//
  Handle(AIS_Trihedron)           aisTrihedron;//

  std::vector<Handle(AIS_Trihedron)> aisTrihedrons;
  Standard_Integer m_x_max;
  Standard_Integer m_y_max;
  CurrentAction3d  m_current_mode;
  //gp_Trsf current_tcp;

  Handle(AIS_Shape) aisBody_tcp_xaxis, aisBody_tcp_yaxis, aisBody_tcp_zaxis;
  };
}

#endif // OPENCASCADE_H

