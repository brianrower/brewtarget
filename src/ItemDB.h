#pragma once

#include <QObject>
#include "brewtarget.h"

class ItemDB: public QObject
{
   Q_OBJECT

public:
   ItemDB();
   virtual void setName(const QString& name);
   QString getName() const;

protected:
   void updateColumn(const QString& colName, const QVariant& value);
   QVariant getColumn( const QString& colName ) const;

   void updateInventoryColumn( const QString& colName, const QVariant& value );
   QVariant getInventoryColumn( const QString& colName ) const;

   QString _tableName;
   int _id; //Referenced as "key" other places

   QString _inventoryTable;
   int _inventoryId;

};

