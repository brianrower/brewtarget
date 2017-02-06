#pragma once

#include "ItemDB.h"

class StyleDB: public ItemDB
{
public:
   StyleDB();

   static const QString kCategoryColumn;
   static const QString kCategoryNumberColumn;
   static const QString kStyleLetterColumn;
   static const QString kStyleGuideColumn;
   static const QString kTypeColumn;
   static const QString kMinOGColumn;
   static const QString kMaxOGColumn;
   static const QString kMinFGColumn;
   static const QString kMaxFGColumn;
   static const QString kMinIBUColumn;
   static const QString kMaxIBUColumn;
   static const QString kMinColorColumn;
   static const QString kMaxColorColumn;
   static const QString kMinCarbColumn;
   static const QString kMaxCarbColumn;
   static const QString kMinABVColumn;
   static const QString kMaxABVColumn;
   static const QString kNotesColumn;
   static const QString kProfileColumn;
   static const QString kIngredientsColumn;
   static const QString kExamplesColumn;
};

