/*
 * equipment.cpp is part of Brewtarget, and is Copyright the following
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

#include <QVector>
#include <QDomElement>
#include <QDomText>
#include <QObject>
#include "equipment.h"
#include "brewtarget.h"
#include "HeatCalculations.h"
#include "EquipmentDB.h"

const QString kBoilSizeColumn("boil_size");
const QString kBatchSizeColumn("batch_size");
const QString kTunVolumeColumn("tun_volume");
const QString kTunWeightColumn("tun_weight");
const QString kTunSpecificHeatColumn("tun_specific_heat");
const QString kTopUpWaterColumn("top_up_water");
const QString kTrubChillerLossColumn("trub_chiller_loss");
const QString kEvaporationRateColumn("evap_rate");
const QString kRealEvaporationRateColumn("real_evap_rate");
const QString kBoilTimeColumn("boil_time");
const QString kCalBoilVolumeColumn("calc_boil_volume");
const QString kLauterDeadspaceColumn("lauter_deadspace");
const QString kTopUpKettleColumn("top_up_kettle");
const QString kHopUtilizationColumn("hop_utilization");
const QString kNotesColumn("notes");
const QString kAbsorptionColumn("absorption");
const QString kBoilingPointColumn("boiling_point");

QHash<QString,QString> Equipment::tagToProp = Equipment::tagToPropHash();

QHash<QString,QString> Equipment::tagToPropHash()
{
   QHash<QString,QString> propHash;
   
   propHash["NAME"] = "name";
   propHash["BOIL_SIZE"] = "boilSize_l";
   propHash["BATCH_SIZE"] = "batchSize_l";
   propHash["TUN_VOLUME"] = "tunVolume_l";
   propHash["TUN_WEIGHT"] = "tunWeight_kg";
   propHash["TUN_SPECIFIC_HEAT"] = "tunSpecificHeat_calGC";
   propHash["TOP_UP_WATER"] = "topUpWater_l";
   propHash["TRUB_CHILLER_LOSS"] = "trubChillerLoss_l";
   propHash["EVAP_RATE"] = "evapRate_pctHr";
   propHash["REAL_EVAP_RATE"] = "evapRate_lHr";
   propHash["BOIL_TIME"] = "boilTime_min";
   propHash["CALC_BOIL_VOLUME"] = "calcBoilVolume";
   propHash["LAUTER_DEADSPACE"] = "lauterDeadspace_l";
   propHash["TOP_UP_KETTLE"] = "topUpKettle_l";
   propHash["HOP_UTILIZATION"] = "hopUtilization_pct";
   propHash["NOTES"] = "notes";
   propHash["ABSORPTION"] = "grainAbsorption_LKg";
   propHash["BOILING_POINT"] = "boilingPoint_c";
   
   return propHash;
}

bool operator<(Equipment &e1, Equipment &e2)
{
   return e1.name() < e2.name();
}

bool operator==(Equipment &e1, Equipment &e2)
{
   return e1.name() == e2.name();
}

//=============================CONSTRUCTORS=====================================

/*
void Equipment::setDefaults()
{
   name = "";
   boilSize_l = 0.0;
   batchSize_l = 0.0;
   tunVolume_l = 0.0;
   tunWeight_kg = 0.0;
   tunSpecificHeat_calGC = 0.0;
   topUpWater_l = 0.0;
   trubChillerLoss_l = 0.0;
   evapRate_pctHr = 0.0;
   evapRate_lHr = 0.0;
   boilTime_min = 0.0;
   calcBoilVolume = false;
   lauterDeadspace_l = 0.0;
   topUpKettle_l = 0.0;
   hopUtilization_pct = 0.0;
   notes = "";
   absorption_LKg = HeatCalculations::absorption_LKg;
   boilingPoint_c = 100.0;
}
*/

Equipment::Equipment()
   : BeerXMLElement()
{
   _db.reset(new EquipmentDB());
}

Equipment::Equipment( Equipment const& other )
   : BeerXMLElement(other)
{
   _db.reset(new EquipmentDB());
}

Equipment::~Equipment()
{

}

ItemDB* Equipment::getDB() const
{
   return _db.get();
}

//============================"SET" METHODS=====================================

void Equipment::setBoilSize_l( double var )
{
   if( var < 0.0 )
   {
      Brewtarget::logW( QString("Equipment: boil size negative: %1").arg(var) );
      return;
   }

   getDB()->updateColumn(EquipmentDB::kBoilSizeColumn, var);
   emit changedBoilSize_l(var);
}

