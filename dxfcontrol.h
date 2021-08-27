#ifndef DXFCONTROL_H
#define DXFCONTROL_H
#include <abstract3dcontrol.h>
#include <dx_data.h>

class AbstractUIHelper;

class DxfController : public Abstract3DControl
{
public:
  DxfController(occ::OpenCascade& view, AbstractUIHelper& helper, dx_data* model);

  virtual bool loadFile(const std::string& fileName);
  virtual void drawModel();
  virtual void setActiveLayer(int layer);

private:
  dx_data* m;
  };
#endif // DXFCONTROL_H
