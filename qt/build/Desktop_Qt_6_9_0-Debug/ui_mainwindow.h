/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QPushButton *createGraphButton;
    QGroupBox *gbLandmarksBasic;
    QComboBox *cmbBasicMethod;
    QLineEdit *txtBasicK;
    QLineEdit *txtBasicM;
    QPushButton *btnCreateBasic;
    QGroupBox *gbLandmarksBFS;
    QComboBox *cmbBFSMethod;
    QLineEdit *txtBFSK;
    QLineEdit *txtBFSM;
    QPushButton *btnCreateBFS;
    QGroupBox *gbCalculations;
    QGridLayout *gridLayout;
    QLineEdit *txtS;
    QLineEdit *txtT;
    QCheckBox *chkInternalRepr;
    QPushButton *btnExact;
    QTextEdit *txtResults;
    QPushButton *btnApproxBFS;
    QPushButton *btnApproxBasic;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(800, 600);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        createGraphButton = new QPushButton(centralwidget);
        createGraphButton->setObjectName("createGraphButton");
        createGraphButton->setGeometry(QRect(320, 40, 131, 26));
        gbLandmarksBasic = new QGroupBox(centralwidget);
        gbLandmarksBasic->setObjectName("gbLandmarksBasic");
        gbLandmarksBasic->setGeometry(QRect(60, 110, 248, 156));
        cmbBasicMethod = new QComboBox(gbLandmarksBasic);
        cmbBasicMethod->addItem(QString());
        cmbBasicMethod->addItem(QString());
        cmbBasicMethod->addItem(QString());
        cmbBasicMethod->setObjectName("cmbBasicMethod");
        cmbBasicMethod->setGeometry(QRect(10, 30, 141, 26));
        cmbBasicMethod->setEditable(false);
        txtBasicK = new QLineEdit(gbLandmarksBasic);
        txtBasicK->setObjectName("txtBasicK");
        txtBasicK->setGeometry(QRect(10, 60, 113, 26));
        txtBasicM = new QLineEdit(gbLandmarksBasic);
        txtBasicM->setObjectName("txtBasicM");
        txtBasicM->setGeometry(QRect(10, 100, 113, 26));
        btnCreateBasic = new QPushButton(gbLandmarksBasic);
        btnCreateBasic->setObjectName("btnCreateBasic");
        btnCreateBasic->setGeometry(QRect(150, 100, 88, 26));
        gbLandmarksBFS = new QGroupBox(centralwidget);
        gbLandmarksBFS->setObjectName("gbLandmarksBFS");
        gbLandmarksBFS->setGeometry(QRect(470, 100, 238, 156));
        cmbBFSMethod = new QComboBox(gbLandmarksBFS);
        cmbBFSMethod->addItem(QString());
        cmbBFSMethod->addItem(QString());
        cmbBFSMethod->addItem(QString());
        cmbBFSMethod->setObjectName("cmbBFSMethod");
        cmbBFSMethod->setGeometry(QRect(10, 30, 141, 26));
        cmbBFSMethod->setEditable(false);
        txtBFSK = new QLineEdit(gbLandmarksBFS);
        txtBFSK->setObjectName("txtBFSK");
        txtBFSK->setGeometry(QRect(10, 60, 113, 26));
        txtBFSM = new QLineEdit(gbLandmarksBFS);
        txtBFSM->setObjectName("txtBFSM");
        txtBFSM->setGeometry(QRect(10, 100, 113, 26));
        btnCreateBFS = new QPushButton(gbLandmarksBFS);
        btnCreateBFS->setObjectName("btnCreateBFS");
        btnCreateBFS->setGeometry(QRect(140, 100, 88, 26));
        gbCalculations = new QGroupBox(centralwidget);
        gbCalculations->setObjectName("gbCalculations");
        gbCalculations->setGeometry(QRect(70, 310, 391, 231));
        gridLayout = new QGridLayout(gbCalculations);
        gridLayout->setObjectName("gridLayout");
        txtS = new QLineEdit(gbCalculations);
        txtS->setObjectName("txtS");

        gridLayout->addWidget(txtS, 0, 0, 1, 1);

        txtT = new QLineEdit(gbCalculations);
        txtT->setObjectName("txtT");

        gridLayout->addWidget(txtT, 1, 0, 1, 1);

        chkInternalRepr = new QCheckBox(gbCalculations);
        chkInternalRepr->setObjectName("chkInternalRepr");

        gridLayout->addWidget(chkInternalRepr, 2, 0, 1, 2);

        btnExact = new QPushButton(gbCalculations);
        btnExact->setObjectName("btnExact");

        gridLayout->addWidget(btnExact, 3, 0, 1, 1);

        txtResults = new QTextEdit(gbCalculations);
        txtResults->setObjectName("txtResults");
        txtResults->setReadOnly(true);

        gridLayout->addWidget(txtResults, 3, 1, 3, 1);

        btnApproxBFS = new QPushButton(gbCalculations);
        btnApproxBFS->setObjectName("btnApproxBFS");

        gridLayout->addWidget(btnApproxBFS, 4, 0, 1, 1);

        btnApproxBasic = new QPushButton(gbCalculations);
        btnApproxBasic->setObjectName("btnApproxBasic");

        gridLayout->addWidget(btnApproxBasic, 5, 0, 1, 1);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 800, 23));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        createGraphButton->setText(QCoreApplication::translate("MainWindow", "\320\241\320\276\320\267\320\264\320\260\321\202\321\214 \320\263\321\200\320\260\321\204", nullptr));
        gbLandmarksBasic->setTitle(QCoreApplication::translate("MainWindow", "Landmarks Basic", nullptr));
        cmbBasicMethod->setItemText(0, QCoreApplication::translate("MainWindow", "highest-degree", nullptr));
        cmbBasicMethod->setItemText(1, QCoreApplication::translate("MainWindow", "best-coverage", nullptr));
        cmbBasicMethod->setItemText(2, QCoreApplication::translate("MainWindow", "random", nullptr));

        btnCreateBasic->setText(QCoreApplication::translate("MainWindow", "\320\241\320\276\320\267\320\264\320\260\321\202\321\214", nullptr));
        gbLandmarksBFS->setTitle(QCoreApplication::translate("MainWindow", "Landmarks BFS", nullptr));
        cmbBFSMethod->setItemText(0, QCoreApplication::translate("MainWindow", "highest-degree", nullptr));
        cmbBFSMethod->setItemText(1, QCoreApplication::translate("MainWindow", "best-coverage", nullptr));
        cmbBFSMethod->setItemText(2, QCoreApplication::translate("MainWindow", "random", nullptr));

        btnCreateBFS->setText(QCoreApplication::translate("MainWindow", "\320\241\320\276\320\267\320\264\320\260\321\202\321\214", nullptr));
        gbCalculations->setTitle(QCoreApplication::translate("MainWindow", "\320\222\321\213\321\207\320\270\321\201\320\273\320\265\320\275\320\270\321\217", nullptr));
        txtS->setText(QString());
        txtT->setText(QString());
        chkInternalRepr->setText(QCoreApplication::translate("MainWindow", "\320\230\321\201\320\277-\321\202\321\214 \320\262\320\275\321\203\321\202-\320\275\320\265\320\265 \320\277\321\200\320\265\320\264-\320\275\320\270\320\265", nullptr));
        btnExact->setText(QCoreApplication::translate("MainWindow", "\320\242\320\276\321\207\320\275\321\213\320\271 \320\260\320\273\320\263\320\276\321\200\320\270\321\202\320\274", nullptr));
        btnApproxBFS->setText(QCoreApplication::translate("MainWindow", "Landmarks BFS", nullptr));
        btnApproxBasic->setText(QCoreApplication::translate("MainWindow", "Landmarks Basic", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
