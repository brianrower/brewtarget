#pragma once

#include "ItemDB.h"

class MashDB : public ItemDB
{
public:
   MashDB();

   static const QString kGrainTempColumn;
   static const QString kNotesColumn;
   static const QString kTunTempColumn;
   static const QString kSpargeTempColumn;
   static const QString kEquipmentAdjustColumn;
   static const QString kPhColumn;
   static const QString kTunWeightColumn;
   static const QString kTunSpecificHeatColumn;

};

