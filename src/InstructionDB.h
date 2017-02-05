#pragma once

#include "ItemDB.h"


class InstructionDB : public ItemDB
{
public:
   InstructionDB();

   static const QString kDirectionsColumn;
   static const QString kHasTimerColumn;
   static const QString kTimerValueColumn;
   static const QString kCompletedColumn;
   static const QString kIntervalColumn;
};