void Equipment::setBatchSize_l( double var )
{
   if( var < 0.0 )
   {
      Brewtarget::logW( QString("Equipment: batch size negative: %1").arg(var) );
      return;
   }

   getDB()->updateColumn(EquipmentDB::kBatchSizeColumn, var);
   doCalculations();
   emit batchSizeChanged();
}

void Equipment::setTunVolume_l( double var )
{
   if( var < 0.0 )
   {
      Brewtarget::logW( QString("Equipment: tun volume negative: %1").arg(var) );
      return;
   }

   getDB()->updateColumn(EquipmentDB::kTunVolumeColumn, var);
   emit tunVolumeChanged();
}

void Equipment::setTunWeight_kg( double var )
{
   if( var < 0.0 )
   {
      Brewtarget::logW( QString("Equipment: tun weight negative: %1").arg(var) );
      return;
   }

   getDB()->updateColumn(EquipmentDB::kTunWeightColumn, var);
   emit tunWeightChanged();
}

void Equipment::setTunSpecificHeat_calGC( double var )
{
   if( var < 0.0 )
   {
      Brewtarget::logW( QString("Equipment: tun sp heat negative: %1").arg(var) );
      return;
   }

   getDB()->updateColumn(EquipmentDB::kTunSpecificHeatColumn, var);
   emit tunSpecificHeatChanged();
}

void Equipment::setTopUpWater_l( double var )
{
   if( var < 0.0 )
   {
      Brewtarget::logW( QString("Equipment: top up water negative: %1").arg(var) );
      return;
   }

   getDB()->updateColumn(EquipmentDB::kTopUpWaterColumn, var);
   doCalculations();
   emit topUpWaterChanged();
}

void Equipment::setTrubChillerLoss_l( double var )
{
   if( var < 0.0 )
   {
      Brewtarget::logW( QString("Equipment: trub chiller loss negative: %1").arg(var) );
      return;
   }

   getDB()->updateColumn(EquipmentDB::kTrubChillerLossColumn, var);
   doCalculations();
   emit trubChillerLossChanged();
}

void Equipment::setEvapRate_pctHr( double var )
{
   if( var < 0.0 || var > 100.0)
   {
      Brewtarget::logW( QString("Equipment: 0 < evap rate < 100: %1").arg(var) );
      return;
   }

   getDB()->updateColumn(EquipmentDB::kEvaporationRateColumn, var);
   getDB()->updateColumn(EquipmentDB::kRealEvaporationRateColumn, var/100.0 * batchSize_l() ); // We always use this one, so set it.
   doCalculations();
   emit evaporationRateChanged();
}

void Equipment::setEvapRate_lHr( double var )
{
   if( var < 0.0 )
   {
      Brewtarget::logW( QString("Equipment: evap rate negative: %1").arg(var) );
      return;
   }

   getDB()->updateColumn(EquipmentDB::kRealEvaporationRateColumn, var);
   setEvapRate_pctHr( var/batchSize_l() * 100.0 ); // We don't use it, but keep it current.
   doCalculations();
   emit evaporationRateChanged();
}

void Equipment::setBoilTime_min( double var )
{
   if( var < 0.0 )
   {
      Brewtarget::logW( QString("Equipment: boil time negative: %1").arg(var) );
      return;
   }

   getDB()->updateColumn(EquipmentDB::kBoilTimeColumn, var);
   doCalculations();
   emit changedBoilTime_min(var);
}

void Equipment::setCalcBoilVolume( bool var )
{
   getDB()->updateColumn(EquipmentDB::kCalcBoilVolumeColumn, var);
   if( var )
      doCalculations();
   emit calcBoilVolumeChanged();
}

void Equipment::setLauterDeadspace_l( double var )
{
   if( var < 0.0 )
   {
      Brewtarget::logW( QString("Equipment: deadspace negative: %1").arg(var) );
      return;
   }

   getDB()->updateColumn(EquipmentDB::kLauterDeadspaceColumn, var);
   emit lauterDeadspaceChanged();
}

void Equipment::setTopUpKettle_l( double var )
{
   if( var < 0.0 )
   {
      Brewtarget::logW( QString("Equipment: top up kettle negative: %1").arg(var) );
      return;
   }

   getDB()->updateColumn(EquipmentDB::kTopUpKettleColumn, var);
   emit topUpKettleChanged();
}

