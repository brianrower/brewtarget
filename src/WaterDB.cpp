#include "WaterDB.h"

const QString WaterDB::kAmountColumn("amount");
const QString WaterDB::kCalciumColumn("calcium");
const QString WaterDB::kBicarbonateColumn("bicarbonate");
const QString WaterDB::kChlorideColumn("chloride");
const QString WaterDB::kSodiumColumn("sodium");
const QString WaterDB::kMagnesiumColumn("magnesium");
const QString WaterDB::kPhColumn("ph");
const QString WaterDB::kSulfateColumn("sulfate");
const QString WaterDB::kNotesColumn("notes");

WaterDB::WaterDB():
   ItemDB(Brewtarget::WATERTABLE, Brewtarget::NOTABLE)
{

}

