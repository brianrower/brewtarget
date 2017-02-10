/*
 * HopEditor.cpp is part of Brewtarget, and is Copyright the following
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

#include <QtGui>
#include <QIcon>
#include "hop.h"
#include "HopEditor.h"
#include "database.h"
#include "config.h"
#include "unit.h"
#include "brewtarget.h"

HopEditor::HopEditor( QWidget* parent )
   : QDialog(parent), obsHop(0)
{
   setupUi(this);
   
   connect( buttonBox, &QDialogButtonBox::accepted, this, &HopEditor::save );
   connect( buttonBox, &QDialogButtonBox::rejected, this, &HopEditor::clearAndClose);
}

void HopEditor::connectToHop(Hop* h)
{
   connect(h, &Hop::nameChanged, this, &HopEditor::onNameChanged );
   connect(h, &Hop::alphaChanged, this, &HopEditor::onAlphaChanged );
   connect(h, &Hop::amountChanged, this, &HopEditor::onAmountChanged );
   connect(h, &Hop::inventoryChanged, this, &HopEditor::onInventoryChanged );
   connect(h, &Hop::useChanged, this, &HopEditor::onUseChanged );
   connect(h, &Hop::timeChanged, this, &HopEditor::onTimeChanged );
   connect(h, &Hop::typeChanged, this, &HopEditor::onTypeChanged );
   connect(h, &Hop::formChanged, this, &HopEditor::onFormChanged );
   connect(h, &Hop::betaChanged, this, &HopEditor::onBetaChanged );
   connect(h, &Hop::hsiChanged, this, &HopEditor::onHSIChanged );
   connect(h, &Hop::originChanged, this, &HopEditor::onOriginChanged );
   connect(h, &Hop::humuleneChanged, this, &HopEditor::onHumuleneChanged );
   connect(h, &Hop::caryophylleneChanged, this, &HopEditor::onCaryophylleneChanged );
   connect(h, &Hop::cohumuloneChanged, this, &HopEditor::onCohumuloneChanged );
   connect(h, &Hop::myrceneChanged, this, &HopEditor::onMyrceneChanged );
   connect(h, &Hop::substitutesChanged, this, &HopEditor::onSubstitutesChanged );
   connect(h, &Hop::notesChanged, this, &HopEditor::onNotesChanged );
}

void HopEditor::setHop( Hop* h )
{
   if( obsHop )
      disconnect( obsHop, 0, this, 0 );
   
   obsHop = h;
   if( obsHop )
   {
      connectToHop(obsHop);
      showChanges();
   }
}

void HopEditor::save()
{
   Hop* h = obsHop;

   if( h == 0 )
   {
      setVisible(false);
      return;
   }

   // TODO: check this out with 1.2.5.
   // Need to disable notification since every "set" method will cause a "showChanges" that
   // will revert any changes made.

   h->setName(lineEdit_name->text());
   h->setAlpha_pct(lineEdit_alpha->toSI());
   h->setAmount_kg(lineEdit_amount->toSI());
   h->setInventoryAmount(lineEdit_inventory->toSI());
   h->setUse(static_cast<Hop::Use>(comboBox_use->currentIndex()));
   h->setTime_min(lineEdit_time->toSI());
   h->setType(static_cast<Hop::Type>(comboBox_type->currentIndex()));
   h->setForm(static_cast<Hop::Form>(comboBox_form->currentIndex()));
   h->setBeta_pct(lineEdit_beta->toSI());
   h->setHsi_pct(lineEdit_HSI->toSI());
   h->setOrigin(lineEdit_origin->text());
   h->setHumulene_pct(lineEdit_humulene->toSI());
   h->setCaryophyllene_pct(lineEdit_caryophyllene->toSI());
   h->setCohumulone_pct(lineEdit_cohumulone->toSI());
   h->setMyrcene_pct(lineEdit_myrcene->toSI());

   h->setSubstitutes(textEdit_substitutes->toPlainText());
   h->setNotes(textEdit_notes->toPlainText());

   setVisible(false);
}

void HopEditor::clearAndClose()
{
   setHop(0);
   setVisible(false); // Hide the window.
}

void HopEditor::showChanges()
{
   onNameChanged();
   onAlphaChanged();
   onAmountChanged();
   onInventoryChanged();
   onUseChanged();
   onTimeChanged();
   onTypeChanged();
   onFormChanged();
   onBetaChanged();
   onHSIChanged();
   onOriginChanged();
   onHumuleneChanged();
   onCaryophylleneChanged();
   onCohumuloneChanged();
   onMyrceneChanged();
   onSubstitutesChanged();
   onNotesChanged();
}

void HopEditor::onNameChanged()
{
   lineEdit_name->setText(obsHop->name());
   lineEdit_name->setCursorPosition(0);
}

void HopEditor::onAlphaChanged()
{
   lineEdit_alpha->setText(obsHop);
}

void HopEditor::onAmountChanged()
{
   lineEdit_amount->setText(obsHop);
}

void HopEditor::onInventoryChanged()
{
   lineEdit_inventory->setText(obsHop);
}

void HopEditor::onUseChanged()
{
   comboBox_use->setCurrentIndex(obsHop->use());
}

void HopEditor::onTimeChanged()
{
   lineEdit_time->setText(obsHop);
}

void HopEditor::onTypeChanged()
{
   comboBox_type->setCurrentIndex(obsHop->type());
}

void HopEditor::onFormChanged()
{
   comboBox_form->setCurrentIndex(obsHop->form());
}

void HopEditor::onBetaChanged()
{
   lineEdit_beta->setText(obsHop);
}

void HopEditor::onHSIChanged()
{
   lineEdit_HSI->setText(obsHop);
}

void HopEditor::onOriginChanged()
{
   lineEdit_origin->setText(obsHop->origin());
   lineEdit_origin->setCursorPosition(0);
}

void HopEditor::onHumuleneChanged()
{
   lineEdit_humulene->setText(obsHop);
}

void HopEditor::onCaryophylleneChanged()
{
   lineEdit_caryophyllene->setText(obsHop);
}

void HopEditor::onCohumuloneChanged()
{
   lineEdit_cohumulone->setText(obsHop);
}

void HopEditor::onMyrceneChanged()
{
   lineEdit_myrcene->setText(obsHop);
}

void HopEditor::onSubstitutesChanged()
{
   textEdit_substitutes->setPlainText(obsHop->substitutes());
}

void HopEditor::onNotesChanged()
{
   textEdit_notes->setPlainText(obsHop->notes());
}
