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
#ifndef DX_DATA_H
#define DX_DATA_H
#include <drw_entities.h>
#include <drw_header.h>
#include <drw_objects.h>
#include <opencascade/AIS_Shape.hxx>
#include <QString>
#include <QListWidgetItem>
#include <exception>


//class to store image data and path from DRW_ImageDef
class dx_ifaceImg: public DRW_Image
{
public:
  dx_ifaceImg() {
    }
  dx_ifaceImg(const DRW_Image &p)
   : DRW_Image(p) {
    }
 ~dx_ifaceImg() {
    }

  std::string path;          //stores the image path
  };


//container class to store entites.
class dx_ifaceBlock: public DRW_Block
{
public:
  dx_ifaceBlock() {
    }
  dx_ifaceBlock(const DRW_Block &p)
   : DRW_Block(p) {
    }
 ~dx_ifaceBlock() {
    for (std::list<DRW_Entity*>::const_iterator it = ent.begin()
       ; it != ent.end()
       ; ++it)
        delete *it;
    }
  std::list<DRW_Entity*> ent;          //stores the entities list
  };


class dx_Entity
{
public:
  dx_Entity(DRW_Entity *e)
   : entity(e)
   , layer(0)
   , selected(false) {
    }
  QString typeName() const;

  DRW_Entity*       entity; //
  double            layer; //
  bool              selected; //
  Handle(AIS_Shape) shape;
  };


class ListItem: public QListWidgetItem
{
public:
  ListItem(dx_Entity &e)
   : rE(e) {
    }
  virtual QVariant data(int role) const {
    if (role == Qt::DisplayRole) return rE.typeName();
    return QVariant();
    }
  void dump() const;
  void setSelected(bool selected = true) {
    rE.selected = selected;
    }

private:
  dx_Entity& rE;
  };


//container class to store full dwg/dxf data.
class dx_data
{
public:
  dx_data()
   : mBlock(NULL), level(0) {
    }
 ~dx_data() {
    reset();
    }
  void reset();
  void addBlock(dx_ifaceBlock *b) {
    blocks.push_back(mBlock = b);
    }
  void addEntity(DRW_Entity *e) {
    if (!mBlock) {
       std::cout << "OUPS - no block to save entities!!!" << std::endl;
       exit(-2);
       }
    mBlock->ent.push_back(e);
    }
  void setLevel(double l) {
    try {
        level = l;
        std::map<double, std::vector<dx_Entity*>>::iterator iter = groupedEntities.find(level);
        curElements = (*iter).second;
        }
    catch (std::out_of_range e) {
        std::cerr << e.what() << std::endl;
        }
  }
  DRW_Header                headerC;    // stores a copy of the header vars
  std::list<DRW_LType>      lineTypes;  // stores a copy of all line types
  std::list<DRW_Layer>      layers;     // stores a copy of all layers
  std::list<DRW_Dimstyle>   dimStyles;  // stores a copy of all dimension styles
  std::list<DRW_Vport>      VPorts;     // stores a copy of all vports
  std::list<DRW_Textstyle>  textStyles; // stores a copy of all text styles
  std::list<DRW_AppId>      appIds;     // stores a copy of all line types
  std::list<dx_ifaceBlock*> blocks;     // stores a copy of all blocks and the entities in it
  std::list<dx_ifaceImg*>   images;     // temporary list to find images for link with DRW_ImageDef. Do not delete it!!
  std::vector<double>       levels;
  std::map<double, std::vector<dx_Entity*>> groupedEntities;
  std::vector<dx_Entity*>   curElements;
  dx_ifaceBlock*            mBlock;     // container to store model entities

private:
  double level;
  };
#endif // DX_DATA_H
