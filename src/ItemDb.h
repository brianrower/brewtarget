#ifndef ITEMDB_H
#define ITEMDB_H

#include "brewtarget.h"

class ItemDb
{
   Q_OBJECT
public:
   ItemDb();
   virtual void setName(const QString& name);

signals:
   void nameChanged(QString newName);

protected:
   void update(const QString& colName, const QString& value);

   Brewtarget::DBTable _tableName;
   int _id; //Referenced as "key" other places
};

#endif // ITEMDB_H
