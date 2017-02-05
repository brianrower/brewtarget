/*
 * mashstep.cpp is part of Brewtarget, and is Copyright the following
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
#include "mashstep.h"
#include "brewtarget.h"
#include "MashStepDB.h"

QStringList MashStep::types = QStringList() << "Infusion" << "Temperature" << "Decoction" << "Fly Sparge" << "Batch Sparge";
QStringList MashStep::typesTr = QStringList() << QObject::tr("Infusion") << QObject::tr("Temperature") << QObject::tr("Decoction") << QObject::tr("Fly Sparge") << QObject::tr("Batch Sparge");

QHash<QString,QString> MashStep::tagToProp = MashStep::tagToPropHash();

QHash<QString,QString> MashStep::tagToPropHash()
{
   QHash<QString,QString> propHash;
   propHash["NAME"] = "name";
   //propHash["TYPE"] = "type";
   propHash["INFUSE_AMOUNT"] = "infuseAmount_l";
   propHash["STEP_TEMP"] = "stepTemp_c";
   propHash["STEP_TIME"] = "stepTime_min";
   propHash["RAMP_TIME"] = "rampTime_min";
   propHash["END_TEMP"] = "endTemp_c";
   propHash["INFUSE_TEMP"] = "infuseTemp_c";
   propHash["DECOCTION_AMOUNT"] = "decoctionAmount_l";
   return propHash;
}

bool operator<(MashStep &m1, MashStep &m2)
{
   return m1.name() < m2.name();
}

bool operator==(MashStep &m1, MashStep &m2)
{
   return m1.name() == m2.name();
}

//==============================CONSTRUCTORS====================================

MashStep::MashStep()
   : BeerXMLElement()
{
   _db.reset(new MashStepDB());
}

MashStep::~MashStep()
{
}

ItemDB* MashStep::getDB() const
{
   return _db.get();
}

//================================"SET" METHODS=================================
void MashStep::setInfuseTemp_c(double var)
{
   getDB()->updateColumn(MashStepDB::kInfuseTempColumn, var);
}

void MashStep::setType( Type t )
{
   getDB()->updateColumn(MashStepDB::kTypeColumn, types.at(t));
}

void MashStep::setInfuseAmount_l( double var )
{
   if( var < 0.0 )
   {
      Brewtarget::logW( QString("%1 number cannot be negative: %2").arg(Q_FUNC_INFO).arg(var) );
      return;
   }

   getDB()->updateColumn(MashStepDB::kInfuseAmtColumn, var);
}

void MashStep::setStepTemp_c( double var )
{
   if( var < -273.15 )
   {
      Brewtarget::logW( QString("%1: temp below absolute zero: %2").arg(Q_FUNC_INFO).arg(var) );
      return;
   }

   getDB()->updateColumn(MashStepDB::kStepTempColumn, var);
}

void MashStep::setStepTime_min( double var )
{
   if( var < 0.0 )
   {
      Brewtarget::logW( QString("%1: step time cannot be negative: %2").arg(Q_FUNC_INFO).arg(var) );
      return;
   }

   getDB()->updateColumn(MashStepDB::kStepTimeColumn, var);
}

void MashStep::setRampTime_min( double var )
{
   if( var < 0.0 )
   {
      Brewtarget::logW( QString("%1: ramp time cannot be negative: %2").arg(Q_FUNC_INFO).arg(var) );
      return;
   }

   getDB()->updateColumn(MashStepDB::kRampTimeColumn, var);
}

void MashStep::setEndTemp_c( double var )
{
   if( var < -273.15 )
   {
      Brewtarget::logW( QString("%1: temp below absolute zero: %2").arg(Q_FUNC_INFO).arg(var) );
      return;
   }

   getDB()->updateColumn(MashStepDB::kEndTempColumn, var);
}

void MashStep::setDecoctionAmount_l(double var)
{
   getDB()->updateColumn(MashStepDB::kDecoctionAmountColumn, var);
}

//============================="GET" METHODS====================================
MashStep::Type MashStep::type() const
{
   return static_cast<MashStep::Type>(types.indexOf(typeString()));
}

const QString MashStep::typeString() const
{
   return getDB()->getColumn(MashStepDB::kTypeColumn).toString();
}

const QString MashStep::typeStringTr() const
{
   return typesTr.at(type());
}

double MashStep::infuseTemp_c() const
{
   return getDB()->getColumn(MashStepDB::kInfuseTempColumn).toDouble();
}

double MashStep::infuseAmount_l() const
{
   return getDB()->getColumn(MashStepDB::kInfuseAmtColumn).toDouble();
}

double MashStep::stepTemp_c() const
{
   return getDB()->getColumn(MashStepDB::kStepTempColumn).toDouble();
}

double MashStep::stepTime_min() const
{
   return getDB()->getColumn(MashStepDB::kStepTimeColumn).toDouble();
}

double MashStep::rampTime_min() const
{
   return getDB()->getColumn(MashStepDB::kRampTimeColumn).toDouble();
}

double MashStep::endTemp_c() const
{
   return getDB()->getColumn(MashStepDB::kEndTempColumn).toDouble();
}

double MashStep::decoctionAmount_l() const
{
   return getDB()->getColumn(MashStepDB::kDecoctionAmountColumn).toDouble();
}

int MashStep::stepNumber() const
{
   return getDB()->getColumn(MashStepDB::kStepNumberColumn).toInt();
}

bool MashStep::isInfusion() const
{
   MashStep::Type _type = type();
   return ( _type == MashStep::Infusion    ||
            _type == MashStep::batchSparge ||
            _type == MashStep::flySparge );
}

bool MashStep::isSparge() const
{
   MashStep::Type _type = type();
   return ( _type == MashStep::batchSparge ||
            _type == MashStep::flySparge   || 
            name() == "Final Batch Sparge" );
}

bool MashStep::isTemperature() const
{
   MashStep::Type _type = type();
   return ( _type == MashStep::Temperature );
}

bool MashStep::isDecoction() const
{
   MashStep::Type _type = type();
   return ( _type == MashStep::Decoction );
}

bool MashStep::isValidType( const QString &str ) const
{
   return MashStep::types.contains(str);
}
