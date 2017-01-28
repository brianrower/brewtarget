/*
 * FermentableEditor.cpp is part of Brewtarget, and is Copyright the following
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

#include <QIcon>
#include "FermentableEditor.h"
#include "fermentable.h"
#include "database.h"
#include "config.h"
#include "unit.h"
#include "brewtarget.h"

FermentableEditor::FermentableEditor( QWidget* parent )
        : QDialog(parent), _ferm(0)
{
   setupUi(this);

   connect( this, SIGNAL( accepted() ), this, SLOT( save() ));
   connect( this, SIGNAL( rejected() ), this, SLOT( clearAndClose() ));

}

void FermentableEditor::setFermentable( Fermentable* f )
{
   if( _ferm )
      disconnect( _ferm, 0, this, 0 );

   _ferm = f;
   if( _ferm )
   {
      connect( _ferm, SIGNAL(changed(QMetaProperty,QVariant)), this, SLOT(changed(QMetaProperty,QVariant)) );
      showChanges();
   }
}

void FermentableEditor::save()
{
   if( _ferm == 0 )
   {
      setVisible(false);
      return;
   }

   _ferm->setName(lineEdit_name->text());

   // NOTE: the following assumes that Fermentable::Type is enumerated in the same
   // order as the combobox.
   _ferm->setType( static_cast<Fermentable::Type>(comboBox_type->currentIndex()) );
   _ferm->setAmount_kg(lineEdit_amount->toSI());
   _ferm->setInventoryAmount(lineEdit_inventory->toSI());
   _ferm->setYield_pct(lineEdit_yield->toSI());
   _ferm->setColor_srm(lineEdit_color->toSI());
   _ferm->setAddAfterBoil( (checkBox_addAfterBoil->checkState() == Qt::Checked)? true : false );
   _ferm->setOrigin( lineEdit_origin->text() );
   _ferm->setSupplier( lineEdit_supplier->text() );
   _ferm->setCoarseFineDiff_pct( lineEdit_coarseFineDiff->toSI() );
   _ferm->setMoisture_pct( lineEdit_moisture->toSI() );
   _ferm->setDiastaticPower_lintner( lineEdit_diastaticPower->toSI() );
   _ferm->setProtein_pct( lineEdit_protein->toSI() );
   _ferm->setMaxInBatch_pct( lineEdit_maxInBatch->toSI() );
   _ferm->setRecommendMash( (checkBox_recommendMash->checkState() == Qt::Checked) ? true : false );
   _ferm->setIsMashed( (checkBox_isMashed->checkState() == Qt::Checked) ? true : false );
   _ferm->setIbuGalPerLb( lineEdit_ibuGalPerLb->toSI() );
   _ferm->setNotes( textEdit_notes->toPlainText() );

   setVisible(false);
}

void FermentableEditor::clearAndClose()
{
   setFermentable(0);
   setVisible(false); // Hide the window.
}

void FermentableEditor::changed(QMetaProperty prop, QVariant /*val*/)
{
   if( sender() == _ferm )
      showChanges(&prop);
}

void FermentableEditor::showChanges(QMetaProperty* metaProp)
{
   if( _ferm == 0 )
      return;

   QString propName;
   bool updateAll = false;
   if( metaProp == 0 )
      updateAll = true;
   else
   {
      propName = metaProp->name();
   }

   if( propName == "name" || updateAll )
   {
      lineEdit_name->setText(_ferm->name());
      lineEdit_name->setCursorPosition(0);
      if( ! updateAll )
         return;
   }
   if( propName == "type" || updateAll) {
      // NOTE: assumes the comboBox entries are in same order as Fermentable::Type
      comboBox_type->setCurrentIndex(_ferm->type());
       if( ! updateAll )
         return;
   }
   if( propName == "amount_kg" || updateAll) {
      lineEdit_amount->setText(_ferm);
      if( ! updateAll )
         return;
   }

   if( propName == "inventory" || updateAll) {
      lineEdit_inventory->setText(_ferm);
      if( ! updateAll )
         return;
   }
   if( propName == "yield_pct" || updateAll) {
      lineEdit_yield->setText(_ferm);
      if( ! updateAll )
         return;
   }
   if( propName == "color_srm" || updateAll) {
      lineEdit_color->setText(_ferm, 0);
       if( ! updateAll )
         return;
   }
   if( propName == "addAfterBoil" || updateAll) {
      checkBox_addAfterBoil->setCheckState( _ferm->addAfterBoil() ? Qt::Checked : Qt::Unchecked );
       if( ! updateAll )
         return;
   }
   if( propName == "origin" || updateAll)
   {
      lineEdit_origin->setText(_ferm->origin());
      lineEdit_origin->setCursorPosition(0);
      if( ! updateAll )
         return;
   }
   if( propName == "supplier" || updateAll)
   {
      lineEdit_supplier->setText(_ferm->supplier());
      lineEdit_supplier->setCursorPosition(0);
       if( ! updateAll )
         return;
   }
   if( propName == "coarseFineDiff_pct" || updateAll) {
      lineEdit_coarseFineDiff->setText(_ferm);
      if( ! updateAll )
         return;
   }
   if( propName == "moisture_pct" || updateAll) {
      lineEdit_moisture->setText(_ferm);
      if( ! updateAll )
         return;
   }
   if( propName == "diastaticPower_lintner" || updateAll) {
      lineEdit_diastaticPower->setText(_ferm);
      if( ! updateAll )
         return;
   }
   if( propName == "protein_pct" || updateAll) {
      lineEdit_protein->setText(_ferm);
      if( ! updateAll )
         return;
   }
   if( propName == "maxInBatch_pct" || updateAll) {
      lineEdit_maxInBatch->setText(_ferm);
      if( ! updateAll )
         return;
   }
   if( propName == "recommendMash" || updateAll) {
      checkBox_recommendMash->setCheckState( _ferm->recommendMash() ? Qt::Checked : Qt::Unchecked );
      if( ! updateAll )
         return;
   }
   if( propName == "isMashed" || updateAll) {
      checkBox_isMashed->setCheckState( _ferm->isMashed() ? Qt::Checked : Qt::Unchecked );
       if( ! updateAll )
         return;
   }
   if( propName == "ibuGalPerLb" || updateAll) {
      lineEdit_ibuGalPerLb->setText(_ferm);
      if( ! updateAll )
         return;
   }
   if( propName == "notes" || updateAll) {
      textEdit_notes->setPlainText( _ferm->notes() );
      if( ! updateAll )
         return;
   }
}
