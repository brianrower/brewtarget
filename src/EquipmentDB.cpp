#include "EquipmentDB.h"

const QString EquipmentDB::kBoilSizeColumn("boil_size");
const QString EquipmentDB::kBatchSizeColumn("batch_size");
const QString EquipmentDB::kTunVolumeColumn("tun_volume");
const QString EquipmentDB::kTunWeightColumn("tun_weight");
const QString EquipmentDB::kTunSpecificHeatColumn("tun_specific_heat");
const QString EquipmentDB::kTopUpWaterColumn("top_up_water");
const QString EquipmentDB::kTrubChillerLossColumn("trub_chiller_loss");
const QString EquipmentDB::kEvaporationRateColumn("evap_rate");
const QString EquipmentDB::kRealEvaporationRateColumn("real_evap_rate");
const QString EquipmentDB::kBoilTimeColumn("boil_time");
const QString EquipmentDB::kCalcBoilVolumeColumn("calc_boil_volume");
const QString EquipmentDB::kLauterDeadspaceColumn("lauter_deadspace");
const QString EquipmentDB::kTopUpKettleColumn("top_up_kettle");
const QString EquipmentDB::kHopUtilizationColumn("hop_utilization");
const QString EquipmentDB::kNotesColumn("notes");
const QString EquipmentDB::kAbsorptionColumn("absorption");
const QString EquipmentDB::kBoilingPointColumn("boiling_point");

EquipmentDB::EquipmentDB():
   ItemDB(Brewtarget::EQUIPTABLE, Brewtarget::NOTABLE)
{
}

