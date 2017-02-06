/*
 * water.cpp is part of Brewtarget, and is Copyright the following
 * authors 2009-2014
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

#include <QVector>
#include "water.h"
#include "brewtarget.h"
#include <QDomElement>
#include <QDomText>
#include <QObject>
#include "water.h"
#include "brewtarget.h"
#include "WaterDB.h"

QHash<QString,QString> Water::tagToProp = Water::tagToPropHash();

QHash<QString,QString> Water::tagToPropHash()
{
   QHash<QString,QString> propHash;
   propHash["NAME"] = "name";
   propHash["AMOUNT"] = "amount_l";
   propHash["CALCIUM"] = "calcium_ppm";
   propHash["BICARBONATE"] = "bicarbonate_ppm";
   propHash["SULFATE"] = "sulfate_ppm";
   propHash["CHLORIDE"] = "chloride_ppm";
   propHash["SODIUM"] = "sodium_ppm";
   propHash["MAGNESIUM"] = "magnesium_ppm";
   propHash["PH"] = "ph";
   propHash["NOTES"] = "notes";
   return propHash;
}

bool operator<(Water &w1, Water &w2)
{
   return w1.name() < w2.name();
}

bool operator==(Water &w1, Water &w2)
{
   return w1.name() == w2.name();
}

Water::Water()
   : BeerXMLElement()
{
   _db.reset(new WaterDB());
}

Water::~Water()
{

}

ItemDB* Water::getDB() const
{
   return _db.get();
}

//================================"SET" METHODS=================================
void Water::setAmount_l( double var )
{
   getDB()->updateColumn(WaterDB::kAmountColumn, var);
}

void Water::setCalcium_ppm( double var )
{
   getDB()->updateColumn(WaterDB::kCalciumColumn, var);
}

void Water::setBicarbonate_ppm( double var )
{
   getDB()->updateColumn(WaterDB::kBicarbonateColumn, var);
}

void Water::setChloride_ppm( double var )
{
   getDB()->updateColumn(WaterDB::kChlorideColumn, var);
}

void Water::setSodium_ppm( double var )
{
   getDB()->updateColumn(WaterDB::kSodiumColumn, var);
}

void Water::setMagnesium_ppm( double var )
{
   getDB()->updateColumn(WaterDB::kMagnesiumColumn, var);
}

void Water::setPh( double var )
{
   getDB()->updateColumn(WaterDB::kPhColumn, var);
}

void Water::setSulfate_ppm( double var )
{
   getDB()->updateColumn(WaterDB::kSulfateColumn, var);
}

void Water::setNotes( const QString &var )
{
   getDB()->updateColumn(WaterDB::kNotesColumn, var);
}

//=========================="GET" METHODS=======================================
QString Water::notes() const
{
   return getDB()->getColumn(WaterDB::kNotesColumn).toString();
}

double Water::sulfate_ppm() const
{
   return getDB()->getColumn(WaterDB::kSulfateColumn).toDouble();
}

double Water::amount_l() const
{
   return getDB()->getColumn(WaterDB::kAmountColumn).toDouble();
}

double Water::calcium_ppm() const
{
   return getDB()->getColumn(WaterDB::kCalciumColumn).toDouble();
}

double Water::bicarbonate_ppm() const
{
   return getDB()->getColumn(WaterDB::kBicarbonateColumn).toDouble();
}

double Water::chloride_ppm() const
{
   return getDB()->getColumn(WaterDB::kChlorideColumn).toDouble();
}

double Water::sodium_ppm() const
{
   return getDB()->getColumn(WaterDB::kSodiumColumn).toDouble();
}

double Water::magnesium_ppm() const
{
   return getDB()->getColumn(WaterDB::kMagnesiumColumn).toDouble();
}

double Water::ph() const
{
   return getDB()->getColumn(WaterDB::kPhColumn).toDouble();
}
