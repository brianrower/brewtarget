#include "ItemDB.h"
#include "database.h"

ItemDB::ItemDB()
{

}

void ItemDB::setName(const QString& name) {
   update("name", name);
   emit nameChanged(name);
}

void ItemDB::update(const QString& colName, const QString& value) {
   Database::instance().updateEntry( _table, _key, colName, value);
}
