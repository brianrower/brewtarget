#include "FermentablesDB.h"


const QString FermentablesDB::kTypeColumn("ftype");
const QString FermentablesDB::kAmountColumn("amount");
const QString FermentablesDB::kYieldColumn("yield");
const QString FermentablesDB::kColorColumn("color");
const QString FermentablesDB::kCoarseFineDiffColumn("coarse_fine_diff");
const QString FermentablesDB::kMoistureColumn("moisture");
const QString FermentablesDB::kDiastaticPowerColumn("diastatic_power");
const QString FermentablesDB::kProteinColumn("protein");
const QString FermentablesDB::kMaxInBatchColumn("max_in_batch");
const QString FermentablesDB::kIBUGalPerLbColumn("ibu_gal_per_lb");
const QString FermentablesDB::kAddAfterBoilColumn("add_after_boil");
const QString FermentablesDB::kOriginColumn("origin");
const QString FermentablesDB::kSupplierColumn("supplier");
const QString FermentablesDB::kNotesColumn("notes");
const QString FermentablesDB::kRecommendMashColumn("recommend_mash");
const QString FermentablesDB::kIsMashedColumn("is_mashed");




FermentablesDB::FermentablesDB():
      ItemDB(Brewtarget::FERMTABLE, Brewtarget::FERMINVTABLE)
{
}
