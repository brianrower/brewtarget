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

   connect( this, &FermentableEditor::accepted, this, &FermentableEditor::save );
   connect( this, &FermentableEditor::rejected, this, &FermentableEditor::clearAndClose );

}

void FermentableEditor::connectToFerm(Fermentable* f)
{
   connect( f, &Fermentable::nameChanged, this, &FermentableEditor::onFermNameChanged );
   connect( f, &Fermentable::typeChanged, this, &FermentableEditor::onTypeChanged );
   connect( f, &Fermentable::amountChanged, this, &FermentableEditor::onAmountChanged );
   connect( f, &Fermentable::inventoryChanged, this, &FermentableEditor::onInventoryChanged );
   connect( f, &Fermentable::yieldChanged, this, &FermentableEditor::onYieldChanged );
   connect( f, &Fermentable::originChanged, this, &FermentableEditor::onOriginChanged );
   connect( f, &Fermentable::colorChanged, this, &FermentableEditor::onColorChanged );
   connect( f, &Fermentable::addAfterBoilChanged, this, &FermentableEditor::onAddAfterBoilChanged );
   connect( f, &Fermentable::supplierChanged, this, &FermentableEditor::onSupplierChanged );
   connect( f, &Fermentable::coarseFineDiffChanged, this, &FermentableEditor::onCoarseFineDiffChanged );
   connect( f, &Fermentable::moisturePercentChanged, this, &FermentableEditor::onMoisturePercentChanged );
   connect( f, &Fermentable::diastaticPowerChanged, this, &FermentableEditor::onDiastaticPowerChanged );
   connect( f, &Fermentable::proteinPercentChanged, this, &FermentableEditor::onProteinPercentChanged );
   connect( f, &Fermentable::maxInBatchPercentChanged, this, &FermentableEditor::onMaxInBatchPercent );
   connect( f, &Fermentable::recommendMashChanged, this, &FermentableEditor::onRecommendMashChanged );
   connect( f, &Fermentable::isMashedChanged, this, &FermentableEditor::onIsMashedChanged );
   connect( f, &Fermentable::ibuGalPerLbChanged, this, &FermentableEditor::onIBUGalPerLbChanged );
   connect( f, &Fermentable::noteChanged, this, &FermentableEditor::onNoteChanged );
}

void FermentableEditor::setFermentable( Fermentable* f )
{
   if( _ferm )
      disconnect( _ferm, 0, this, 0 );

   _ferm = f;
   if( _ferm )
   {
      connectToFerm(f);
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

void FermentableEditor::showChanges()
{
   if( !_ferm )
      return;

   onFermNameChanged();
   onTypeChanged();
   onAmountChanged();
   onInventoryChanged();
   onYieldChanged();
   onOriginChanged();
   onColorChanged();
   onAddAfterBoilChanged();
   onSupplierChanged();
   onCoarseFineDiffChanged();
   onMoisturePercentChanged();
   onDiastaticPowerChanged();
   onProteinPercentChanged();
   onMaxInBatchPercent();
   onRecommendMashChanged();
   onIsMashedChanged();
   onIBUGalPerLbChanged();
   onNoteChanged();
}

void FermentableEditor::onFermNameChanged()
{
   lineEdit_name->setText(_ferm->name());
   lineEdit_name->setCursorPosition(0);
}

void FermentableEditor::onTypeChanged()
{
   // NOTE: assumes the comboBox entries are in same order as Fermentable::Type
   comboBox_type->setCurrentIndex(_ferm->type());
}

void FermentableEditor::onAmountChanged()
{
   lineEdit_amount->setText(_ferm);
}

void FermentableEditor::onInventoryChanged()
{
   lineEdit_inventory->setText(_ferm);
}

void FermentableEditor::onYieldChanged()
{
   lineEdit_yield->setText(_ferm);
}

void FermentableEditor::onColorChanged()
{
   lineEdit_color->setText(_ferm, 0);
}

void FermentableEditor::onAddAfterBoilChanged()
{
   checkBox_addAfterBoil->setCheckState( _ferm->addAfterBoil() ? Qt::Checked : Qt::Unchecked );
}

void FermentableEditor::onOriginChanged()
{
   lineEdit_origin->setText(_ferm->origin());
   lineEdit_origin->setCursorPosition(0);
}

void FermentableEditor::onSupplierChanged()
{
   lineEdit_supplier->setText(_ferm->supplier());
   lineEdit_supplier->setCursorPosition(0);
}

void FermentableEditor::onCoarseFineDiffChanged()
{
   lineEdit_coarseFineDiff->setText(_ferm);
}

void FermentableEditor::onMoisturePercentChanged()
{
   lineEdit_moisture->setText(_ferm);
}

void FermentableEditor::onDiastaticPowerChanged()
{
   lineEdit_diastaticPower->setText(_ferm);
}

void FermentableEditor::onProteinPercentChanged()
{
   lineEdit_protein->setText(_ferm);
}

void FermentableEditor::onMaxInBatchPercent()
{
   lineEdit_maxInBatch->setText(_ferm);
}

void FermentableEditor::onRecommendMashChanged()
{
   checkBox_recommendMash->setCheckState( _ferm->recommendMash() ? Qt::Checked : Qt::Unchecked );
}

void FermentableEditor::onIsMashedChanged()
{
   checkBox_isMashed->setCheckState( _ferm->isMashed() ? Qt::Checked : Qt::Unchecked );
}

void FermentableEditor::onIBUGalPerLbChanged()
{
   lineEdit_ibuGalPerLb->setText(_ferm);
}

void FermentableEditor::onNoteChanged()
{
   textEdit_notes->setPlainText( _ferm->notes() );
}
