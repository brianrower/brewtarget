/*
 * instruction.cpp is part of Brewtarget, and is Copyright the following
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

#include "instruction.h"
#include "brewtarget.h"
#include "database.h"
#include "InstructionDB.h"

QHash<QString,QString> Instruction::tagToProp = Instruction::tagToPropHash();

QHash<QString,QString> Instruction::tagToPropHash()
{
   QHash<QString,QString> propHash;
   
   propHash["NAME"] = "name";
   propHash["DIRECTIONS"] = "directions";
   propHash["HAS_TIMER"] = "hasTimer";
   propHash["TIMER_VALUE"] = "timerValue";
   propHash["COMPLETED"] = "completed";
   propHash["INTERVAL"] = "interval";
   
   return propHash;
}

Instruction::Instruction()
   : BeerXMLElement()
{
   setObjectName("Instruction"); 
   _db.reset(new InstructionDB());
}

Instruction::~Instruction()
{
}

ItemDB* Instruction::getDB() const
{
   return _db.get();
}

// Setters ====================================================================
void Instruction::setDirections(const QString& dir)
{
   getDB()->updateColumn(InstructionDB::kDirectionsColumn, dir);
}

void Instruction::setHasTimer(bool has)
{
   getDB()->updateColumn(InstructionDB::kHasTimerColumn, has);
}

void Instruction::setTimerValue(const QString& timerVal)
{
   getDB()->updateColumn(InstructionDB::kTimerValueColumn, timerVal);
}

void Instruction::setCompleted(bool comp)
{
   getDB()->updateColumn(InstructionDB::kCompletedColumn, comp);
}

void Instruction::setInterval(double time) 
{
   getDB()->updateColumn(InstructionDB::kIntervalColumn, time);
}

void Instruction::addReagent(const QString& reagent)
{
   _reagents.append(reagent);
}

// Accessors ==================================================================
QString Instruction::directions() const
{
   return getDB()->getColumn(InstructionDB::kDirectionsColumn).toString();
}

bool Instruction::hasTimer() const
{
   return getDB()->getColumn(InstructionDB::kHasTimerColumn).toBool();
}

QString Instruction::timerValue() const
{
   return getDB()->getColumn(InstructionDB::kTimerValueColumn).toString();
}

bool Instruction::completed() const
{
   return getDB()->getColumn(InstructionDB::kCompletedColumn).toBool();
}

QList<QString> Instruction::reagents() const
{
   return _reagents;
}

double Instruction::interval() const
{
   return getDB()->getColumn(InstructionDB::kIntervalColumn).toDouble();
}

int Instruction::instructionNumber() const
{
   return Database::instance().instructionNumber(this);
}
