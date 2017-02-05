#pragma once

#include "ItemDB.h"

class MiscDB : public ItemDB
{
public:
   MiscDB();

   static const QString kTypeColumn;
   static const QString kUseColumn;
   static const QString kAmountColumn;
   static const QString kTimeColumn;
   static const QString kAmtIsWeightColumn;
   static const QString kUseForColumn;
   static const QString kNotesColumn;
};

