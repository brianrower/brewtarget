#pragma once

#include <QObject>
#include "brewtarget.h"

class ItemDB
{

public:
   ItemDB(Brewtarget::DBTable tableName, Brewtarget::DBTable inventoryTableName);
   void setName(const QString& name);
   QString getName() const;

   void setDeleted(bool deleted);
   bool getDeleted() const;


   void setDisplay(bool display);
   bool getDisplay() const;

   void setFolder(const QString& folder);
   QString getFolder() const;

   void remove();

protected:
   void updateColumn(const QString& colName, const QVariant& value);
   QVariant getColumn( const QString& colName ) const;

   void updateInventoryColumn( const QString& colName, const QVariant& value );
   QVariant getInventoryColumn( const QString& colName ) const;

   Brewtarget::DBTable _table;
   int _id; //Referenced as "key" other places

   Brewtarget::DBTable _inventoryTable;
   int _inventoryId;

};

