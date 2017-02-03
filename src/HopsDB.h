#pragma once

#include "ItemDB.h"


class HopsDB : public ItemDB
{
public:
   HopsDB();

   static const QString kAlphaColumn;
   static const QString kAmountColumn;
   static const QString kUseColumn;
   static const QString kTimeColumn;
   static const QString kNotesColumn;
   static const QString kTypeColumn;
   static const QString kFormColumn;
   static const QString kBetaColumn;
   static const QString kHSIColumn;
   static const QString kOriginColumn;
   static const QString kSubstitutesColumn;
   static const QString kHumuleneColumn;
   static const QString kCaryophylleneColumn;
   static const QString kCohumuloneColumn;
   static const QString kMyrceneColumn;
};

