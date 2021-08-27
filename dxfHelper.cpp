/******************************************************************************
 **                                                                           **
 **  Copyright (C) 2015 José F. Soriano, rallazz@gmail.com                    **
 **                                                                           **
 **  This library is free software, licensed under the terms of the GNU       **
 **  General Public License as published by the Free Software Foundation,     **
 **  either version 2 of the License, or (at your option) any later version.  **
 **  You should have received a copy of the GNU General Public License        **
 **  along with this program.  If not, see <http://www.gnu.org/licenses/>.    **
 ******************************************************************************/
#include <dxfHelper.h>
#include <iostream>
#include <algorithm>
#include "libdwgr.h"
#include "libdxfrw.h"
#include "draw_primitives.h"
#include "AbstractUIHelper.h"


bool DxfHelper::fileImport(const std::string &fileI) {
  unsigned int found = fileI.find_last_of(".");
  std::string fileExt = fileI.substr(found + 1);
  std::transform(fileExt.begin(), fileExt.end(), fileExt.begin(), ::toupper);

  std::cout << "import file <| " << fileI << " |> with extension: " << fileExt
            << std::endl;

  if (fileExt == "DXF") {
     //loads dxf
     dxfRW *dxf = new dxfRW(fileI.c_str());
     dxf->setDebug(DRW::DEBUG);
     bool success = dxf->read(this, false);
     delete dxf;

     return success;
     }
  else if (fileExt == "DWG") {
     //loads dwg
     dwgR *dwg = new dwgR(fileI.c_str());
     bool success = dwg->read(this, false);
     delete dwg;

     return success;
     }
  std::cout << "file extension can be dxf or dwg" << std::endl;

  return false;
  }


