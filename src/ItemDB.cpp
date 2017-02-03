#include "ItemDB.h"
#include "database.h"

const QString ItemDB::kNameColumn("name");
const QString ItemDB::kDeletedColumn("deleted");
const QString ItemDB::kDisplayColumn("display");
const QString ItemDB::kFolderColumn("folder");

ItemDB::ItemDB(Brewtarget::DBTable table, Brewtarget::DBTable inventoryTable):
      _table(table),
      _inventoryTable(inventoryTable)
{

}

void ItemDB::remove()
{
   Database::instance().deleteRecord(_table, _id);
}

void ItemDB::updateColumn(const QString& colName, const QVariant& value)
{
   Database::instance().updateEntry( _table, _id, colName, value);
}

QVariant ItemDB::getColumn( const QString& colName ) const
{
   return Database::instance().get( _table, _id, colName );
}

void ItemDB::updateInventoryColumn( const QString& colName, const QVariant& value )
{
    Database::instance().updateEntry( _inventoryTable, _inventoryId, colName, value);
}

QVariant ItemDB::getInventoryColumn( const QString& colName ) const
{
   return Database::instance().get( _inventoryTable, _inventoryId, colName );
}
