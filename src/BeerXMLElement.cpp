/*
 * BeerXMLElement.cpp is part of Brewtarget, and is Copyright the following
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

#include "BeerXMLElement.h"
#include <QDomElement>
#include <QDomNode>
#include <QMetaProperty>
#include "brewtarget.h"
#include "database.h"
#include "ItemDB.h"

BeerXMLElement::BeerXMLElement()
   : QObject(0),
     _key(-1),
     _table(Brewtarget::NOTABLE),
     _folder(QString())
{
   _valid = true;
}

BeerXMLElement::BeerXMLElement(BeerXMLElement const& other)
   : QObject(0),
   _key(other._key),
   _table(other._table),
   _folder(QString())
{
   _valid = true;
}

bool BeerXMLElement::deleted() const
{
   return getDB()->getDeleted();
}

bool BeerXMLElement::display() const
{
   return getDB()->getDisplay();
}

// Sigh. New databases, more complexity
void BeerXMLElement::setDeleted(const bool var)
{
   getDB()->setDeleted(var);
}

void BeerXMLElement::setDisplay(bool var)
{
   getDB()->setDisplay(var);
}

QString BeerXMLElement::folder() const
{
   return getDB()->getFolder();
}

void BeerXMLElement::setFolder(const QString& var, bool signal)
{
   getDB()->setFolder(var);
   if ( signal )
      emit changedFolder(var);
}

QString BeerXMLElement::name() const
{
   return getDB()->getName();
}

void BeerXMLElement::setName(const QString newName)
{
   getDB()->setName(newName);
   emit changedName(newName);
}

void BeerXMLElement::remove()
{
   getDB()->remove();
}

int BeerXMLElement::key() const { return _key; }

Brewtarget::DBTable BeerXMLElement::table() const{ return _table; }

int BeerXMLElement::version() const { return QString(metaObject()->classInfo(metaObject()->indexOfClassInfo("version")).value()).toInt(); }

QMetaProperty BeerXMLElement::metaProperty(const char* name) const
{
   return metaObject()->property(metaObject()->indexOfProperty(name));
}

QMetaProperty BeerXMLElement::metaProperty(QString const& name) const
{
   return metaObject()->property(metaObject()->indexOfProperty(name.toStdString().c_str()));
}

// getVal =====================================================================
double BeerXMLElement::getDouble(const QDomText& textNode)
{
   bool ok;
   double ret;

   QString text = textNode.nodeValue();

   // ret = text.toDouble(&ok);
   ret = Brewtarget::toDouble(text,&ok);
   if( !ok )
      Brewtarget::logE(QString("BeerXMLElement::getDouble: %1 is not a number. Line %2").arg(text).arg(textNode.lineNumber()) );

   return ret;
}

bool BeerXMLElement::getBool(const QDomText& textNode)
{
   QString text = textNode.nodeValue();

   if( text == "TRUE" )
      return true;
   else if( text == "FALSE" )
      return false;
   else
      Brewtarget::logE(QString("BeerXMLElement::getBool: %1 is not a boolean value. Line %2").arg(text).arg(textNode.lineNumber()) );

   return false;
}

int BeerXMLElement::getInt(const QDomText& textNode)
{
   bool ok;
   int ret;
   QString text = textNode.nodeValue();

   ret = text.toInt(&ok);
   if( !ok )
      Brewtarget::logE(QString("BeerXMLElement::getInt: %1 is not an integer. Line %2").arg(text).arg(textNode.lineNumber()) );

   return ret;
}

QString BeerXMLElement::getString( QDomText const& textNode )
{
   return textNode.nodeValue();
}

QDateTime BeerXMLElement::getDateTime( QDomText const& textNode )
{
   bool ok = true;
   QDateTime ret;
   QString text = textNode.nodeValue();

   ret = QDateTime::fromString(text, Qt::ISODate);
   ok = ret.isValid();
   if( !ok )
      Brewtarget::logE(QString("BeerXMLElement::getDateTime: %1 is not a date. Line %2").arg(text).arg(textNode.lineNumber()) );

   return ret;
}

QDate BeerXMLElement::getDate( QDomText const& textNode )
{
   bool ok = true;
   QDate ret;
   QString text = textNode.nodeValue();

   ret = QDate::fromString(text, "M/d/yyyy");
   ok = ret.isValid();
   // Dates have some odd inconsistencies.
   if( !ok )
   {
      ret = QDate::fromString(text,"d/M/yyyy");
      ok = ret.isValid();
   }

   if ( !ok )
      Brewtarget::logE(QString("BeerXMLElement::getDate: %1 is not an ISO date-time. Line %2").arg(text).arg(textNode.lineNumber()) );

   return ret;
}

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

QDateTime BeerXMLElement::getDateTime(QString const& str)
{
   QDateTime temp;

   if ( str != "" && (temp = QDateTime::fromString(str, Qt::ISODate)).isValid() )
      return temp;
   else
      return QDateTime::currentDateTime();
}

QString BeerXMLElement::text(bool val)
{
   if( val )
      return QString("TRUE");
   else
      return QString("FALSE");
}

QString BeerXMLElement::text(double val)
{
   return QString("%1").arg(val, 0, 'f', 8);
}

QString BeerXMLElement::text(int val)
{
   return QString("%1").arg(val);
}

QString BeerXMLElement::text(QDate const& val)
{
   return val.toString(Qt::ISODate);
}

bool BeerXMLElement::isValid()
{
   return _valid;
}

void BeerXMLElement::invalidate()
{
   _valid = false;
}
