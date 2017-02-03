
#pragma once

#include "ItemDB.h"

class BrewNoteDB : public ItemDB
{
public:
   BrewNoteDB();

   static const QString kBrewDateColumn;
   static const QString kFermentDateColumn;
   static const QString kNotesColumn;
   static const QString kSpecificGravityColumn;
   static const QString kVolumeIntoBoilColumn;
   static const QString kOriginalGravityColumn;
   static const QString kVolumeIntoFermenterColumn;
   static const QString kFinalGravityColumn;
   static const QString kProjectedPointsColumn;
   static const QString kProjectedFermentationPointsColumn;
   static const QString kABVColumn;
   static const QString kEfficiencyIntoBoilColumn;
   static const QString kBrewhouseEfficiencyColumn;
   static const QString kStrikeTempColumn;
   static const QString kMashFinalTempColumn;
   static const QString kPostBoilVolumeColumn;
   static const QString kPitchTempColumn;
   static const QString kFinalVolumeColumn;
   static const QString kProjectedBoilGravityColumn;
   static const QString kProjectedVolumeIntoBoilColumn;
   static const QString kProjectedStrikeTempColumn;
   static const QString kProjectedMashFinishTempColumn;
   static const QString kProjectedOGColumn;
   static const QString kProjectedVolumeIntoFermenterColumn;
   static const QString kProjectedFGColumn;
   static const QString kProjectedEfficiencyColumn;
   static const QString kProjectedABVColumn;
   static const QString kProjectedAttenuationColumn;
   static const QString kBoilOffColumn;
};

