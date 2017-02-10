/*
 * yeast.cpp is part of Brewtarget, and is Copyright the following
 * authors 2009-2014
 * - marker5a
 * - Philip Greggory Lee <rocketman768@gmail.com>
 * - plut0nium
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

#include <QDomNode>
#include <QDomElement>
#include <QDomText>
#include <QObject>
#include "yeast.h"
#include "brewtarget.h"
#include "YeastDB.h"

QStringList Yeast::types = QStringList() << "Ale" << "Lager" << "Wheat" << "Wine" << "Champagne";
QStringList Yeast::forms = QStringList() << "Liquid" << "Dry" << "Slant" << "Culture";
QStringList Yeast::flocculations = QStringList() << "Low" << "Medium" << "High" << "Very High";
QHash<QString,QString> Yeast::tagToProp = Yeast::tagToPropHash();

QHash<QString,QString> Yeast::tagToPropHash()
{
   QHash<QString,QString> propHash;
   propHash["NAME"] = "name";
   //propHash["TYPE"] = "type";
   //propHash["FORM"] = "form";
   propHash["AMOUNT"] = "amount";
   propHash["INVENTORY"] = "inventory";
   propHash["AMOUNT_IS_WEIGHT"] = "amountIsWeight";
   propHash["LABORATORY"] = "laboratory";
   propHash["PRODUCT_ID"] = "productID";
   propHash["MIN_TEMPERATURE"] = "minTemperature_c";
   propHash["MAX_TEMPERATURE"] = "maxTemperature_c";
   //propHash["FLOCCULATION"] = "flocculation";
   propHash["ATTENUATION"] = "attenuation_pct";
   propHash["NOTES"] = "notes";
   propHash["BEST_FOR"] = "bestFor";
   propHash["TIMES_CULTURED"] = "timesCultured";
   propHash["MAX_REUSE"] = "maxReuse";
   propHash["ADD_TO_SECONDARY"] = "addToSecondary";
   return propHash;
}

bool operator<(Yeast &y1, Yeast &y2)
{
   return y1.name() < y2.name();
}

bool operator==(Yeast &y1, Yeast &y2)
{
   return y1.name() == y2.name();
}

//============================CONSTRUCTORS======================================
Yeast::Yeast()
   : BeerIngredient()
{
   _db.reset(new YeastDB());
}

Yeast::Yeast(Yeast const& other) : BeerIngredient(other)
{
   _db.reset(new YeastDB());
}

Yeast::~Yeast()
{
}

ItemDB* Yeast::getDB() const
{
   return _db.get();
}

//============================="GET" METHODS====================================
QString Yeast::laboratory() const
{
   return getDB()->getColumn(YeastDB::kLaboratoryColumn).toString();
}

QString Yeast::productID() const
{
   return getDB()->getColumn(YeastDB::kProductIDColumn).toString();
}

QString Yeast::notes() const
{
   return getDB()->getColumn(YeastDB::kNotesColumn).toString();
}

QString Yeast::bestFor() const
{
   return getDB()->getColumn(YeastDB::kBestForColumn).toString();
}

double Yeast::amount() const
{
   return getDB()->getColumn(YeastDB::kAmountColumn).toDouble();
}

double Yeast::minTemperature_c() const
{
   return getDB()->getColumn(YeastDB::kMinTempColumn).toDouble();
}

double Yeast::maxTemperature_c() const
{
   return getDB()->getColumn(YeastDB::kMaxTempColumn).toDouble();
}

double Yeast::attenuation_pct() const
{
   return getDB()->getColumn(YeastDB::kAttenuationColumn).toDouble();
}

int Yeast::inventory() const
{
   return getDB()->getInventoryColumn(YeastDB::kQuantityColumn).toInt();
}

int Yeast::timesCultured() const
{
   return getDB()->getColumn(YeastDB::kTimesCulturedColumn).toInt();
}

int Yeast::maxReuse() const
{
   return getDB()->getColumn(YeastDB::kMaxReuseColumn).toInt();
}

bool Yeast::addToSecondary() const
{
   return getDB()->getColumn(YeastDB::kAddToSecondaryColumn).toBool();
}

bool Yeast::amountIsWeight() const
{
   return getDB()->getColumn(YeastDB::kAmtIsWeightColumn).toBool();
}

Yeast::Form Yeast::form() const
{
   return static_cast<Yeast::Form>(forms.indexOf(formString()));
}

const QString Yeast::formString() const
{
   return getDB()->getColumn(YeastDB::kFormColumn).toString();
}

Yeast::Flocculation Yeast::flocculation() const
{
   return static_cast<Yeast::Flocculation>( flocculations.indexOf(flocculationString()));
}

const QString Yeast::flocculationString() const
{
   return getDB()->getColumn(YeastDB::kFlocculationColumn).toString();
}

Yeast::Type Yeast::type() const
{
   return static_cast<Yeast::Type>( types.indexOf(typeString()));
}

const QString Yeast::typeString() const
{
   return getDB()->getColumn(YeastDB::kTypeColumn).toString();
}

const QString Yeast::typeStringTr() const
{
   static QStringList typesTr = QStringList() << QObject::tr("Ale")
                                       << QObject::tr("Lager")
                                       << QObject::tr("Wheat")
                                       << QObject::tr("Wine")
                                       << QObject::tr("Champagne");
   return typesTr.at(type());
}

const QString Yeast::formStringTr() const
{
   static QStringList formsTr = QStringList() << QObject::tr("Liquid")
                                       << QObject::tr("Dry")
                                       << QObject::tr("Slant")
                                       << QObject::tr("Culture");
   return formsTr.at(form());
}

const QString Yeast::flocculationStringTr() const
{
   static QStringList flocculationsTr = QStringList() << QObject::tr("Low")
                                               << QObject::tr("Medium")
                                               << QObject::tr("High")
                                               << QObject::tr("Very High");
   return flocculationsTr.at(flocculation());
}

//============================="SET" METHODS====================================
void Yeast::setType( Yeast::Type t )
{
   getDB()->updateColumn(YeastDB::kTypeColumn, types.at(t));
   emit yeastChanged();
}

void Yeast::setForm( Yeast::Form f )
{
   getDB()->updateColumn(YeastDB::kFormColumn, forms.at(f));
   emit yeastChanged();
}

void Yeast::setAmount( double var )
{
   if( var < 0.0 )
   {
      Brewtarget::logW( QString("Yeast: amount < 0: %1").arg(var) );
      return;
   }

   getDB()->updateColumn(YeastDB::kAmountColumn, var);
   emit yeastChanged();

}

void Yeast::setInventoryQuanta( int var )
{
   if( var < 0.0 )
   {
      Brewtarget::logW( QString("Yeast: inventory < 0: %1").arg(var) );
      return;
   }

   getDB()->updateInventoryColumn(YeastDB::kQuantityColumn, var);
   emit yeastChanged();
}

void Yeast::setAmountIsWeight( bool var )
{
   getDB()->updateColumn(YeastDB::kAmtIsWeightColumn, var);
   emit yeastChanged();
}

void Yeast::setLaboratory( const QString& var )
{
   getDB()->updateColumn(YeastDB::kLaboratoryColumn, var);
   emit yeastChanged();
}

void Yeast::setProductID( const QString& var )
{
   getDB()->updateColumn(YeastDB::kProductIDColumn, var);
   emit yeastChanged();
}

void Yeast::setMinTemperature_c( double var )
{
   if( var < -273.15 )
      return;

   getDB()->updateColumn(YeastDB::kMinTempColumn, var);
   emit yeastChanged();
}

void Yeast::setMaxTemperature_c( double var )
{
   if( var < -273.15 )
      return;

   getDB()->updateColumn(YeastDB::kMaxTempColumn, var);
   emit yeastChanged();
}

void Yeast::setFlocculation( Yeast::Flocculation f )
{
   getDB()->updateColumn(YeastDB::kFlocculationColumn, flocculations.at(f));
   emit yeastChanged();
}

void Yeast::setAttenuation_pct( double var )
{
   if( var < 0.0 || var > 100.0 )
      return;

   getDB()->updateColumn(YeastDB::kAttenuationColumn, var);
   emit yeastChanged();
}

void Yeast::setNotes( const QString& var )
{
   getDB()->updateColumn(YeastDB::kNotesColumn, var);
   emit yeastChanged();
}

void Yeast::setBestFor( const QString& var )
{
   getDB()->updateColumn(YeastDB::kBestForColumn, var);
   emit yeastChanged();
}

void Yeast::setTimesCultured( int var )
{
   if( var < 0 )
      return;

   getDB()->updateColumn(YeastDB::kTimesCulturedColumn, var);
   emit yeastChanged();
}

void Yeast::setMaxReuse( int var )
{
   if( var < 0 )
      return;

   getDB()->updateColumn(YeastDB::kMaxReuseColumn, var);
   emit yeastChanged();
}

void Yeast::setAddToSecondary( bool var )
{
   getDB()->updateColumn(YeastDB::kAddToSecondaryColumn, var);
   emit yeastChanged();
}

//========================OTHER METHODS=========================================
bool Yeast::isValidType(const QString& str) const
{
   static const QString types[] = {"Ale", "Lager", "Wheat", "Wine", "Champagne"};
   unsigned int i, size = 5;
   
   for( i = 0; i < size; ++i )
      if( str == types[i] )
         return true;
   
   return false;
}

bool Yeast::isValidForm(const QString& str) const
{
   static const QString forms[] = {"Liquid", "Dry", "Slant", "Culture"};
   unsigned int i, size=4;
   
   for( i = 0; i < size; ++i )
      if( str == forms[i] )
         return true;
   
   return false;
}

bool Yeast::isValidFlocculation(const QString& str) const
{
   static const QString floc[] = {"Low", "Medium", "High", "Very High"};
   unsigned int i, size=4;
   
   for( i = 0; i < size; ++i )
      if( str == floc[i] )
         return true;
   
   return false;
}
