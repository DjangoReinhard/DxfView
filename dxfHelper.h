/*****************************************************************************
 **                                                                         **
 ** Copyright (C) 2015 José F. Soriano, rallazz@gmail.com                   **
 **                                                                         **
 ** This library is free software, licensed under the terms of the GNU      **
 ** General Public License as published by the Free Software Foundation,    **
 ** either version 2 of the License, or (at your option) any later version. **
 ** You should have received a copy of the GNU General Public License       **
 ** along with this program.  If not, see <http://www.gnu.org/licenses/>.   **
 *****************************************************************************/
#ifndef DXFHELPER_H
#define DXFHELPER_H

#include <drw_interface.h>
#include <libdxfrw.h>
#include "dx_data.h"
#include <vector>

class AbstractUIHelper;

class DxfHelper: public DRW_Interface
{
public:
  DxfHelper(dx_data &data)
      : rData(data) {
    rData.blocks.push_back(data.mBlock);
  }
  ~DxfHelper() {
  }
  bool fileImport(const std::string &fileI);
  void separateLayers();
  void genShapes(AbstractUIHelper&);
  void dump(DRW_Entity *e);
  bool alreadyContained(DRW_Entity*, std::vector<DRW_Entity*>&);

  void addHeader(const DRW_Header *d) {
    rData.headerC = *d;
  }
  //tables
  virtual void addLType(const DRW_LType &d) {
    rData.lineTypes.push_back(d);
  }
  virtual void addLayer(const DRW_Layer &d) {
    rData.layers.push_back(d);
  }
  virtual void addDimStyle(const DRW_Dimstyle &d) {
    rData.dimStyles.push_back(d);
  }
  virtual void addVport(const DRW_Vport &d) {
    rData.VPorts.push_back(d);
  }
  virtual void addTextStyle(const DRW_Textstyle &d) {
    rData.textStyles.push_back(d);
  }
  virtual void addAppId(const DRW_AppId &d) {
    rData.appIds.push_back(d);
  }
  //blocks
  virtual void addBlock(const DRW_Block &d) {
    rData.addBlock(new dx_ifaceBlock(d));
  }
  virtual void endBlock() {
  }
  virtual void setBlock(const int /*handle*/) {
  }
  //entities
  virtual void addPoint(const DRW_Point &d) {
    rData.addEntity(new DRW_Point(d));
  }
  virtual void addLine(const DRW_Line &d) {
    rData.addEntity(new DRW_Line(d));
  }
  virtual void addRay(const DRW_Ray &d) {
    rData.addEntity(new DRW_Ray(d));
  }
  virtual void addXline(const DRW_Xline &d) {
    rData.addEntity(new DRW_Xline(d));
  }
  virtual void addArc(const DRW_Arc &d) {
    rData.addEntity(new DRW_Arc(d));
  }
  virtual void addCircle(const DRW_Circle &d) {
    rData.addEntity(new DRW_Circle(d));
  }
  virtual void addEllipse(const DRW_Ellipse &d) {
    rData.addEntity(new DRW_Ellipse(d));
  }
  virtual void addLWPolyline(const DRW_LWPolyline &d) {
    rData.addEntity(new DRW_LWPolyline(d));
  }
  virtual void addPolyline(const DRW_Polyline &d) {
    rData.addEntity(new DRW_Polyline(d));
  }
  virtual void addSpline(const DRW_Spline *d) {
    rData.addEntity(new DRW_Spline(*d));
  }
  // ¿para que se usa?
  virtual void addKnot(const DRW_Entity &d) {
  }
  virtual void addInsert(const DRW_Insert &d) {
    rData.addEntity(new DRW_Insert(d));
  }
  virtual void addTrace(const DRW_Trace &d) {
    rData.addEntity(new DRW_Trace(d));
  }
  virtual void add3dFace(const DRW_3Dface &d) {
    rData.addEntity(new DRW_3Dface(d));
  }
  virtual void addSolid(const DRW_Solid &d) {
    rData.addEntity(new DRW_Solid(d));
  }
  virtual void addMText(const DRW_MText &d) {
    rData.addEntity(new DRW_MText(d));
  }
  virtual void addText(const DRW_Text &d) {
    rData.addEntity(new DRW_Text(d));
  }
  virtual void addDimAlign(const DRW_DimAligned *d) {
    rData.addEntity(new DRW_DimAligned(*d));
  }
  virtual void addDimLinear(const DRW_DimLinear *d) {
    rData.addEntity(new DRW_DimLinear(*d));
  }
  virtual void addDimRadial(const DRW_DimRadial *d) {
    rData.addEntity(new DRW_DimRadial(*d));
  }
  virtual void addDimDiametric(const DRW_DimDiametric *d) {
    rData.addEntity(new DRW_DimDiametric(*d));
  }
  virtual void addDimAngular(const DRW_DimAngular *d) {
    rData.addEntity(new DRW_DimAngular(*d));
  }
  virtual void addDimAngular3P(const DRW_DimAngular3p *d) {
    rData.addEntity(new DRW_DimAngular3p(*d));
  }
  virtual void addDimOrdinate(const DRW_DimOrdinate *d) {
    rData.addEntity(new DRW_DimOrdinate(*d));
  }
  virtual void addLeader(const DRW_Leader *d) {
    rData.addEntity(new DRW_Leader(*d));
  }
  virtual void addHatch(const DRW_Hatch *d) {
    rData.addEntity(new DRW_Hatch(*d));
  }
  virtual void addViewport(const DRW_Viewport &d) {
    rData.addEntity(new DRW_Viewport(d));
  }
  virtual void addImage(const DRW_Image *d) {
    dx_ifaceImg *img = new dx_ifaceImg(*d);

    rData.addEntity(new dx_ifaceImg(*d));
    rData.images.push_back(img);
  }
  virtual void linkImage(const DRW_ImageDef *d) {
    duint32 handle = d->handle;
    std::string path(d->name);

    for (std::list<dx_ifaceImg*>::iterator it = rData.images.begin();
        it != rData.images.end(); ++it) {
      if ((*it)->ref == handle) {
        dx_ifaceImg *img = *it;
        img->path = path;
      }
    }
  }

//writer part, not implemented
  virtual void addComment(const char* /*comment*/) {
  }
  virtual void writeHeader(DRW_Header &d) {
  }
  virtual void writeBlocks() {
  }
  virtual void writeBlockRecords() {
  }
  virtual void writeEntities() {
  }
  virtual void writeLTypes() {
  }
  virtual void writeLayers() {
  }
  virtual void writeTextstyles() {
  }
  virtual void writeVports() {
  }
  virtual void writeDimstyles() {
  }
  virtual void writeAppId() {
  }

  dx_data& rData;
};

#endif
