#include "MiscDB.h"

const QString MiscDB::kTypeColumn("mtype");
const QString MiscDB::kUseColumn("use");
const QString MiscDB::kAmountColumn("amount");
const QString MiscDB::kTimeColumn("time");
const QString MiscDB::kAmtIsWeightColumn("amount_is_weight");
const QString MiscDB::kUseForColumn("use_for");
const QString MiscDB::kNotesColumn("notes");

MiscDB::MiscDB():
   ItemDB(Brewtarget::MISCTABLE, Brewtarget::MISCINVTABLE)
{

}

