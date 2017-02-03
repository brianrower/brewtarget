#include "BrewNoteDB.h"


const QString BrewNoteDB::kBrewDateColumn("brewDate");
const QString BrewNoteDB::kFermentDateColumn("fermentDate");
const QString BrewNoteDB::kNotesColumn("notes");
const QString BrewNoteDB::kSpecificGravityColumn("sg");
const QString BrewNoteDB::kVolumeIntoBoilColumn("volume_into_bk");
const QString BrewNoteDB::kOriginalGravityColumn("og");
const QString BrewNoteDB::kVolumeIntoFermenterColumn("volume_into_fermenter");
const QString BrewNoteDB::kFinalGravityColumn("fg");
const QString BrewNoteDB::kProjectedPointsColumn("projected_points");
const QString BrewNoteDB::kProjectedFermentationPointsColumn("projected_ferm_points");
const QString BrewNoteDB::kABVColumn("abv");
const QString BrewNoteDB::kEfficiencyIntoBoilColumn("eff_into_bk");
const QString BrewNoteDB::kBrewhouseEfficiencyColumn("brewhouse_eff");
const QString BrewNoteDB::kStrikeTempColumn("strike_temp");
const QString BrewNoteDB::kMashFinalTempColumn("mash_final_temp");
const QString BrewNoteDB::kPostBoilVolumeColumn("post_boil_volume");
const QString BrewNoteDB::kPitchTempColumn("pitch_temp");
const QString BrewNoteDB::kFinalVolumeColumn("final_volume");
const QString BrewNoteDB::kProjectedBoilGravityColumn("projected_boil_grav");
const QString BrewNoteDB::kProjectedVolumeIntoBoilColumn("projected_vol_into_bk");
const QString BrewNoteDB::kProjectedStrikeTempColumn("projected_strike_temp");
const QString BrewNoteDB::kProjectedMashFinishTempColumn("projected_mash_fin_temp");
const QString BrewNoteDB::kProjectedOGColumn("projected_og");
const QString BrewNoteDB::kProjectedVolumeIntoFermenterColumn("projected_vol_into_ferm");
const QString BrewNoteDB::kProjectedFGColumn("projected_fg");
const QString BrewNoteDB::kProjectedEfficiencyColumn("projected_eff");
const QString BrewNoteDB::kProjectedABVColumn("projected_abv");
const QString BrewNoteDB::kProjectedAttenuationColumn("projected_atten");
const QString BrewNoteDB::kBoilOffColumn("boil_off");

BrewNoteDB::BrewNoteDB():
      ItemDB(Brewtarget::BREWNOTETABLE, Brewtarget::NOTABLE)
{

}

