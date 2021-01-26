/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.13.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>
#include <mlabel.h>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QPushButton *ReadHSI_button;
    mlabel *showHSI_label;
    QProgressBar *StatProgress;
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_2;
    QSlider *imgThreshold_ScrollBar;
    QLabel *specIndex_label;
    QLabel *label_position;
    QLabel *img_posLbl;
    QSlider *changeROI_ScrollBar;
    QLabel *ROI_label;
    QTextBrowser *selectNum_textBrowser;
    QPushButton *selectSpectral_Button;
    QWidget *layoutWidget1;
    QHBoxLayout *horizontalLayout;
    QLabel *band_label;
    QSlider *changeBand_ScrollBar;
    QPushButton *saveSpecdata_button;
    QPushButton *get100PixDta_Button;
    QPushButton *SaveJPG_Button;
    QCheckBox *checkBox_sick;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1920, 1040);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        ReadHSI_button = new QPushButton(centralWidget);
        ReadHSI_button->setObjectName(QString::fromUtf8("ReadHSI_button"));
        ReadHSI_button->setGeometry(QRect(10, 70, 75, 23));
        showHSI_label = new mlabel(centralWidget);
        showHSI_label->setObjectName(QString::fromUtf8("showHSI_label"));
        showHSI_label->setGeometry(QRect(130, 20, 21, 21));
        showHSI_label->setMouseTracking(true);
        showHSI_label->setFrameShape(QFrame::NoFrame);
        StatProgress = new QProgressBar(centralWidget);
        StatProgress->setObjectName(QString::fromUtf8("StatProgress"));
        StatProgress->setGeometry(QRect(10, 960, 118, 23));
        StatProgress->setValue(24);
        layoutWidget = new QWidget(centralWidget);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(170, 960, 139, 24));
        horizontalLayout_2 = new QHBoxLayout(layoutWidget);
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        label_2 = new QLabel(layoutWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        horizontalLayout_2->addWidget(label_2);

        imgThreshold_ScrollBar = new QSlider(layoutWidget);
        imgThreshold_ScrollBar->setObjectName(QString::fromUtf8("imgThreshold_ScrollBar"));
        imgThreshold_ScrollBar->setOrientation(Qt::Horizontal);

        horizontalLayout_2->addWidget(imgThreshold_ScrollBar);

        specIndex_label = new QLabel(centralWidget);
        specIndex_label->setObjectName(QString::fromUtf8("specIndex_label"));
        specIndex_label->setGeometry(QRect(440, 960, 81, 21));
        specIndex_label->setFrameShape(QFrame::Panel);
        label_position = new QLabel(centralWidget);
        label_position->setObjectName(QString::fromUtf8("label_position"));
        label_position->setGeometry(QRect(1720, 890, 181, 31));
        label_position->setFrameShape(QFrame::Box);
        img_posLbl = new QLabel(centralWidget);
        img_posLbl->setObjectName(QString::fromUtf8("img_posLbl"));
        img_posLbl->setGeometry(QRect(1720, 940, 181, 31));
        img_posLbl->setFrameShape(QFrame::Box);
        changeROI_ScrollBar = new QSlider(centralWidget);
        changeROI_ScrollBar->setObjectName(QString::fromUtf8("changeROI_ScrollBar"));
        changeROI_ScrollBar->setGeometry(QRect(530, 960, 160, 22));
        changeROI_ScrollBar->setOrientation(Qt::Horizontal);
        ROI_label = new QLabel(centralWidget);
        ROI_label->setObjectName(QString::fromUtf8("ROI_label"));
        ROI_label->setGeometry(QRect(700, 960, 47, 21));
        ROI_label->setFrameShape(QFrame::Box);
        selectNum_textBrowser = new QTextBrowser(centralWidget);
        selectNum_textBrowser->setObjectName(QString::fromUtf8("selectNum_textBrowser"));
        selectNum_textBrowser->setGeometry(QRect(1720, 760, 181, 111));
        selectSpectral_Button = new QPushButton(centralWidget);
        selectSpectral_Button->setObjectName(QString::fromUtf8("selectSpectral_Button"));
        selectSpectral_Button->setGeometry(QRect(780, 960, 75, 23));
        layoutWidget1 = new QWidget(centralWidget);
        layoutWidget1->setObjectName(QString::fromUtf8("layoutWidget1"));
        layoutWidget1->setGeometry(QRect(320, 960, 117, 24));
        horizontalLayout = new QHBoxLayout(layoutWidget1);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        band_label = new QLabel(layoutWidget1);
        band_label->setObjectName(QString::fromUtf8("band_label"));
        band_label->setEnabled(true);

        horizontalLayout->addWidget(band_label);

        changeBand_ScrollBar = new QSlider(layoutWidget1);
        changeBand_ScrollBar->setObjectName(QString::fromUtf8("changeBand_ScrollBar"));
        changeBand_ScrollBar->setOrientation(Qt::Horizontal);

        horizontalLayout->addWidget(changeBand_ScrollBar);

        saveSpecdata_button = new QPushButton(centralWidget);
        saveSpecdata_button->setObjectName(QString::fromUtf8("saveSpecdata_button"));
        saveSpecdata_button->setGeometry(QRect(10, 100, 75, 23));
        get100PixDta_Button = new QPushButton(centralWidget);
        get100PixDta_Button->setObjectName(QString::fromUtf8("get100PixDta_Button"));
        get100PixDta_Button->setGeometry(QRect(10, 160, 75, 111));
        SaveJPG_Button = new QPushButton(centralWidget);
        SaveJPG_Button->setObjectName(QString::fromUtf8("SaveJPG_Button"));
        SaveJPG_Button->setGeometry(QRect(10, 130, 75, 23));
        checkBox_sick = new QCheckBox(centralWidget);
        checkBox_sick->setObjectName(QString::fromUtf8("checkBox_sick"));
        checkBox_sick->setGeometry(QRect(10, 300, 73, 31));
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1920, 21));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        ReadHSI_button->setText(QCoreApplication::translate("MainWindow", "Read", nullptr));
        showHSI_label->setText(QString());
        label_2->setText(QCoreApplication::translate("MainWindow", "TextLabel", nullptr));
        specIndex_label->setText(QString());
        label_position->setText(QString());
        img_posLbl->setText(QString());
        ROI_label->setText(QString());
        selectSpectral_Button->setText(QCoreApplication::translate("MainWindow", "Spectral", nullptr));
        band_label->setText(QCoreApplication::translate("MainWindow", "Band", nullptr));
        saveSpecdata_button->setText(QCoreApplication::translate("MainWindow", "Save Spec csv", nullptr));
        get100PixDta_Button->setText(QCoreApplication::translate("MainWindow", "Get 121pixDta", nullptr));
        SaveJPG_Button->setText(QCoreApplication::translate("MainWindow", "Save JPG", nullptr));
        checkBox_sick->setText(QCoreApplication::translate("MainWindow", "sick", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
