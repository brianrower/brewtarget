#include "ItemDB.h"
#include "database.h"

const QString kNameColumn("name");
const QString kDeletedColumn("deleted");
const QString kDisplayColumn("display");
const QString kFolderColumn("folder");

ItemDB::ItemDB(Brewtarget::DBTable table, Brewtarget::DBTable inventoryTable):
      _table(table),
      _inventoryTable(inventoryTable)
{

}

void ItemDB::setName(const QString& name)
{
   updateColumn(kNameColumn, name);
}

QString ItemDB::getName() const
{
   return getColumn(kNameColumn).toString();
}

void ItemDB::setDeleted(bool isDeleted)
{
   updateColumn(kDeletedColumn, isDeleted ? Brewtarget::dbTrue() : Brewtarget::dbFalse());
}

bool ItemDB::isDeleted() const
{
   return getColumn(kDeletedColumn).toBool();
}

void ItemDB::setDisplay(bool display)
{
   updateColumn(kDisplayColumn, display ? Brewtarget::dbTrue() : Brewtarget::dbFalse());
}

bool ItemDB::getDisplay() const
{
   return getColumn(kDisplayColumn).toBool();
}

void ItemDB::setFolder(const QString& folder)
{
   updateColumn(kFolderColumn, folder);
}

QString ItemDB::getFolder() const
{
   return getColumn(kFolderColumn);
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
