#include "StyleDB.h"

const QString StyleDB::kCategoryColumn("category");
const QString StyleDB::kCategoryNumberColumn("category_number");
const QString StyleDB::kStyleLetterColumn("style_letter");
const QString StyleDB::kStyleGuideColumn("style_guide");
const QString StyleDB::kTypeColumn("s_type");
const QString StyleDB::kMinOGColumn("og_min");
const QString StyleDB::kMaxOGColumn("og_max");
const QString StyleDB::kMinFGColumn("fg_min");
const QString StyleDB::kMaxFGColumn("fg_max");
const QString StyleDB::kMinIBUColumn("ibu_min");
const QString StyleDB::kMaxIBUColumn("ibu_max");
const QString StyleDB::kMinColorColumn("color_min");
const QString StyleDB::kMaxColorColumn("color_max");
const QString StyleDB::kMinCarbColumn("carb_min");
const QString StyleDB::kMaxCarbColumn("carb_max");
const QString StyleDB::kMinABVColumn("abv_min");
const QString StyleDB::kMaxABVColumn("abv_max");
const QString StyleDB::kNotesColumn("notes");
const QString StyleDB::kProfileColumn("profile");
const QString StyleDB::kIngredientsColumn("ingredients");
const QString StyleDB::kExamplesColumn("examples");

StyleDB::StyleDB():
   ItemDB(Brewtarget::STYLETABLE, Brewtarget::NOTABLE)
{

}

