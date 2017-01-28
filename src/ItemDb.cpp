#include "ItemDb.h"
#include "database.h"

ItemDb::ItemDb()
{

}

void ItemDb::setName(const QString& name) {
   update("name", name);
   emit nameChanged(name);
}

void ItemDb::update(const QString& colName, const QString& value) {
   Database::instance().updateEntry( _table, _key, colName, value);
}
