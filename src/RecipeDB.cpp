#include "RecipeDB.h"

const QString RecipeDB::kTypeColumn("type");
const QString RecipeDB::kBrewerColumn("brewer");
const QString RecipeDB::kBatchSizeColumn("batch_size");
const QString RecipeDB::kBoilSizeColumn("boil_size");
const QString RecipeDB::kBoilTimeColumn("boil_time");
const QString RecipeDB::kEfficiencyColumn("efficiency");
const QString RecipeDB::kAsstBrewerColumn("assistant_brewer");
const QString RecipeDB::kNotesColumn("notes");
const QString RecipeDB::kTasteNotesColumn("taste_notes");
const QString RecipeDB::kTasteRatingColumn("taste_rating");
const QString RecipeDB::kOGColumn("og");
const QString RecipeDB::kFGColumn("fg");
const QString RecipeDB::kFermStagesColumn("fermentation_stages");
const QString RecipeDB::kPrimaryAgeColumn("primary_age");
const QString RecipeDB::kPrimaryTempColumn("primary_temp");
const QString RecipeDB::kSecondaryAgeColumn("secondary_age");
const QString RecipeDB::kSecondaryTempColumn("secondary_temp");
const QString RecipeDB::kTertiaryAgeColumn("tertiary_age");
const QString RecipeDB::kTertiaryTempColumn("tertiary_temp");
const QString RecipeDB::kAgeColumn("age");
const QString RecipeDB::kAgeTempColumn("age_temp");
const QString RecipeDB::kDateColumn("date");
const QString RecipeDB::kCarbVolumeColumn("carb_volume");
const QString RecipeDB::kForcedCarbColumn("forced_carb");
const QString RecipeDB::kPrimingSugarNameColumn("priming_sugar_name");
const QString RecipeDB::kCarbonationTempColumn("carbonationTemp_c");
const QString RecipeDB::kPrimingSugarEquivColumn("priming_sugar_equiv");
const QString RecipeDB::kKegPrimingFactorColumn("keg_priming_factor");

RecipeDB::RecipeDB():
      ItemDB(Brewtarget::RECTABLE, Brewtarget::NOTABLE)
{

}

