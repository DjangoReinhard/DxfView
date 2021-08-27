/*
 * test file to parse dxf file ...
 *
 */
#include <iostream>
#include <algorithm>
#include <map>
#include <vector>
#include "dx_data.h"
#include <drw_entities.h>
#include <dxfHelper.h>

void usage() {
  std::cout << "please gimme a filename" << std::endl;
}

void dump(DRW_Entity *e) {
  switch (e->eType) {
    case DRW::E3DFACE:
      std::cout << "\t>>> entity type:    E3DFace" << std::endl;
      break;
    case DRW::ARC: {
//             std::cout << "entity type: Arc" << std::endl;
      DRW_Coord c = ((DRW_Arc*) e)->basePoint;
      double r = ((DRW_Arc*) e)->radious;
      double sa = ((DRW_Arc*) e)->staangle;
      double ea = ((DRW_Arc*) e)->endangle;
      int ccw = ((DRW_Arc*) e)->isccw;

      std::cout << std::fixed << "arc: (" << c.x << "/" << c.y << "/" << c.z
                << ") with radius: " << r << "  start-angle: " << sa
                << "  end-angle: " << ea << "  dir: " << (ccw ? "ccw" : "cw")
                << std::endl;
    }
      break;
    case DRW::BLOCK:
      std::cout << "\t>>> entity type:    Block" << std::endl;
      break;
    case DRW::CIRCLE: {
//             std::cout << "entity type: Circle" << std::endl;
      DRW_Coord c = ((DRW_Circle*) e)->basePoint;
      double r = ((DRW_Circle*) e)->radious;

      std::cout << std::fixed << "circle: (" << c.x << "/" << c.y << "/" << c.z
                << ") with radius: " << r << std::endl;
    }
      break;
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
//             std::cout << "entity type: Line" << std::endl;
      DRW_Coord start = ((DRW_Line*) e)->basePoint;
      DRW_Coord end = ((DRW_Line*) e)->secPoint;

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
    }
      break;
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

void dump(std::multimap<double, DRW_Entity*> &m) {
  double oldLevel = -1;

  for (std::multimap<double, DRW_Entity*>::iterator it = m.begin();
      it != m.end(); ++it) {
    if ((*it).first != oldLevel) {
      oldLevel = (*it).first;

      std::cout << "\n\nelements at layer: " << oldLevel << std::endl;
    }
    DRW_Entity *e = (*it).second;

    dump(e);
  }
}

void dump(std::map<double, std::vector<DRW_Entity*>> &m) {
  for (std::map<double, std::vector<DRW_Entity*>>::iterator it = m.begin();
      it != m.end(); ++it) {
    double curLayer = (*it).first;
    std::vector<DRW_Entity*> entities = (*it).second;

    std::cout << "\n\nelements at layer: " << curLayer << std::endl;
    for (std::vector<DRW_Entity*>::iterator iE = entities.begin();
        iE != entities.end(); ++iE) {
      dump(*iE);
    }
  }
}

void separateLayers(std::multimap<double, DRW_Entity*> &m,
                    dx_ifaceBlock *block) {
  for (std::list<DRW_Entity*>::const_iterator it = block->ent.begin();
      it != block->ent.end(); ++it) {
    DRW_Entity *e = *it;

    switch (e->eType) {
      case DRW::E3DFACE:
        std::cout << "\t>>> entity type:    E3DFace" << std::endl;
        break;
      case DRW::ARC: {
        DRW_Coord c = ((DRW_Arc*) e)->basePoint;

        m.insert(std::make_pair(c.z, e));
      }
        break;
      case DRW::BLOCK:
        std::cout << "\t>>> entity type:    Block" << std::endl;
        break;
      case DRW::CIRCLE: {
        DRW_Coord c = ((DRW_Circle*) e)->basePoint;

        m.insert(std::make_pair(c.z, e));
      }
        break;
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
        DRW_Coord start = ((DRW_Line*) e)->basePoint;
        DRW_Coord end = ((DRW_Line*) e)->secPoint;

        if (start.z == end.z) { // handle horizontal lines only!
          m.insert(std::make_pair(start.z, e));
        }
      }
        break;
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
    }
  }
}

void separateLayers(std::map<double, std::vector<DRW_Entity*>> &m,
                    dx_ifaceBlock *block) {
  for (std::list<DRW_Entity*>::const_iterator it = block->ent.begin();
      it != block->ent.end(); ++it) {
    DRW_Entity *e = *it;

    switch (e->eType) {
      case DRW::E3DFACE:
        std::cout << "\t>>> entity type:    E3DFace" << std::endl;
        break;
      case DRW::ARC: {
        DRW_Coord c = ((DRW_Arc*) e)->basePoint;

        m[c.z].push_back(e);
      }
        break;
      case DRW::BLOCK:
        std::cout << "\t>>> entity type:    Block" << std::endl;
        break;
      case DRW::CIRCLE: {
        DRW_Coord c = ((DRW_Circle*) e)->basePoint;

        m[c.z].push_back(e);
      }
        break;
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
        DRW_Coord start = ((DRW_Line*) e)->basePoint;
        DRW_Coord end = ((DRW_Line*) e)->secPoint;

        if (start.z == end.z) { // handle horizontal lines only!
          m[start.z].push_back(e);
        }
      }
        break;
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
    }
  }
}

#ifdef NO_QT_MAIN
int main(int cArgs, char** argv) {
  if (cArgs < 2) {
     usage();
     return -1;
     }
  bool        badState = false;
  std::string fileName = argv[1];
  dx_data     fData;
  dx_iface*   input = new dx_iface();

  badState = input->fileImport(fileName, &fData);
  if (!badState) {
     std::cout << "Error reading file " << fileName << std::endl;
     return -2;
     }
//  dump(input->currentBlock);
#ifdef REDNOSE
  std::multimap<double, DRW_Entity*> layers; // = std::multimap<double, DRW_Entity*>();

  separateLayers(layers, input->currentBlock);
  dump(layers);
#else
  std::map<double, std::vector<DRW_Entity*>> layers;

  separateLayers(layers, input->currentBlock);
  dump(layers);
#endif
  delete input;

  return 0;
  }
#endif
