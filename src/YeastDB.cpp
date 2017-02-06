#include "YeastDB.h"

const QString YeastDB::kLaboratoryColumn("laboratory");
const QString YeastDB::kProductIDColumn("product_id");
const QString YeastDB::kNotesColumn("notes");
const QString YeastDB::kBestForColumn("best_for");
const QString YeastDB::kAmountColumn("amount");
const QString YeastDB::kMinTempColumn("min_temperature");
const QString YeastDB::kMaxTempColumn("max_temperature");
const QString YeastDB::kAttenuationColumn("attenuation");
const QString YeastDB::kQuantityColumn("quanta");
const QString YeastDB::kTimesCulturedColumn("times_cultured");
const QString YeastDB::kMaxReuseColumn("max_reuse");
const QString YeastDB::kAddToSecondaryColumn("add_to_secondary");
const QString YeastDB::kAmtIsWeightColumn("amount_is_weight");
const QString YeastDB::kFormColumn("form");
const QString YeastDB::kFlocculationColumn("flocculation");
const QString YeastDB::kTypeColumn("ytype");

YeastDB::YeastDB():
   ItemDB(Brewtarget::YEASTTABLE, Brewtarget::YEASTINVTABLE)
{

}

