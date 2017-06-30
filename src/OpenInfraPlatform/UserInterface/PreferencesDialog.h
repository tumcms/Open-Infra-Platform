/*
    Copyright (c) 2017 Technical University of Munich
    Chair of Computational Modeling and Simulation.

    TUM Open Infra Platform is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License Version 3
    as published by the Free Software Foundation.

    TUM Open Infra Platform is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program. If not, see <http://www.gnu.org/licenses/>.
*/

#pragma once
#ifndef OpenInfraPlatform_UserInterface_PreferencesDialog_38da791c_994f_450a_abc1_6676bdf555c4_h
#define OpenInfraPlatform_UserInterface_PreferencesDialog_38da791c_994f_450a_abc1_6676bdf555c4_h

#include "ui_PreferencesDialog.h"
#include "ColorPicker/colorpickerwidget.h"
#include "OpenInfraPlatform/UserInterface/ViewPanel/View.h"
//#include <BlueFramework/Engine/Camera/InfraCameraController.h>
#include <QDialog>
#include <QColorDialog>
#include <boost/noncopyable.hpp>
#include <iostream>

namespace OpenInfraPlatform
{
	namespace UserInterface
	{
		class PreferencesDialog : public QDialog
		{
			Q_OBJECT;

		public:
			//! Default constructor.
			PreferencesDialog(OpenInfraPlatform::UserInterface::View* view, QWidget *parent = nullptr);

			//! Virtual destructor.
			virtual ~PreferencesDialog();
			
		protected:
			virtual void changeEvent(QEvent* evt) override;

		private Q_SLOTS:
			void clearColorChanged(const QColor &col);

			void on_checkBoxGradientClear_clicked (bool checked);
			void on_checkBoxShowGrid_clicked (bool checked);
			void on_checkBoxShowReferenceCoordinateSystem_clicked(bool checked);
			void on_checkBoxSkybox_clicked (bool checked);
			
			void on_doubleSpinBoxAlignmentLineWidth_valueChanged(double i);

			void on_checkBoxShowFrameTimes_clicked(bool checked);

			void on_doubleSpinBoxAnimationTime_valueChanged(double value);
			void on_doubleSpinBoxNearPlane_valueChanged(double value);
			void on_doubleSpinBoxFarPlane_valueChanged(double value);
			void on_doubleSpinBoxPanSpeed_valueChanged(double value); // this SpinBox changes pan speed in spectator mode

			void onComboBoxRenderSystem_currentIndexChanged(int index);
			void onCheckBoxMSAA_clicked(bool);

			void onComboBoxLanguage_currentIndexChanged(const QString & text);

            //---------------------------------------------------------------------------//
            // ViewCube
            //---------------------------------------------------------------------------//

            void on_doubleSpinBoxBoundHeight_valueChanged(double value);
            void on_doubleSpinBoxOuterBoundWidth_valueChanged(double value);
            void on_doubleSpinBoxInnerBoundWidth_valueChanged(double value);
            void on_doubleSpinBoxSize_valueChanged(double value);

            void on_pushButton_Export_clicked();
            void on_pushButton_Import_clicked(QString filename = nullptr);

            void on_pushButtonFaceColor_clicked();
            void on_pushButtonBorderColor_clicked();
            void on_pushButtonHighlightColor_clicked();
            void on_pushButtonTextColor_clicked();

            void on_radioButtonLegacy_toggled(bool value);
            void on_radioButtonTextured_toggled(bool value);
            void on_radioButtonStandard_toggled(bool value);

            void on_checkBoxShowViewCube_clicked(bool checked);
            void on_checkBoxShowCompass_clicked(bool checked);
            void on_checkBoxShowRotationArrows_clicked(bool checked);

		private:
			void updateRenderSystem();
            //void faceColorChanged(const QColor &col);
            //void highlightColorChanged(const QColor &col);
            //void boundColorChanged(const QColor &col);
            //void textColorChanged(const QColor &col);
			void createLanguageMenu();

            bool useTextured = false;
			
		private:
			Ui::PreferencesDialog*	ui_;
			ColorPickerWidget*		colorPickerWidget_;
            QColorDialog            faceColorDialog_, borderColorDialog_, textColorDialog_, highlightColorDialog_;

			QTranslator*			translator_;
			OpenInfraPlatform::UserInterface::View* view_;
			//buw::ReferenceCounted<buw::InfraCameraController>	infraCameraController_;

		}; // end class PreferencesDialog
	} // end namespace UserInterface
} // end namespace OpenInfraPlatform

namespace buw
{
	using OpenInfraPlatform::UserInterface::PreferencesDialog;
}

#endif // end define OpenInfraPlatform_UserInterface_PreferencesDialog_38da791c_994f_450a_abc1_6676bdf555c4_h