void Equipment::setHopUtilization_pct( double var )
{
   if( var < 0.0 )
   {
      Brewtarget::logW( QString("Equipment: 0 < hop utilization: %1").arg(var) );
      return;
   }

   getDB()->updateColumn(EquipmentDB::kHopUtilizationColumn, var);
   emit hopUtilizationChanged();
}

void Equipment::setNotes( const QString &var )
{
   getDB()->updateColumn(EquipmentDB::kNotesColumn, var);
   emit notesChanged();
}

void Equipment::setGrainAbsorption_LKg(double var)
{
   if( var < 0.0 )
   {
      Brewtarget::logW( QString("Equipment: absorption < 0: %1").arg(var) );
      return;
   }

   getDB()->updateColumn(EquipmentDB::kAbsorptionColumn, var);
   emit grainAbsorptionChanged();
}

void Equipment::setBoilingPoint_c(double var)
{
   if ( var < 0.0 )
   {
      Brewtarget::logW( QString("Equipment: boiling point of water < 0: %1").arg(var));
      return;
   }

   getDB()->updateColumn(EquipmentDB::kBoilingPointColumn, var);
   emit boilingPointChanged();
}

//============================"GET" METHODS=====================================

QString Equipment::notes() const                { return getDB()->getColumn(EquipmentDB::kNotesColumn).toString(); }
bool Equipment::calcBoilVolume() const          { return getDB()->getColumn(EquipmentDB::kCalcBoilVolumeColumn).toBool(); }
double Equipment::boilSize_l() const            { return getDB()->getColumn(EquipmentDB::kBoilSizeColumn).toDouble(); }
double Equipment::batchSize_l() const           { return getDB()->getColumn(EquipmentDB::kBatchSizeColumn).toDouble(); }
double Equipment::tunVolume_l() const           { return getDB()->getColumn(EquipmentDB::kTunVolumeColumn).toDouble(); }
double Equipment::tunWeight_kg() const          { return getDB()->getColumn(EquipmentDB::kTunWeightColumn).toDouble(); }
double Equipment::tunSpecificHeat_calGC() const { return getDB()->getColumn(EquipmentDB::kTunSpecificHeatColumn).toDouble(); }
double Equipment::topUpWater_l() const          { return getDB()->getColumn(EquipmentDB::kTopUpWaterColumn).toDouble(); }
double Equipment::trubChillerLoss_l() const     { return getDB()->getColumn(EquipmentDB::kTrubChillerLossColumn).toDouble(); }
double Equipment::evapRate_pctHr() const        { return getDB()->getColumn(EquipmentDB::kEvaporationRateColumn).toDouble(); }
double Equipment::evapRate_lHr() const          { return getDB()->getColumn(EquipmentDB::kRealEvaporationRateColumn).toDouble(); }
double Equipment::boilTime_min() const          { return getDB()->getColumn(EquipmentDB::kBoilTimeColumn).toDouble(); }
double Equipment::lauterDeadspace_l() const     { return getDB()->getColumn(EquipmentDB::kLauterDeadspaceColumn).toDouble(); }
double Equipment::topUpKettle_l() const         { return getDB()->getColumn(EquipmentDB::kTopUpKettleColumn).toDouble(); }
double Equipment::hopUtilization_pct() const    { return getDB()->getColumn(EquipmentDB::kHopUtilizationColumn).toDouble(); }
double Equipment::grainAbsorption_LKg()         { return getDB()->getColumn(EquipmentDB::kAbsorptionColumn).toDouble(); }
double Equipment::boilingPoint_c() const        { return getDB()->getColumn(EquipmentDB::kBoilingPointColumn).toDouble(); }

void Equipment::doCalculations()
{
   // Only do the calculation if we're asked to.
   if( ! calcBoilVolume() )
      return;

   setBoilSize_l( batchSize_l() - topUpWater_l() + trubChillerLoss_l() + (boilTime_min()/(double)60)*evapRate_lHr());
}

double Equipment::wortEndOfBoil_l( double kettleWort_l ) const
{
   //return kettleWort_l * (1 - (boilTime_min/(double)60) * (evapRate_pctHr/(double)100) );

   return kettleWort_l - (boilTime_min()/(double)60)*evapRate_lHr();
}
