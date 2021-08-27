#ifndef STEPCONTROL_H
#define STEPCONTROL_H
#include "abstract3dcontrol.h"

#include <BRepPrimAPI_MakeSphere.hxx>
#include <BRepPrimAPI_MakeCone.hxx>
#include <BRepPrimAPI_MakeTorus.hxx>
#include <BRepPrimAPI_MakeBox.hxx>
#include <XCAFDoc_ColorTool.hxx>
#include <XCAFDoc_ShapeTool.hxx>
#include <AIS_Shape.hxx>
#include <TDF_Label.hxx>
#include <opencascade.h>

#include <string>
#include <vector>

struct SEGMENT
{
  std::vector<Handle(AIS_Shape)> Ais_ShapeVec = {
    }; ///each stepfile can contain multiple shapes, we need the vector.
  gp_Trsf MyTrsf = {
    };
  };


#ifdef REDNOSE
extern SEGMENT Segment;
extern std::vector<SEGMENT> SegmentVec;

extern gp_Trsf level0x1x2x3x4x5x6;
#endif


class AbstractUIHelper;

class StepController : public Abstract3DControl
{
public:
  StepController(occ::OpenCascade& view, AbstractUIHelper& auh, void* model = nullptr);

  virtual bool loadFile(const std::string& fileName);
  virtual void drawModel();
  virtual void setActiveLayer(int layer);

protected:
  void drawModel(const TDF_Label& id, occ::OpenCascade& view);

private:
  Handle(XCAFDoc_ColorTool) colorTool;
  Handle(XCAFDoc_ShapeTool) shapeTool;
  Handle(TDocStd_Document)  doc;
  TDF_Label                 rootLabel;
  SEGMENT                   segment;
  std::vector<SEGMENT>      segmentVector;
  };
#endif // STEPCONTROL_H