void DxfHelper::dump(DRW_Entity *e) {
  switch (e->type()) {
    case DRW::E3DFACE:
         std::cout << "\t>>> entity type:    E3DFace" << std::endl;
         break;
    case DRW::ARC: {
//       std::cout << "entity type: Arc" << std::endl;
         DRW_Coord c = ((DRW_Arc*) e)->basePoint;
         double r = ((DRW_Arc*) e)->radious;
         double sa = ((DRW_Arc*) e)->staangle;
         double ea = ((DRW_Arc*) e)->endangle;
         int ccw = ((DRW_Arc*) e)->isccw;

         std::cout << std::fixed << "\tarc: (" << c.x << "/" << c.y << "/" << c.z
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

         std::cout << std::fixed << "\tcircle: (" << c.x << "/" << c.y << "/"
                   << c.z << ") with radius: " << r << std::endl;
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
         DRW_Coord end = ((DRW_Line*) e)->secPoint;

         if (start.z != end.z) {
            std::cout << std::fixed << "\t\tinvalid line from (" << start.x << "/"
                      << start.y << "/" << start.z << ")   to =>   (" << end.x
                      << "/" << end.y << "/" << end.z << ")" << std::endl;
            }
         else {
            std::cout << std::fixed << "\tline from (" << start.x << "/" << start.y
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


bool DxfHelper::alreadyContained(DRW_Entity *e, std::vector<DRW_Entity*> &list) {
  for (unsigned i = 0; i < list.size(); ++i) {
      DRW_Entity *pChk = list.at(i);

      if (*pChk == *e) return true;
      }
  return false;
  }


void DxfHelper::separateLayers() {
  std::vector<DRW_Entity*> elements;

  for (std::list<DRW_Entity*>::const_iterator it = rData.mBlock->ent.begin()
     ; it != rData.mBlock->ent.end()
     ; ++it) {
      const DRW_Entity *e = *it;

      if (e->type() == DRW::LINE) {
         DRW_Line *l = dynamic_cast<DRW_Line*>(*it);

         if (l->basePoint.z != l->secPoint.z) continue;
         }
      if (!alreadyContained(*it, elements)) {
         elements.push_back(*it);
         }
      }
  for (std::vector<DRW_Entity*>::const_iterator it = elements.begin()
     ; it != elements.end()
     ; ++it) {
      DRW_Entity *e = *it;

      switch (e->type()) {
        case DRW::POINT:
             std::cout << "\t>>> entity type:    Point" << std::endl;
             break;
        case DRW::LINE: {
             DRW_Coord start = ((DRW_Line*) e)->basePoint;
             DRW_Coord end   = ((DRW_Line*) e)->secPoint;

             if (start.z == end.z) {          // handle horizontal lines only!
                rData.groupedEntities[start.z].push_back(new dx_Entity(e));
                }
             } break;
        case DRW::LWPOLYLINE:
             std::cout << "\t>>> TODO: entity type:    LWPolyLine" << std::endl;
             break;
        case DRW::SPLINE:
             std::cout << "\t>>> TODO: entity type:    Spline" << std::endl;
             break;
        case DRW::ARC: {
             DRW_Coord c = ((DRW_Arc*) e)->basePoint;

             rData.groupedEntities[c.z].push_back(new dx_Entity(e));
             } break;
        case DRW::CIRCLE: {
             DRW_Coord c = ((DRW_Circle*) e)->basePoint;

             rData.groupedEntities[c.z].push_back(new dx_Entity(e));
             } break;
        case DRW::ELLIPSE:
             std::cout << "\t>>> TODO: entity type:    Ellipse" << std::endl;
             break;
        default:
             std::cout << "<<< UNSUPPORTED TYPE: " << e->type() << std::endl;
        }
      }
  }


void DxfHelper::genShapes(AbstractUIHelper& cbUtil) {
  for (std::map<double, std::vector<dx_Entity*>>::iterator it = rData.groupedEntities.begin()
     ; it != rData.groupedEntities.end()
     ; ++it) {
      double curLayer = (*it).first;

      rData.levels.push_back(curLayer);
      cbUtil.addLayer(curLayer);
      std::vector<dx_Entity*> entities = (*it).second;

//      std::cout << "\n\nelements at layer: " << curLayer << std::endl;
      for (std::vector<dx_Entity*>::iterator iE = entities.begin()
         ; iE != entities.end()
         ; ++iE) {
          dx_Entity *pE = *iE;

          pE->layer = curLayer;
//          dump(pE->entity);
          switch (pE->entity->type()) {
            case DRW::POINT: {
                 DRW_Point *p = dynamic_cast<DRW_Point*>(pE->entity);

                 pE->shape = OCCT::draw_3d_point({ p->basePoint.x
                                                 , p->basePoint.y
                                                 , p->basePoint.z });
                 } break;
            case DRW::LINE: {
                 DRW_Line *p = dynamic_cast<DRW_Line*>(pE->entity);

                 pE->shape = OCCT::draw_3d_line({ p->basePoint.x
                                                , p->basePoint.y
                                                , p->basePoint.z }
                                              , { p->secPoint.x
                                                , p->secPoint.y
                                                , p->secPoint.z });
                 } break;
            case DRW::LWPOLYLINE: {
                 DRW_LWPolyline *p = dynamic_cast<DRW_LWPolyline*>(pE->entity);
                 std::vector<gp_Pnt> points;

                 for (unsigned int i = 0; i < p->vertlist.size(); ++i) {
                     points.push_back({ p->vertlist.front()->x
                                      , p->vertlist.front()->y
                                      , 0 });
                     }
                 pE->shape = OCCT::draw_3d_line_wire(points);
                 } break;
            case DRW::SPLINE: {
                 DRW_Spline *p = dynamic_cast<DRW_Spline*>(pE->entity);
                 std::vector<gp_Pnt> points;

                 for (unsigned int i = 0; i < p->controllist.size(); ++i) {
                     points.push_back({ p->controllist.at(i)->x
                                      , p->controllist.at(i)->y
                                      , p->controllist.at(i)->z });
                     pE->shape = OCCT::draw_3d_spline(points, 5);
                     }
                 } break;
            case DRW::ARC: {
                 DRW_Arc *p = dynamic_cast<DRW_Arc*>(pE->entity);

                 pE->shape = OCCT::draw_2d_acad_arc({ p->center().x
                                                    , p->center().y
                                                    , p->center().z }
                                                  , p->radius()
                                                  , p->startAngle()
                                                  , p->endAngle());
                 } break;
            case DRW::CIRCLE: {
                 DRW_Circle *p = dynamic_cast<DRW_Circle*>(pE->entity);

                 pE->shape = OCCT::draw_2d_circle({ p->basePoint.x
                                                  , p->basePoint.y
                                                  , p->basePoint.z }
                                                , p->radious);
                 } break;
            case DRW::ELLIPSE: {
                 DRW_Ellipse *p = dynamic_cast<DRW_Ellipse*>(pE->entity);

                 pE->shape = OCCT::draw_2d_ellipse({ p->basePoint.x
                                                   , p->basePoint.y
                                                   , p->basePoint.z }
                                                 , { p->secPoint.x
                                                   , p->secPoint.y
                                                   , p->secPoint.z }
                                                 , p->staparam
                                                 , p->endparam
                                                 , p->ratio);
                 } break;
            default:
                 break;
            }
         }
     }
  }
