#include "dxfcontrol.h"
#include "dxfHelper.h"
#include <QDebug>


DxfController::DxfController(occ::OpenCascade& view, AbstractUIHelper& auh, dx_data* model)
 : Abstract3DControl(view, auh)
 , m(model) {
  }


bool DxfController::loadFile(const std::string &fileName) {
  DxfHelper dh(*m);
  bool      ok = dh.fileImport(fileName);

  if (ok) {
     dh.separateLayers();
     dh.genShapes(auh);
     }
  return ok;
  }


void DxfController::setActiveLayer(int layer) {
  double level = 0;

  try {
      level = m->levels.at(layer);
      activeLayer = level;
      }
  catch (std::out_of_range e) {
      qDebug() << e.what();
      }
  m->setLevel(activeLayer);

  for (unsigned i = 0; i < m->curElements.size(); ++i) {
      dx_Entity *pE = m->curElements.at(i);
      ListItem *newItem = new ListItem(*pE);

      auh.addListEntry(newItem);
      }
  drawModel();
  }


void DxfController::drawModel() {
  v.erase_all();
  for (std::map<double, std::vector<dx_Entity*>>::iterator it = m->groupedEntities.begin()
     ; it != m->groupedEntities.end()
     ; ++it) {
      std::vector<dx_Entity*> entities = (*it).second;

      for (unsigned i = 0; i < entities.size(); ++i) {
          dx_Entity *pE = entities.at(i);
          if (pE->layer == activeLayer) {
             if (pE->selected) {
                // use predefined color of opencascade
                v.set_shape_selected(pE->shape);
                }
             else {
                // oce/Quantity_NameOfColor.hxx
                OCCT::colorize(pE->shape, Quantity_NOC_ROYALBLUE, 1);
//                OCCT::colorize(pE->shape, Quantity_NOC_BLUE, 1);
//                OCCT::colorize(pE->shape, Quantity_NOC_CYAN, 1);
//                OCCT::colorize(pE->shape, Quantity_NOC_RED, 1);
//                OCCT::colorize(pE->shape, Quantity_NOC_PURPLE2, 1);
                }
             }
          else {
             OCCT::colorize(pE->shape, Quantity_NOC_GRAY6, 1);
             }
          v.show_shape(pE->shape);
          }
      }
  }
