/*
 * hop.cpp is part of Brewtarget, and is Copyright the following
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
#include <QObject>
#include "hop.h"
#include "brewtarget.h"
#include "HopsDB.h"

QStringList Hop::types = QStringList() << "Bittering" << "Aroma" << "Both";
QStringList Hop::forms = QStringList() << "Leaf" << "Pellet" << "Plug";
QStringList Hop::uses = QStringList() << "Mash" << "First Wort" << "Boil" << "Aroma" << "Dry Hop";
QHash<QString,QString> Hop::tagToProp = Hop::tagToPropHash();

QHash<QString,QString> Hop::tagToPropHash()
{
   QHash<QString,QString> propHash;
   
   propHash["NAME"] = "name";
   propHash["ALPHA"] = "alpha_pct";
   propHash["AMOUNT"] = "amount_kg";
   propHash["INVENTORY"] = "inventory";
   //propHash["USE"] = "use";
   propHash["TIME"] = "time_min";
   propHash["NOTES"] = "notes";
   //propHash["TYPE"] = "type";
   //propHash["FORM"] = "form";
   propHash["BETA"] = "beta_pct";
   propHash["HSI"] = "hsi_pct";
   propHash["ORIGIN"] = "origin";
   propHash["SUBSTITUTES"] = "substitutes";
   propHash["HUMULENE"] = "humulene_pct";
   propHash["CARYOPHYLLENE"] = "caryophyllene_pct";
   propHash["COHUMULONE"] = "cohumulone_pct";
   propHash["MYRCENE"] = "myrcene_pct";
   return propHash;
}

bool operator<( Hop &h1, Hop &h2 )
{
   return h1.name() < h2.name();
}

bool operator==( Hop &h1, Hop &h2 )
{
   return h1.name() == h2.name();
}

bool Hop::isValidUse(const QString& str)
{
   return (uses.indexOf(str) >= 0);
}

bool Hop::isValidType(const QString& str)
{
   return (types.indexOf(str) >= 0);
}

bool Hop::isValidForm(const QString& str)
{
   return (forms.indexOf(str) >= 0);
}

Hop::Hop()
   : BeerIngredient()
{
   _db.reset(new HopsDB());
}

Hop::Hop( Hop const& other )
   : BeerIngredient(other)
{
   _db.reset(new HopsDB());
}

Hop::~Hop()
{

}

ItemDB* Hop::getDB() const
{
   return _db.get();
}

//============================="SET" METHODS====================================
void Hop::setAlpha_pct( double num )
{
   if( num < 0.0 || num > 100.0 )
   {
      Brewtarget::logW( QString("Hop: 0 < alpha < 100: %1").arg(num) );
      return;
   }

   getDB()->updateColumn(HopsDB::kAlphaColumn, num);
   emit alphaChanged();
}

void Hop::setAmount_kg( double num )
{
   if( num < 0.0 )
   {
      Brewtarget::logW( QString("Hop: amount < 0: %1").arg(num) );
      return;
   }

   getDB()->updateColumn(HopsDB::kAmountColumn, num);
   emit amountChanged();
}

void Hop::setInventoryAmount( double num )
{
   if( num < 0.0 )
   {
      Brewtarget::logW( QString("Hop: inventory < 0: %1").arg(num) );
      return;
   }

   getDB()->updateInventoryColumn(HopsDB::kAmountColumn, num);
   emit inventoryChanged();
}

void Hop::setUse(Use u)
{
   if ( u >= 0 ) {
      getDB()->updateColumn(HopsDB::kUseColumn, uses.at(u));
      emit useChanged();
   }
}

void Hop::setTime_min( double num )
{
   if( num < 0.0 )
   {
      Brewtarget::logW( QString("Hop: time < 0: %1").arg(num) );
      return;
   }
   getDB()->updateColumn(HopsDB::kTimeColumn, num);
   emit timeChanged();
}
      
void Hop::setNotes( const QString& str )
{
   getDB()->updateColumn(HopsDB::kNotesColumn, str);
   emit notesChanged();
}

void Hop::setType(Type t)
{
   if ( t >= 0 ) {
      getDB()->updateColumn(HopsDB::kTypeColumn, types.at(t));
      emit typeChanged();
   }
}

void Hop::setForm( Form f )
{
   if ( f >= 0 ) {
      getDB()->updateColumn(HopsDB::kFormColumn, forms.at(f));
      emit formChanged();
   }
}

void Hop::setBeta_pct( double num )
{
   if( num < 0.0 || num > 100.0 )
   {
      Brewtarget::logW( QString("Hop: 0 < beta < 100: %1").arg(num) );
      return;
   }

   getDB()->updateColumn(HopsDB::kBetaColumn, num);
   emit betaChanged();
}

void Hop::setHsi_pct( double num )
{
   if( num < 0.0 || num > 100.0 )
   {
      Brewtarget::logW( QString("Hop: 0 < hsi < 100: %1").arg(num) );
      return;
   }

   getDB()->updateColumn(HopsDB::kHSIColumn, num);
   emit hsiChanged();
}

void Hop::setOrigin( const QString& str )
{
   getDB()->updateColumn(HopsDB::kOriginColumn, str);
   emit originChanged();
}

void Hop::setSubstitutes( const QString& str )
{
   getDB()->updateColumn(HopsDB::kSubstitutesColumn, str);
   emit substitutesChanged();
}

void Hop::setHumulene_pct( double num )
{
   if( num < 0.0 || num > 100.0 )
   {
      Brewtarget::logW( QString("Hop: 0 < humulene < 100: %1").arg(num) );
      return;
   }

   getDB()->updateColumn(HopsDB::kHumuleneColumn, num);
   emit humuleneChanged();
}

void Hop::setCaryophyllene_pct( double num )
{
   if( num < 0.0 || num > 100.0 )
   {
      Brewtarget::logW( QString("Hop: 0 < cary < 100: %1").arg(num) );
      return;
   }
   getDB()->updateColumn(HopsDB::kCaryophylleneColumn, num);
   emit caryophylleneChanged();
}

void Hop::setCohumulone_pct( double num )
{
   if( num < 0.0 || num > 100.0 )
   {
      Brewtarget::logW( QString("Hop: 0 < cohumulone < 100: %1").arg(num) );
      return;
   }

   getDB()->updateColumn(HopsDB::kCohumuloneColumn, num);
   emit cohumuloneChanged();
}

void Hop::setMyrcene_pct( double num )
{
   if( num < 0.0 || num > 100.0 )
   {
      Brewtarget::logW( QString("Hop: 0 < myrcene < 100: %1").arg(num) );
      return;
   }
   getDB()->updateColumn(HopsDB::kMyrceneColumn, num);
   emit myrceneChanged();
}

//============================="GET" METHODS====================================

Hop::Use Hop::use() const
{
   return static_cast<Hop::Use>(uses.indexOf(useString()));
}

const QString Hop::useString() const
{
   return getDB()->getColumn(HopsDB::kUseColumn).toString();
}

Hop::Form Hop::form() const
{
   QString form = getDB()->getColumn(HopsDB::kFormColumn).toString();
   return static_cast<Hop::Form>(forms.indexOf(form));
}

const QString Hop::notes() const
{
   return getDB()->getColumn(HopsDB::kNotesColumn).toString();
}

Hop::Type Hop::type() const
{
   return static_cast<Hop::Type>(types.indexOf(typeString()));
}

const QString Hop::typeString() const
{
   return getDB()->getColumn(HopsDB::kTypeColumn).toString();
}

const QString Hop::formString() const
{
   return getDB()->getColumn(HopsDB::kFormColumn).toString();
}

const QString Hop::origin() const
{
   return getDB()->getColumn(HopsDB::kOriginColumn).toString();
}

const QString Hop::substitutes() const
{
   return getDB()->getColumn(HopsDB::kSubstitutesColumn).toString();
}


double Hop::alpha_pct() const
{
   return getDB()->getColumn(HopsDB::kAlphaColumn).toDouble();
}

double Hop::amount_kg() const
{
   return getDB()->getColumn(HopsDB::kAmountColumn).toDouble();
}

double Hop::time_min() const
{
   return getDB()->getColumn(HopsDB::kTimeColumn).toDouble();
}

double Hop::beta_pct() const
{
   return getDB()->getColumn(HopsDB::kBetaColumn).toDouble();
}

double Hop::hsi_pct() const
{
   return getDB()->getColumn(HopsDB::kHSIColumn).toDouble();
}

double Hop::humulene_pct() const
{
   return getDB()->getColumn(HopsDB::kHumuleneColumn).toDouble();
}

double Hop::caryophyllene_pct() const
{
   return getDB()->getColumn(HopsDB::kCaryophylleneColumn).toDouble();
}

double Hop::cohumulone_pct() const
{
   return getDB()->getColumn(HopsDB::kCohumuloneColumn).toDouble();
}

double Hop::myrcene_pct() const
{
   return getDB()->getColumn(HopsDB::kMyrceneColumn).toDouble();
}

// inventory still must be handled separately, and I'm still annoyed.
double Hop::inventory() const
{
   return getDB()->getInventoryColumn(HopsDB::kAmountColumn).toDouble();
}

const QString Hop::useStringTr() const
{
   static QStringList usesTr = QStringList() << tr("Mash") << tr("First Wort") << tr("Boil") << tr("Aroma") << tr("Dry Hop") ;
   return usesTr.at(use());
}

const QString Hop::typeStringTr() const
{
   static QStringList typesTr = QStringList() << tr("Bittering") << tr("Aroma") << tr("Both");
   return typesTr.at(type());
}

const QString Hop::formStringTr() const
{
   static QStringList formsTr = QStringList() << tr("Leaf") << tr("Pellet") << tr("Plug");
   return formsTr.at(form());
}

