#pragma once

#include "ItemDB.h"


class MashStepDB : public ItemDB
{
public:
   MashStepDB();

   static const QString kInfuseTempColumn;
   static const QString kTypeColumn;
   static const QString kInfuseAmtColumn;
   static const QString kStepTempColumn;
   static const QString kStepTimeColumn;
   static const QString kRampTimeColumn;
   static const QString kEndTempColumn;
   static const QString kDecoctionAmountColumn;
   static const QString kStepNumberColumn;
};
