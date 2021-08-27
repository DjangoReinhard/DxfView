/*
 * dx_data.cpp
 *
 *  Created on: 03.08.2021
 *      Author: django
 */
#include "dx_data.h"
#define tr(s)   s

void dx_data::reset() {
  headerC.vars.clear();
  lineTypes.clear();
  layers.clear();
  dimStyles.clear();
  VPorts.clear();
  textStyles.clear();
  appIds.clear();
  for (std::list<dx_ifaceBlock*>::const_iterator it = blocks.begin();
      it != blocks.end(); ++it)
    if (*it) delete *it;

  for (std::list<dx_ifaceImg*>::const_iterator it = images.begin();
      it != images.end(); ++it)
    if (*it) delete *it;
  groupedEntities.clear();
}

QString dx_Entity::typeName() const {
  if (!entity) return QString(tr("Invalid"));
  switch (entity->type()) {
    case DRW::E3DFACE:
      return QString(tr("E3DFace"));
    case DRW::ARC:
      return QString(tr("Arc"));
    case DRW::BLOCK:
      return QString(tr("Block"));
    case DRW::CIRCLE:
      return QString(tr("Circle"));
    case DRW::DIMENSION:
      return QString(tr("Dimension"));
    case DRW::DIMALIGNED:
      return QString(tr("DimAligned"));
    case DRW::DIMLINEAR:
      return QString(tr("DimLinear"));
    case DRW::DIMRADIAL:
      return QString(tr("DimRadial"));
    case DRW::DIMDIAMETRIC:
      return QString(tr("DimDiametric"));
    case DRW::DIMANGULAR:
      return QString(tr("DimAngular"));
    case DRW::DIMANGULAR3P:
      return QString(tr("DimAngular3P"));
    case DRW::DIMORDINATE:
      return QString(tr("DimOrdinate"));
    case DRW::ELLIPSE:
      return QString(tr("Ellipse"));
    case DRW::HATCH:
      return QString(tr("Hatch"));
    case DRW::IMAGE:
      return QString(tr("Image"));
    case DRW::INSERT:
      return QString(tr("Insert"));
    case DRW::LEADER:
      return QString(tr("Leader"));
    case DRW::LINE:
      return QString(tr("Line"));
    case DRW::LWPOLYLINE:
      return QString(tr("LwPolyLine"));
    case DRW::MTEXT:
      return QString(tr("MText"));
    case DRW::POINT:
      return QString(tr("Point"));
    case DRW::POLYLINE:
      return QString(tr("PolyLine"));
    case DRW::RAY:
      return QString(tr("Ray"));
    case DRW::SOLID:
      return QString(tr("Solid"));
    case DRW::SPLINE:
      return QString(tr("Spline"));
    case DRW::TEXT:
      return QString(tr("Text"));
    case DRW::TRACE:
      return QString(tr("Trace"));
    case DRW::UNDERLAY:
      return QString(tr("Underlay"));
    case DRW::VERTEX:
      return QString(tr("Vertex"));
    case DRW::VIEWPORT:
      return QString(tr("ViewPort"));
    case DRW::XLINE:
      return QString(tr("XLine"));
    default:
      return QString(tr("Unknown/Unsupported"));
  }
}
