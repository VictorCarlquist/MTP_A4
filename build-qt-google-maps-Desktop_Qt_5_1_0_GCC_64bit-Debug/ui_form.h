/********************************************************************************
** Form generated from reading UI file 'form.ui'
**
** Created by: Qt User Interface Compiler version 5.1.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FORM_H
#define UI_FORM_H

#include <QtCore/QVariant>
#include <QtWebKitWidgets/QWebView>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Form
{
public:
    QGridLayout *gridLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QLineEdit *lePostalAddress;
    QLabel *label_2;
    QSpinBox *zoomSpinBox;
    QPushButton *goButton;
    QWebView *webView;
    QListWidget *lwMarkers;
    QPushButton *pbRemoveMarker;

    void setupUi(QWidget *Form)
    {
        if (Form->objectName().isEmpty())
            Form->setObjectName(QStringLiteral("Form"));
        Form->resize(824, 656);
        gridLayout = new QGridLayout(Form);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        label = new QLabel(Form);
        label->setObjectName(QStringLiteral("label"));

        horizontalLayout->addWidget(label);

        lePostalAddress = new QLineEdit(Form);
        lePostalAddress->setObjectName(QStringLiteral("lePostalAddress"));

        horizontalLayout->addWidget(lePostalAddress);

        label_2 = new QLabel(Form);
        label_2->setObjectName(QStringLiteral("label_2"));

        horizontalLayout->addWidget(label_2);

        zoomSpinBox = new QSpinBox(Form);
        zoomSpinBox->setObjectName(QStringLiteral("zoomSpinBox"));
        zoomSpinBox->setMinimum(5);
        zoomSpinBox->setMaximum(30);
        zoomSpinBox->setSingleStep(1);
        zoomSpinBox->setValue(15);

        horizontalLayout->addWidget(zoomSpinBox);

        goButton = new QPushButton(Form);
        goButton->setObjectName(QStringLiteral("goButton"));

        horizontalLayout->addWidget(goButton);


        gridLayout->addLayout(horizontalLayout, 0, 0, 1, 1);

        webView = new QWebView(Form);
        webView->setObjectName(QStringLiteral("webView"));
        webView->setUrl(QUrl(QStringLiteral("about:blank")));

        gridLayout->addWidget(webView, 1, 0, 1, 1);

        lwMarkers = new QListWidget(Form);
        lwMarkers->setObjectName(QStringLiteral("lwMarkers"));

        gridLayout->addWidget(lwMarkers, 1, 1, 1, 1);

        pbRemoveMarker = new QPushButton(Form);
        pbRemoveMarker->setObjectName(QStringLiteral("pbRemoveMarker"));

        gridLayout->addWidget(pbRemoveMarker, 0, 1, 1, 1);


        retranslateUi(Form);

        QMetaObject::connectSlotsByName(Form);
    } // setupUi

    void retranslateUi(QWidget *Form)
    {
        Form->setWindowTitle(QApplication::translate("Form", "Form", 0));
        label->setText(QApplication::translate("Form", "Postal Address", 0));
        label_2->setText(QApplication::translate("Form", "Zoom", 0));
        goButton->setText(QApplication::translate("Form", "Go", 0));
        pbRemoveMarker->setText(QApplication::translate("Form", "Remove marker", 0));
    } // retranslateUi

};

namespace Ui {
    class Form: public Ui_Form {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FORM_H
