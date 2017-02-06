/*
 * fermentable.cpp is part of Brewtarget, and is Copyright the following
 * authors 2009-2014
 * - Kregg K <gigatropolis@yahoo.com>
 * - Mik Firestone <mikfire@gmail.com>
 * - Philip Greggory Lee <rocketman768@gmail.com>
 * - Samuel Östling <MrOstling@gmail.com>
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

#include <QDomElement>
#include <QDomText>
#include <QVariant>
#include <QObject>
#include <QDebug>
#include "fermentable.h"
#include "brewtarget.h"
#include "FermentablesDB.h"

QStringList Fermentable::types = QStringList() << "Grain" << "Sugar" << "Extract" << "Dry Extract" << "Adjunct";
QHash<QString,QString> Fermentable::tagToProp = Fermentable::tagToPropHash();

QHash<QString,QString> Fermentable::tagToPropHash()
{
   QHash<QString,QString> propHash;
   
   propHash["NAME"] = "name";
   // NOTE: since type is actually stored as a string (not integer), have to handle separately.
   //propHash["TYPE"] = "type";
   propHash["AMOUNT"] = "amount_kg";
   propHash["INVENTORY"] = "inventory";
   propHash["YIELD"] = "yield_pct";
   propHash["COLOR"] = "color_srm";
   propHash["ADD_AFTER_BOIL"] = "addAfterBoil";
   propHash["ORIGIN"] = "origin";
   propHash["SUPPLIER"] = "supplier";
   propHash["NOTES"] = "notes";
   propHash["COARSE_FINE_DIFF"] = "coarseFineDiff_pct";
   propHash["MOISTURE"] = "moisture_pct";
   propHash["DIASTATIC_POWER"] = "diastaticPower_lintner";
   propHash["PROTEIN"] = "protein_pct";
   propHash["MAX_IN_BATCH"] = "maxInBatch_pct";
   propHash["RECOMMEND_MASH"] = "recommendMash";
   propHash["IS_MASHED"] = "isMashed";
   propHash["IBU_GAL_PER_LB"] = "ibuGalPerLb";
   return propHash;
}

bool operator<(Fermentable &f1, Fermentable &f2)
{
   return f1.name() < f2.name();
}

bool operator==(Fermentable &f1, Fermentable &f2)
{
   return f1.name() == f2.name();
}

Fermentable::Fermentable()
   : BeerIngredient()
{
   _db.reset(new FermentablesDB());
}

Fermentable::Fermentable( Fermentable const& other )
        : BeerIngredient( other )
{
   _db.reset(new FermentablesDB());
}

Fermentable::~Fermentable()
{
}

ItemDB* Fermentable::getDB() const
{
   return _db.get();
}

// Get
const Fermentable::Type Fermentable::type() const
{
   QString type = getDB()->getColumn(FermentablesDB::kTypeColumn).toString();
   return static_cast<Fermentable::Type>(types.indexOf(type));
}

const QString Fermentable::typeString() const
{
   return types.at(type());
}

const QString Fermentable::typeStringTr() const
{
   static QStringList typesTr = QStringList () << QObject::tr("Grain") << QObject::tr("Sugar") << QObject::tr("Extract") << QObject::tr("Dry Extract") << QObject::tr("Adjunct");
   return typesTr.at(type());
}

const Fermentable::AdditionMethod Fermentable::additionMethod() const
{
   Fermentable::AdditionMethod additionMethod;
   if(isMashed())
      additionMethod = Fermentable::Mashed;
   else
   {
      if(type() == Fermentable::Grain)
         additionMethod = Fermentable::Steeped;
      else
         additionMethod = Fermentable::Not_Mashed;
   }
   return additionMethod;
}

const Fermentable::AdditionTime Fermentable::additionTime() const
{
   Fermentable::AdditionTime additionTime;
   if(addAfterBoil())
      additionTime = Fermentable::Late;
   else
      additionTime = Fermentable::Normal;

   return additionTime;
}

const QString Fermentable::additionMethodStringTr() const
{
    QString retString;

    if(isMashed())
       retString = tr("Mashed");
    else
    {
       if(type() == Fermentable::Grain)
          retString = tr("Steeped");
       else
          retString = tr("Not mashed");
    }
    return retString;
}

const QString Fermentable::additionTimeStringTr() const
{
    QString retString;

    if(addAfterBoil())
       retString = tr("Late");
    else
       retString = tr("Normal");

    return retString;
}

double Fermentable::amount_kg() const
{
   return getDB()->getColumn(FermentablesDB::kAmountColumn).toDouble();
}

double Fermentable::yield_pct() const
{
   return getDB()->getColumn(FermentablesDB::kYieldColumn).toDouble();
}

double Fermentable::color_srm() const
{
   return getDB()->getColumn(FermentablesDB::kColorColumn).toDouble();
}

double Fermentable::coarseFineDiff_pct() const
{
   return getDB()->getColumn(FermentablesDB::kCoarseFineDiffColumn).toDouble();
}

double Fermentable::moisture_pct() const
{
   return getDB()->getColumn(FermentablesDB::kMoistureColumn).toDouble();
}

double Fermentable::diastaticPower_lintner() const
{
   return getDB()->getColumn(FermentablesDB::kDiastaticPowerColumn).toDouble();
}

double Fermentable::protein_pct() const
{
   return getDB()->getColumn(FermentablesDB::kProteinColumn).toDouble();
}

double Fermentable::maxInBatch_pct() const
{
   return getDB()->getColumn(FermentablesDB::kMaxInBatchColumn).toDouble();
}

double Fermentable::ibuGalPerLb() const
{
   return getDB()->getColumn(FermentablesDB::kIBUGalPerLbColumn).toDouble();
}

// inventory must be handled separately, to my great annoyance
double Fermentable::inventory() const 
{ 
   return getDB()->getInventoryColumn(FermentablesDB::kAmountColumn).toDouble();
}

bool Fermentable::addAfterBoil() const
{
   return getDB()->getColumn(FermentablesDB::kAddAfterBoilColumn).toBool();
}

const QString Fermentable::origin() const
{
   return getDB()->getColumn(FermentablesDB::kOriginColumn).toString();
}
const QString Fermentable::supplier() const
{
   return getDB()->getColumn(FermentablesDB::kSupplierColumn).toString();
}

const QString Fermentable::notes() const
{
   return getDB()->getColumn(FermentablesDB::kNotesColumn).toString();
}

bool Fermentable::recommendMash() const
{
   return getDB()->getColumn(FermentablesDB::kRecommendMashColumn).toBool();
}

bool Fermentable::isMashed() const
{
   return getDB()->getColumn(FermentablesDB::kIsMashedColumn).toBool();
}

bool Fermentable::isExtract()
{
   return ((type() == Extract) || (type() == Dry_Extract));
}

bool Fermentable::isSugar()
{
   return (type() == Sugar);
}

bool Fermentable::isValidType( const QString& str )
{
   return (types.indexOf(str) >= 0);
}


void Fermentable::setType( Type t )
{
   getDB()->updateColumn(FermentablesDB::kTypeColumn, types.at(t));
}


void Fermentable::setAdditionMethod( Fermentable::AdditionMethod m )
{
   setIsMashed(m == Fermentable::Mashed);
}

void Fermentable::setAdditionTime( Fermentable::AdditionTime t )
{
   setAddAfterBoil(t == Fermentable::Late );
}

void Fermentable::setAddAfterBoil( bool b )
{
   getDB()->updateColumn(FermentablesDB::kAddAfterBoilColumn, b);
}

void Fermentable::setOrigin( const QString& str )
{
   getDB()->updateColumn(FermentablesDB::kOriginColumn, str);
}

void Fermentable::setSupplier( const QString& str)
{
   getDB()->updateColumn(FermentablesDB::kSupplierColumn, str);
}

void Fermentable::setNotes( const QString& str )
{
   getDB()->updateColumn(FermentablesDB::kNotesColumn, str);
}

void Fermentable::setRecommendMash( bool b )
{
   getDB()->updateColumn(FermentablesDB::kRecommendMashColumn, b);
}

void Fermentable::setIsMashed(bool var)
{
   getDB()->updateColumn(FermentablesDB::kIsMashedColumn, var);
}

void Fermentable::setIbuGalPerLb( double num )
{
   getDB()->updateColumn(FermentablesDB::kIBUGalPerLbColumn, num);
}

double Fermentable::equivSucrose_kg() const
{
   double ret = amount_kg() * yield_pct() * (1.0-moisture_pct()/100.0) / 100.0;
   
   // If this is a steeped grain...
   if( type() == Grain && !isMashed() )
      return 0.60 * ret; // Reduce the yield by 60%.
   else
      return ret;
}
void Fermentable::setAmount_kg( double num )
{
   if( num < 0.0 )
   {
      Brewtarget::logW( QString("Fermentable: negative amount: %1").arg(num) );
      return;
   }

   getDB()->updateColumn(FermentablesDB::kAmountColumn, num);
}
void Fermentable::setInventoryAmount( double num )
{
   if( num < 0.0 )
   {
      Brewtarget::logW( QString("Fermentable: negative inventory: %1").arg(num) );
      return;
   }
   getDB()->updateInventoryColumn(FermentablesDB::kAmountColumn, num);
}

void Fermentable::setYield_pct( double num )
{
   if( num >= 0.0 && num <= 100.0 )
   {
      getDB()->updateColumn(FermentablesDB::kYieldColumn, num);
   }
   else
   {
      Brewtarget::logW( QString("Fermentable: 0 < yield < 100: %1").arg(num) );
   }
}

void Fermentable::setColor_srm( double num )
{
   if( num < 0.0 )
   {
      Brewtarget::logW( QString("Fermentable: negative color: %1").arg(num) );
      return;
   }

   getDB()->updateColumn(FermentablesDB::kColorColumn, num);
}

void Fermentable::setCoarseFineDiff_pct( double num )
{
   if( num >= 0.0 && num <= 100.0 )
   {
      getDB()->updateColumn(FermentablesDB::kCoarseFineDiffColumn, num);
   }
   else
   {
      Brewtarget::logW( QString("Fermentable: 0 < coarsefinediff < 100: %1").arg(num) );
   }
}
void Fermentable::setMoisture_pct( double num )
{
   if( num >= 0.0 && num <= 100.0 )
   {
      getDB()->updateColumn(FermentablesDB::kMoistureColumn, num);
   }
   else
   {
      Brewtarget::logW( QString("Fermentable: 0 < moisture < 100: %1").arg(num) );
   }
}
void Fermentable::setDiastaticPower_lintner( double num )
{
   if( num < 0.0 )
   {
      Brewtarget::logW( QString("Fermentable: negative DP: %1").arg(num) );
      return;
   }

   getDB()->updateColumn(FermentablesDB::kDiastaticPowerColumn, num);

}
void Fermentable::setProtein_pct( double num )
{
   if( num >= 0.0 && num <= 100.0 )
   {
      getDB()->updateColumn(FermentablesDB::kProteinColumn, num);
   }
   else
   {
      Brewtarget::logW( QString("Fermentable: 0 < protein < 100: %1").arg(num) );
   }
}
void Fermentable::setMaxInBatch_pct( double num )
{
   if( num >= 0.0 && num <= 100.0 )
   {
      getDB()->updateColumn(FermentablesDB::kMaxInBatchColumn, num);
   }
   else
   {
      Brewtarget::logW( QString("Fermentable: 0 < maxinbatch < 100: %1").arg(num) );
   }
}

