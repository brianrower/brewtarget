#pragma once

#include <QObject>
#include <QString>
#include "brewtarget.h"

class ItemDB
{

public:
   ItemDB(Brewtarget::DBTable tableName, Brewtarget::DBTable inventoryTableName);

   void updateColumn(const QString& colName, const QVariant& value);
   QVariant getColumn( const QString& colName ) const;

   void updateInventoryColumn( const QString& colName, const QVariant& value );
   QVariant getInventoryColumn( const QString& colName ) const;

   void remove();

   static const QString kNameColumn;
   static const QString kDeletedColumn;
   static const QString kDisplayColumn;
   static const QString kFolderColumn;

protected:
   Brewtarget::DBTable _table;
   int _id; //Referenced as "key" other places

   Brewtarget::DBTable _inventoryTable;
   int _inventoryId;

};

