#include "MashStepDB.h"

const QString MashStepDB::kInfuseTempColumn("infuse_temp");
const QString MashStepDB::kTypeColumn("mstype");
const QString MashStepDB::kInfuseAmtColumn("infuse_amount");
const QString MashStepDB::kStepTempColumn("step_temp");
const QString MashStepDB::kStepTimeColumn("step_time");
const QString MashStepDB::kRampTimeColumn("ramp_time");
const QString MashStepDB::kEndTempColumn("end_temp");
const QString MashStepDB::kDecoctionAmountColumn("decoction_amount");
const QString MashStepDB::kStepNumberColumn("step_number");

MashStepDB::MashStepDB():
   ItemDB(Brewtarget::MASHSTEPTABLE, Brewtarget::NOTABLE)
{

}

