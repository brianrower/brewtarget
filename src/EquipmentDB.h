#pragma once

#include "ItemDB.h"


class EquipmentDB : public ItemDB
{
public:
   EquipmentDB();

   static const QString kBoilSizeColumn;
   static const QString kBatchSizeColumn;
   static const QString kTunVolumeColumn;
   static const QString kTunWeightColumn;
   static const QString kTunSpecificHeatColumn;
   static const QString kTopUpWaterColumn;
   static const QString kTrubChillerLossColumn;
   static const QString kEvaporationRateColumn;
   static const QString kRealEvaporationRateColumn;
   static const QString kBoilTimeColumn;
   static const QString kCalcBoilVolumeColumn;
   static const QString kLauterDeadspaceColumn;
   static const QString kTopUpKettleColumn;
   static const QString kHopUtilizationColumn;
   static const QString kNotesColumn;
   static const QString kAbsorptionColumn;
   static const QString kBoilingPointColumn;
};

