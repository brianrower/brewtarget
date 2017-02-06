/*
 * style.cpp is part of Brewtarget, and is Copyright the following
 * authors 2009-2014
 * - Mik Firestone <mikfire@gmail.com>
 * - Philip Greggory Lee <rocketman768@gmail.com>
 *
 * Brewtarget is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Brewtarget is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "brewtarget.h"
#include "style.h"
#include <QDebug>
#include "StyleDB.h"

QStringList Style::types = QStringList() << "Lager" << "Ale" << "Mead" << "Wheat" << "Mixed" << "Cider";
QHash<QString,QString> Style::tagToProp = Style::tagToPropHash();

QHash<QString,QString> Style::tagToPropHash()
{
   QHash<QString,QString> propHash;
   propHash["NAME"] = "name";
   propHash["CATEGORY"] = "category";
   propHash["CATEGORY_NUMBER"] = "categoryNumber";
   propHash["STYLE_LETTER"] = "styleLetter";
   propHash["STYLE_GUIDE"] = "styleGuide";
   //propHash["TYPE"] = "type";
   propHash["OG_MIN"] = "ogMin";
   propHash["OG_MAX"] = "ogMax";
   propHash["FG_MIN"] = "fgMin";
   propHash["FG_MAX"] = "fgMax";
   propHash["IBU_MIN"] = "ibuMin";
   propHash["IBU_MAX"] = "ibuMax";
   propHash["COLOR_MIN"] = "colorMin_srm";
   propHash["COLOR_MAX"] = "colorMax_srm";
   propHash["CARB_MIN"] = "carbMin_vol";
   propHash["CARB_MAX"] = "carbMax_vol";
   propHash["ABV_MIN"] = "abvMin_pct";
   propHash["ABV_MAX"] = "abvMax_pct";
   propHash["NOTES"] = "notes";
   propHash["PROFILE"] = "profile";
   propHash["INGREDIENTS"] = "ingredients";
   propHash["EXAMPLES"] = "examples";
   return propHash;
}

bool operator<(Style &s1, Style &s2)
{
   return s1.name() < s2.name();
}

bool operator==(Style &s1, Style &s2)
{
   return s1.key() == s2.key();
}

Style::Style()
   : BeerXMLElement()
{
   _db.reset(new StyleDB());
}

Style::~Style()
{

}

ItemDB* Style::getDB() const
{
   return _db.get();
}

//==============================="SET" METHODS==================================
void Style::setCategory( const QString& var )
{
   getDB()->updateColumn(StyleDB::kCategoryColumn, var );
}

void Style::setCategoryNumber( const QString& var )
{
   getDB()->updateColumn(StyleDB::kCategoryNumberColumn, var );
}

void Style::setStyleLetter( const QString& var )
{
   getDB()->updateColumn(StyleDB::kStyleLetterColumn, var );
}

void Style::setStyleGuide( const QString& var )
{
   getDB()->updateColumn(StyleDB::kStyleGuideColumn, var );
}

void Style::setType( Type t )
{
   getDB()->updateColumn(StyleDB::kTypeColumn, types.at(t) );
}

void Style::setOgMin( double var )
{
   if( var < 0.0 )
      return;

   getDB()->updateColumn(StyleDB::kMinOGColumn, var);
}

void Style::setOgMax( double var )
{
   if( var < 0.0 )
      return;

   getDB()->updateColumn(StyleDB::kMaxOGColumn, var);
}

void Style::setFgMin( double var )
{
   if( var < 0.0 )
      return;

   getDB()->updateColumn(StyleDB::kMinFGColumn, var);
}

void Style::setFgMax( double var )
{
   if( var < 0.0 )
      return;

   getDB()->updateColumn(StyleDB::kMaxFGColumn, var);
}

void Style::setIbuMin( double var )
{
   if( var < 0.0 )
      return;

   getDB()->updateColumn(StyleDB::kMinIBUColumn, var);
}

void Style::setIbuMax( double var )
{
   if( var < 0.0 )
      return;

   getDB()->updateColumn(StyleDB::kMaxIBUColumn, var);
}

void Style::setColorMin_srm( double var )
{
   if( var < 0.0 )
      return;

   getDB()->updateColumn(StyleDB::kMinColorColumn, var);
}

void Style::setColorMax_srm( double var )
{
   if( var < 0.0 )
      return;

   getDB()->updateColumn(StyleDB::kMaxColorColumn, var);
}

void Style::setCarbMin_vol( double var )
{
   if( var < 0.0 )
      return;

   getDB()->updateColumn(StyleDB::kMinCarbColumn, var);
}

void Style::setCarbMax_vol( double var )
{
   if( var < 0.0 )
      return;

   getDB()->updateColumn(StyleDB::kMaxCarbColumn, var);
}

void Style::setAbvMin_pct( double var )
{
   if( var < 0.0 || var > 100.0 )
      return;

   getDB()->updateColumn(StyleDB::kMinABVColumn, var);
}

void Style::setAbvMax_pct( double var )
{
   if( var < 0.0 || var > 100.0 )
      return;

   getDB()->updateColumn(StyleDB::kMaxABVColumn, var);
}

void Style::setNotes( const QString& var )
{
   getDB()->updateColumn(StyleDB::kNotesColumn, var);
}

void Style::setProfile( const QString& var )
{
   getDB()->updateColumn(StyleDB::kProfileColumn, var);
}

void Style::setIngredients( const QString& var )
{
   getDB()->updateColumn(StyleDB::kIngredientsColumn, var);
}

void Style::setExamples( const QString& var )
{
   getDB()->updateColumn(StyleDB::kExamplesColumn, var);
}

//============================="GET" METHODS====================================
QString Style::category() const
{
   return getDB()->getColumn(StyleDB::kCategoryColumn).toString();
}

QString Style::categoryNumber() const
{
   return getDB()->getColumn(StyleDB::kCategoryNumberColumn).toString();
}

QString Style::styleLetter() const
{
   return getDB()->getColumn(StyleDB::kStyleLetterColumn).toString();
}

QString Style::styleGuide() const
{
   return getDB()->getColumn(StyleDB::kStyleGuideColumn).toString();
}

QString Style::notes() const
{
   return getDB()->getColumn(StyleDB::kNotesColumn).toString();
}

QString Style::profile() const
{
   return getDB()->getColumn(StyleDB::kProfileColumn).toString();
}

QString Style::ingredients() const
{
   return getDB()->getColumn(StyleDB::kIngredientsColumn).toString();
}

QString Style::examples() const
{
   return getDB()->getColumn(StyleDB::kExamplesColumn).toString();
}

const Style::Type Style::type() const
{
   return static_cast<Style::Type>(types.indexOf(typeString()));
}

const QString Style::typeString() const
{
   return getDB()->getColumn(StyleDB::kTypeColumn).toString();
}

double Style::ogMin()        const
{
   return getDB()->getColumn(StyleDB::kMinOGColumn).toDouble();
}

double Style::ogMax()        const
{
   return getDB()->getColumn(StyleDB::kMaxOGColumn).toDouble();
}

double Style::fgMin()        const
{
   return getDB()->getColumn(StyleDB::kMinFGColumn).toDouble();
}

double Style::fgMax()        const
{
   return getDB()->getColumn(StyleDB::kMaxFGColumn).toDouble();
}

double Style::ibuMin()       const
{
   return getDB()->getColumn(StyleDB::kMinIBUColumn).toDouble();
}

double Style::ibuMax()       const
{
   return getDB()->getColumn(StyleDB::kMaxIBUColumn).toDouble();
}

double Style::colorMin_srm() const
{
   return getDB()->getColumn(StyleDB::kMinColorColumn).toDouble();
}

double Style::colorMax_srm() const
{
   return getDB()->getColumn(StyleDB::kMaxColorColumn).toDouble();
}

double Style::carbMin_vol()  const
{
   return getDB()->getColumn(StyleDB::kMinCarbColumn).toDouble();
}

double Style::carbMax_vol()  const
{
   return getDB()->getColumn(StyleDB::kMaxCarbColumn).toDouble();
}

double Style::abvMin_pct()   const
{
   return getDB()->getColumn(StyleDB::kMinABVColumn).toDouble();
}

double Style::abvMax_pct()   const
{
   return getDB()->getColumn(StyleDB::kMaxABVColumn).toDouble();
}

bool Style::isValidType( const QString &str )
{
   return types.contains( str );
}

