//The MIT License (MIT)

//Copyright (c) 2014 Stephen Martin <ste@superste.me>

//Permission is hereby granted, free of charge, to any person obtaining a copy
//of this software and associated documentation files (the "Software"), to deal
//in the Software without restriction, including without limitation the rights
//to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
//copies of the Software, and to permit persons to whom the Software is
//furnished to do so, subject to the following conditions:

//The above copyright notice and this permission notice shall be included in
//all copies or substantial portions of the Software.

//THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
//IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
//AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
//LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
//OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
//THE SOFTWARE.

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QFileDialog>
#include <QFile>
#include "passwordlistgenerator.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->checkBoxUsernameCombo->setChecked(true);
    ui->checkBoxLeet->setChecked(true);
    ui->checkBoxCase->setChecked(true);
    ui->checkBoxPasswordJoin->setChecked(true);
    QPalette lcdpalette;
    lcdpalette.setColor(QPalette::Background, QColor(0, 0, 0));
    lcdpalette.setColor(QPalette::Base, QColor(0, 0, 0));
    lcdpalette.setColor(QPalette::AlternateBase, QColor(0, 0, 0));
    ui->lcdNumber->setPalette(lcdpalette);
    ui->lcdNumber->setAutoFillBackground(true);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    qDebug() << "Clicked!";
    ui->pushButtonSavePasswords->setEnabled(true);
    PasswordListGenerator pgen;
    if (ui->checkBoxCase->isChecked())
        pgen.do_case = true;
    else
        pgen.do_case = false;
    if (ui->checkBoxUsernameCombo->isChecked())
            pgen.do_username_combo = true;
    else
        pgen.do_username_combo = false;
    if (ui->checkBoxPasswordJoin->isChecked())
            pgen.do_password_join = true;
    else
        pgen.do_password_join = false;
    if (ui->checkBoxLeet->isChecked())
            pgen.do_leet = true;
    else
        pgen.do_leet = false;
    if (ui->checkBoxLeetAll->isChecked())
            pgen.do_leet_all = true;
    else
        pgen.do_leet_all = false;
    if (ui->checkBoxSortPasswords->isChecked())
            pgen.do_sort = true;
    else
        pgen.do_sort = false;
    if (ui->plainTextEditKeywords->toPlainText().count()>0){
        QString keywords_text = ui->plainTextEditKeywords->toPlainText();
        pgen.setKeywords(keywords_text.split('\n'));
    }
    pgen.setFName(ui->lineEditFirstName->text());
    pgen.setLName(ui->lineEditLastName->text());
    pgen.setCompany(ui->lineEditCompany->text());
    if (ui->lineEditPrefixSymbols->text().length()>0){
        qDebug() << "Prefix Symbols not null so adding to pgen";
        pgen.setPrefixes(ui->lineEditPrefixSymbols->text().split(','));
    }
    if (ui->lineEditSuffixSymbols_2->text().length()>0){
        qDebug() << "Suffix Symbols not null so adding to pgen";
        pgen.setSuffixes(ui->lineEditSuffixSymbols_2->text().split(','));
    }
    if (ui->lineEditPasswordJoinChars->text().length()>0){
        qDebug() << "Suffix Symbols not null so adding to pgen";
        pgen.setComboList(ui->lineEditPasswordJoinChars->text().split(','));
    }

    m_passwords = pgen.generatePasswords();
    ui->lcdNumber->display(m_passwords.count());

}

void MainWindow::on_pushButtonSavePasswords_clicked()
{
    QString file_name;
    file_name = QFileDialog::getSaveFileName(this,
         tr("Save Passwords"),"", tr("TXT Files (*.txt)"));
    QFile file(file_name);
       file.open(QIODevice::WriteOnly | QIODevice::Text);
    QTextStream out(&file);
    foreach (QString password, m_passwords){
    out << password+"\n";
    }
    file.close();
}



void MainWindow::on_checkBoxPasswordJoin_stateChanged(int arg1)
{
    if (ui->checkBoxPasswordJoin->isChecked())
        ui->lineEditPasswordJoinChars->setEnabled(true);
    else
        ui->lineEditPasswordJoinChars->setEnabled(false);
}



void MainWindow::on_pushButtonUncheckAll_clicked()
{
    ui->checkBoxCase->setChecked(false);
    ui->checkBoxLeet->setChecked(false);
    ui->checkBoxLeetAll->setChecked(false);
    ui->checkBoxPasswordJoin->setChecked(false);
    ui->checkBoxSortPasswords->setChecked(false);
    ui->checkBoxUsernameCombo->setChecked(false);
}

void MainWindow::on_pushButtonCheckAll_clicked()
{
    ui->checkBoxCase->setChecked(true);
    ui->checkBoxLeet->setChecked(true);
    ui->checkBoxLeetAll->setChecked(true);
    ui->checkBoxPasswordJoin->setChecked(true);
    ui->checkBoxSortPasswords->setChecked(true);
    ui->checkBoxUsernameCombo->setChecked(true);
}
