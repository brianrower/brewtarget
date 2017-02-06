#pragma once

#include "ItemDB.h"

class YeastDB : public ItemDB
{
public:
   YeastDB();

   static const QString kLaboratoryColumn;
   static const QString kProductIDColumn;
   static const QString kNotesColumn;
   static const QString kBestForColumn;
   static const QString kAmountColumn;
   static const QString kMinTempColumn;
   static const QString kMaxTempColumn;
   static const QString kAttenuationColumn;
   static const QString kQuantityColumn;
   static const QString kTimesCulturedColumn;
   static const QString kMaxReuseColumn;
   static const QString kAddToSecondaryColumn;
   static const QString kAmtIsWeightColumn;
   static const QString kFormColumn;
   static const QString kFlocculationColumn;
   static const QString kTypeColumn;
};

