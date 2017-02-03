
#pragma once

#include "ItemDB.h"

class FermentablesDB : public ItemDB
{
public:
   FermentablesDB();

   static const QString kTypeColumn;
   static const QString kAmountColumn;
   static const QString kYieldColumn;
   static const QString kColorColumn;
   static const QString kCoarseFineDiffColumn;
   static const QString kMoistureColumn;
   static const QString kDiastaticPowerColumn;
   static const QString kProteinColumn;
   static const QString kMaxInBatchColumn;
   static const QString kIBUGalPerLbColumn;
   static const QString kAddAfterBoilColumn;
   static const QString kOriginColumn;
   static const QString kSupplierColumn;
   static const QString kNotesColumn;
   static const QString kRecommendMashColumn;
   static const QString kIsMashedColumn;

};

