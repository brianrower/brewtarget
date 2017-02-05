/*
 * misc.cpp is part of Brewtarget, and is Copyright the following
 * authors 2009-2014
 * - mik firestone <mikfire@gmail.com>
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

#include <iostream>
#include <string>
#include <QVector>
#include <QDomElement>
#include <QDomText>
#include <QObject>
#include <QDebug>
#include "misc.h"
#include "brewtarget.h"
#include "MiscDB.h"

QStringList Misc::uses = QStringList() << "Boil" << "Mash" << "Primary" << "Secondary" << "Bottling";
QStringList Misc::types = QStringList() << "Spice" << "Fining" << "Water Agent" << "Herb" << "Flavor" << "Other";
QStringList Misc::amountTypes = QStringList() << "Weight" << "Volume";
QHash<QString,QString> Misc::tagToProp = Misc::tagToPropHash();

QHash<QString,QString> Misc::tagToPropHash()
{
   QHash<QString,QString> propHash;
   propHash["NAME"] = "name";
   //propHash["TYPE"] = "type";
   //propHash["USE"] = "use";
   propHash["TIME"] = "time";
   propHash["AMOUNT"] = "amount";
   propHash["AMOUNT_IS_WEIGHT"] = "amountIsWeight";
   propHash["INVENTORY"] = "inventory";
   propHash["USE_FOR"] = "useFor";
   propHash["NOTES"] = "notes";
   return propHash;
}
//============================CONSTRUCTORS======================================
Misc::Misc() : BeerXMLElement()
{
   _db.reset(new MiscDB());
}

Misc::Misc(Misc const& other) : BeerXMLElement(other)
{
   _db.reset(new MiscDB());
}

Misc::~Misc()
{
}

ItemDB* Misc::getDB() const
{
   return _db.get();
}

//============================"GET" METHODS=====================================
Misc::Type Misc::type() const
{
   return static_cast<Misc::Type>(types.indexOf(typeString()));
}

const QString Misc::typeString() const
{
   return getDB()->getColumn(MiscDB::kTypeColumn).toString();
}

Misc::Use Misc::use() const
{
   return static_cast<Misc::Use>(uses.indexOf(useString()));
}

const QString Misc::useString() const
{
   return getDB()->getColumn(MiscDB::kUseColumn).toString();
}

double Misc::amount()    const
{
   return getDB()->getColumn(MiscDB::kAmountColumn).toDouble();
}

double Misc::time()      const
{
   return getDB()->getColumn(MiscDB::kTimeColumn).toDouble();
}

bool Misc::amountIsWeight() const
{
   return getDB()->getColumn(MiscDB::kAmtIsWeightColumn).toBool();
}

QString Misc::useFor() const
{
   return getDB()->getColumn(MiscDB::kUseForColumn).toString();
}

QString Misc::notes() const
{
   return getDB()->getColumn(MiscDB::kNotesColumn).toString();
}

double Misc::inventory() const
{
   return getDB()->getInventoryColumn(MiscDB::kAmountColumn).toDouble();
}

Misc::AmountType Misc::amountType() const
{
   return amountIsWeight() ? AmountType_Weight : AmountType_Volume;
}

const QString Misc::amountTypeString() const
{
   return amountTypes.at(amountType());
}

const QString Misc::typeStringTr() const
{
   QStringList typesTr = QStringList() << tr("Spice") << tr("Fining") << tr("Water Agent") << tr("Herb") << tr("Flavor") << tr("Other");
   return typesTr.at(type());
}

const QString Misc::useStringTr() const
{
   QStringList usesTr = QStringList() << tr("Boil") << tr("Mash") << tr("Primary") << tr("Secondary") << tr("Bottling");
   return usesTr.at(use());
}

const QString Misc::amountTypeStringTr() const
{
   QStringList amountTypesTr = QStringList() << tr("Weight") << tr("Volume");
   return amountTypesTr.at(amountType());
}

//============================"SET" METHODS=====================================
void Misc::setType( Type t )
{
   getDB()->updateColumn(MiscDB::kTypeColumn, types.at(t) );
}

void Misc::setUse( Use u )
{
   getDB()->updateColumn(MiscDB::kUseColumn, uses.at(u) );
}

void Misc::setAmountType( AmountType t )
{
   setAmountIsWeight(t == AmountType_Weight ? true : false);
}

void Misc::setUseFor( const QString& var )
{
   getDB()->updateColumn(MiscDB::kUseForColumn, var );
}

void Misc::setNotes( const QString& var )
{
   getDB()->updateColumn(MiscDB::kNotesColumn, var );
}

void Misc::setAmountIsWeight( bool var )
{
   getDB()->updateColumn(MiscDB::kAmtIsWeightColumn, var );
}

void Misc::setAmount( double var )
{
   if( var < 0.0 )
      Brewtarget::logW( QString("Misc: amount < 0: %1").arg(var) );
   else
      getDB()->updateColumn(MiscDB::kAmountColumn, var );
}

void Misc::setInventoryAmount( double var )
{
   if( var < 0.0 )
      Brewtarget::logW( QString("Misc: inventory < 0: %1").arg(var) );
   else
      getDB()->updateInventoryColumn(MiscDB::kAmountColumn, var );
}

void Misc::setTime( double var )
{
   if( var < 0.0 )
      Brewtarget::logW( QString("Misc: time < 0: %1").arg(var) );
   else
      getDB()->updateColumn(MiscDB::kTimeColumn, var );
}

//========================OTHER METHODS=========================================

bool Misc::isValidUse( const QString& var )
{
   static const QString uses[] = {"Boil", "Mash", "Primary", "Secondary", "Bottling"};
   static const unsigned int size = 5;
   unsigned int i;
   
   for( i = 0; i < size; ++i )
      if( var == uses[i] )
         return true;
   
   return false;
}

bool Misc::isValidType( const QString& var )
{
   static const QString types[] = {"Spice", "Fining", "Water Agent", "Herb", "Flavor", "Other"};
   static const unsigned int size = 6;
   unsigned int i;
   
   for( i = 0; i < size; ++i )
      if( var == types[i] )
         return true;
   
   return false;
}
