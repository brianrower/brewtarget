#include "HopsDB.h"


const QString HopsDB::kAlphaColumn("alpha");
const QString HopsDB::kAmountColumn("amount");
const QString HopsDB::kUseColumn("use");
const QString HopsDB::kTimeColumn("time");
const QString HopsDB::kNotesColumn("notes");
const QString HopsDB::kTypeColumn("htype");
const QString HopsDB::kFormColumn("form");
const QString HopsDB::kBetaColumn("beta");
const QString HopsDB::kHSIColumn("hsi");
const QString HopsDB::kOriginColumn("origin");
const QString HopsDB::kSubstitutesColumn("substitutes");
const QString HopsDB::kHumuleneColumn("humulene");
const QString HopsDB::kCaryophylleneColumn("caryophyllene");
const QString HopsDB::kCohumuloneColumn("cohumulone");
const QString HopsDB::kMyrceneColumn("myrcene");


HopsDB::HopsDB():
   ItemDB(Brewtarget::HOPTABLE, Brewtarget::HOPINVTABLE)
{

}

