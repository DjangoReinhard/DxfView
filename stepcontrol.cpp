#include "stepcontrol.h"
#include "AbstractUIHelper.h"

#include <OSD.hxx>
#include <AIS_Trihedron.hxx>
#include <AIS_ViewCube.hxx>
#include <AIS_Selection.hxx>
#include <AIS_ColoredShape.hxx>
#include <AIS_ColoredDrawer.hxx>
#include <BRepLib.hxx>
#include <BRepOffsetAPI_ThruSections.hxx>
#include <BRepBuilderAPI_MakeWire.hxx>
#include <BRepBuilderAPI_Transform.hxx>
#include <BRepBuilderAPI_MakeFace.hxx>
#include <BRepBuilderAPI_MakeEdge.hxx>
#include <BRepPrimAPI_MakePrism.hxx>
#include <BRepFilletAPI_MakeFillet.hxx>
#include <BRepOffsetAPI_MakeThickSolid.hxx>
#include <BRepPrimAPI_MakeCylinder.hxx>
#include <BRepAlgoAPI_Fuse.hxx>
#include <BRepTools_ReShape.hxx>
#include <BRepTools.hxx>
#include <BRepBuilderAPI_MakeVertex.hxx>
#include <gp_Trsf.hxx>
#include <TopoDS.hxx>
#include <TopoDS_Solid.hxx>
#include <TopExp.hxx>
#include <TopTools_IndexedMapOfShape.hxx>
#include <TopExp_Explorer.hxx>
#include <TopoDS_Compound.hxx>
#include <TPrsStd_AISPresentation.hxx>
#include <STEPControl_Writer.hxx>
#include <STEPControl_Reader.hxx>
#include <STEPCAFControl_Reader.hxx>
#include <STEPCAFControl_Controller.hxx>
#include <Geom_Line.hxx>
#include <Geom_Circle.hxx>
#include <Geom_TrimmedCurve.hxx>
#include <Geom_CartesianPoint.hxx>
#include <GC_MakeArcOfCircle.hxx>
#include <GC_MakeArcOfEllipse.hxx>
#include <GC_MakeCircle.hxx>
#include <GC_MakeEllipse.hxx>
#include <GC_MakeSegment.hxx>
#include <gce_MakeRotation.hxx>
#include <TopExp.hxx>
#include <TopoDS_Wire.hxx>
#include <TopoDS.hxx>
#include <TopExp_Explorer.hxx>
#include <TopoDS_Edge.hxx>
#include <TDocStd_Document.hxx>
#include <TDocStd_Application.hxx>
#include <TDF_Label.hxx>
#include <TDF_AttributeIterator.hxx>
#include <TDF_ChildIterator.hxx>
#include <TDF_LabelSequence.hxx>
#include <TDataStd_Name.hxx>
#include <TDataStd_TreeNode.hxx>
#include <TDataStd_UAttribute.hxx>
#include <TNaming_NamedShape.hxx>
#include <TopTools.hxx>
#include <Geom_Plane.hxx>
#include <Geom_CylindricalSurface.hxx>
#include <Geom2d_Ellipse.hxx>
#include <Geom2d_TrimmedCurve.hxx>
#include "Geom_Axis2Placement.hxx"
#include <GCE2d_MakeSegment.hxx>
#include <GC_MakeArcOfCircle.hxx>
#include <XCAFDoc_Area.hxx>
#include <XCAFDoc_Centroid.hxx>
#include <XCAFDoc_Datum.hxx>
#include <XCAFDoc_Dimension.hxx>
#include <XCAFDoc_Location.hxx>
#include <XCAFDoc_Volume.hxx>
#include <XCAFDoc_DocumentTool.hxx>
#include <XCAFApp_Application.hxx>
#include <XCAFDoc_ColorTool.hxx>
#include <XCAFDoc_ShapeTool.hxx>
#include <XCAFDoc_DocumentTool.hxx>
#include <Quantity_Color.hxx>
#include <Quantity_ColorRGBA.hxx>

#include "XCAFPrs_DocumentExplorer.hxx"
#include <TDataStd_Name.hxx>
#include <XCAFDoc_AssemblyItemId.hxx>
#include <XCAFDoc_AssemblyItemRef.hxx>

#include <BRepTools.hxx>
#include <Font_BRepFont.hxx>
#include <Font_BRepTextBuilder.hxx>
#include <Bnd_Box.hxx>

#include "gp_Elips.hxx"
#include <NCollection_Mat4.hxx>
#include <gp_Quaternion.hxx>


StepController::StepController(occ::OpenCascade& view, AbstractUIHelper& auh, void* /*model*/)
 : Abstract3DControl(view, auh) {
  }


bool StepController::loadFile(const std::string &fileName) {
  segmentVector.push_back(segment);     //TODO: ???

  STEPCAFControl_Controller::Init();
  Handle(XCAFApp_Application)  app = XCAFApp_Application::GetApplication();

  app->NewDocument("MDTV-XCAF", doc);
  STEPCAFControl_Reader stepReader;

  stepReader.SetColorMode(true);
  stepReader.SetNameMode(true);
  stepReader.SetLayerMode(true);
  stepReader.SetPropsMode(true);
  stepReader.ReadFile(fileName.c_str());
  stepReader.Transfer(doc);

  rootLabel = doc->Main();
  shapeTool = XCAFDoc_DocumentTool::ShapeTool(rootLabel);
  colorTool = XCAFDoc_DocumentTool::ColorTool(rootLabel);

  return true;
  }


void StepController::drawModel() {
  drawModel(rootLabel, v);
  }


void StepController::setActiveLayer(int layer) {
  }


void StepController::drawModel(const TDF_Label& id, occ::OpenCascade& view) {
  id.EntryDump(std::cout);
  Quantity_Color        col;
  TopoDS_Shape          shape;
  Handle(TDataStd_Name) name;

  if (id.FindAttribute(TDataStd_Name::GetID(), name)) {
     std::cout << "  Name: " << name->Get() << std::endl;
     }
  bool skip = 0;

  if (shapeTool->IsShape(id)) {
     //TopoDS_Shape aShape;
     //if a shape can be made from the current label, look for the color of that label:
     if (shapeTool->GetShape(id, shape)) {
        //std::cout<<"made a shape"<<std::endl;

        if (colorTool->GetColor(shape, XCAFDoc_ColorSurf, col)) skip = 0;
        else                                                    skip = 1;
        }

     if (!skip) {
        segmentVector.back().Ais_ShapeVec.push_back(new AIS_Shape(shape));
        //if(aColor.Name()!=Quantity_NOC_YELLOW && aColor.Name()!=Quantity_NOC_RED) {
        segmentVector.back().Ais_ShapeVec.back()->SetColor(col);
        //}
        segmentVector.back().Ais_ShapeVec.back()->SetDisplayMode(AIS_Shaded);
        segmentVector.back().Ais_ShapeVec.back()->Attributes()->SetFaceBoundaryDraw(true);
        segmentVector.back().Ais_ShapeVec.back()->Attributes()
                                                ->SetFaceBoundaryAspect(new Prs3d_LineAspect(Quantity_NOC_BLACK
                                                                                           , Aspect_TOL_SOLID
                                                                                           , 1.));
        segmentVector.back().Ais_ShapeVec.back()->Attributes()->SetIsoOnTriangulation(true);

        view.show_shape(segmentVector.back().Ais_ShapeVec.back());
        }
     }
  /*! Repeat the visit function for each childmember. */
  for (TDF_ChildIterator c(id); c.More(); c.Next()) {
      drawModel(c.Value(), view);
      }
  }
