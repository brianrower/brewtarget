#include "MashDB.h"

const QString MashDB::kGrainTempColumn("grain_temp");
const QString MashDB::kNotesColumn("notes");
const QString MashDB::kTunTempColumn("tun_temp");
const QString MashDB::kSpargeTempColumn("sparge_temp");
const QString MashDB::kEquipmentAdjustColumn("equip_adjust");
const QString MashDB::kPhColumn("ph");
const QString MashDB::kTunWeightColumn("tun_weight");
const QString MashDB::kTunSpecificHeatColumn("tun_specific_heat");

MashDB::MashDB():
   ItemDB(Brewtarget::MASHTABLE, Brewtarget::NOTABLE)
{

}

