
#pragma once

#include "ItemDB.h"

class WaterDB : public ItemDB
{
public:
   WaterDB();

   static const QString kAmountColumn;
   static const QString kCalciumColumn;
   static const QString kBicarbonateColumn;
   static const QString kChlorideColumn;
   static const QString kSodiumColumn;
   static const QString kMagnesiumColumn;
   static const QString kPhColumn;
   static const QString kSulfateColumn;
   static const QString kNotesColumn;
};

