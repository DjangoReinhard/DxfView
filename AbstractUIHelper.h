#ifndef ABSTRACTUIHELPER_H
#define ABSTRACTUIHELPER_H

class QListWidgetItem;

class AbstractUIHelper
{
public:
  virtual void addLayer(double l) = 0;
  virtual void addListEntry(QListWidgetItem* item) = 0;
  };
#endif // ABSTRACTUIHELPER_H
