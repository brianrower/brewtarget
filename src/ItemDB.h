#pragma once

#include "brewtarget.h"

class ItemDB
{
   Q_OBJECT

public:
   ItemDB();
   virtual void setName(const QString& name);

signals:
   void nameChanged(QString newName);

protected:
   void update(const QString& colName, const QString& value);

   Brewtarget::DBTable _tableName;
   int _id; //Referenced as "key" other places
};

