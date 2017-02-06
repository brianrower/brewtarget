#pragma once

#include "ItemDB.h"

class RecipeDB : public ItemDB
{
public:
   RecipeDB();

   static const QString kTypeColumn;
   static const QString kBrewerColumn;
   static const QString kBatchSizeColumn;
   static const QString kBoilSizeColumn;
   static const QString kBoilTimeColumn;
   static const QString kEfficiencyColumn;
   static const QString kAsstBrewerColumn;
   static const QString kNotesColumn;
   static const QString kTasteNotesColumn;
   static const QString kTasteRatingColumn;
   static const QString kOGColumn;
   static const QString kFGColumn;
   static const QString kFermStagesColumn;
   static const QString kPrimaryAgeColumn;
   static const QString kPrimaryTempColumn;
   static const QString kSecondaryAgeColumn;
   static const QString kSecondaryTempColumn;
   static const QString kTertiaryAgeColumn;
   static const QString kTertiaryTempColumn;
   static const QString kAgeColumn;
   static const QString kAgeTempColumn;
   static const QString kDateColumn;
   static const QString kCarbVolumeColumn;
   static const QString kForcedCarbColumn;
   static const QString kPrimingSugarNameColumn;
   static const QString kCarbonationTempColumn;
   static const QString kPrimingSugarEquivColumn;
   static const QString kKegPrimingFactorColumn;
};

