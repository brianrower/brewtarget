#include "InstructionDB.h"

const QString InstructionDB::kDirectionsColumn("directions");
const QString InstructionDB::kHasTimerColumn("hasTimer");
const QString InstructionDB::kTimerValueColumn("timerValue");
const QString InstructionDB::kCompletedColumn("completed");
const QString InstructionDB::kIntervalColumn("interval");

InstructionDB::InstructionDB():
   ItemDB(Brewtarget::INSTRUCTIONTABLE, Brewtarget::NOTABLE)
{

}

