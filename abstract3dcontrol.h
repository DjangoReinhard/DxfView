#ifndef ABSTRACT3DCONTROL_H
#define ABSTRACT3DCONTROL_H
#include <opencascade.h>
#include "AbstractUIHelper.h"


class Abstract3DControl
{
public:
  Abstract3DControl(occ::OpenCascade& view, AbstractUIHelper& auh);
  virtual ~Abstract3DControl();

  virtual bool loadFile(const std::string& fileName) = 0;
  virtual void drawModel() = 0;
  virtual void setActiveLayer(int layer) = 0;

protected:
  occ::OpenCascade& v;
  AbstractUIHelper& auh;
  int activeLayer;
  };
#endif // ABSTRACT3DCONTROL_H
