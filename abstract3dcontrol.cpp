#include "abstract3dcontrol.h"


Abstract3DControl::Abstract3DControl(occ::OpenCascade& view, AbstractUIHelper& helper)
 : v(view)
 , auh(helper)
 , activeLayer(0) {
  }


Abstract3DControl::~Abstract3DControl() {
  v.erase_all();
  }
