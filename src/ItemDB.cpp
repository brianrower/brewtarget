#include "ItemDB.h"
#include "database.h"

const QString kNameColumn("name");

ItemDB::ItemDB()
{

}

void ItemDB::setName(const QString& name)
{
   update(kNameColumn, name);
}

QString ItemDB::getName() const
{
   return getColumn(kNameColumn).toString();
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
