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

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    m_pgen = new PasswordListGenerator;
    connect(this,SIGNAL(readyToStartGenerating()),m_pgen,SLOT(startPasswordGeneration()));
    connect(m_pgen,SIGNAL(passwordGenerationComplete()),this,SLOT(generationComplete()));

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
    ui->labelGeneratedPasswords->setText("No passwords generated yet.");

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{

    ui->labelGeneratedPasswords->setText("Working please wait...");
    ui->lcdNumber->display(0);
    ui->pushButtonSavePasswords->setEnabled(true);
    if (ui->checkBoxCase->isChecked())
        m_pgen->do_case = true;
    else
        m_pgen->do_case = false;
    if (ui->checkBoxUsernameCombo->isChecked())
            m_pgen->do_username_combo = true;
    else
        m_pgen->do_username_combo = false;
    if (ui->checkBoxPasswordJoin->isChecked())
            m_pgen->do_password_join = true;
    else
        m_pgen->do_password_join = false;
    if (ui->checkBoxLeet->isChecked())
            m_pgen->do_leet = true;
    else
        m_pgen->do_leet = false;
    if (ui->checkBoxLeetAll->isChecked())
            m_pgen->do_leet_all = true;
    else
        m_pgen->do_leet_all = false;
    if (ui->checkBoxSortPasswords->isChecked())
            m_pgen->do_sort = true;
    else
        m_pgen->do_sort = false;
    if (ui->plainTextEditKeywords->toPlainText().count()>0){
        QString keywords_text = ui->plainTextEditKeywords->toPlainText();
        m_pgen->setKeywords(keywords_text.split('\n'));
    }
    m_pgen->setFName(ui->lineEditFirstName->text());
    m_pgen->setLName(ui->lineEditLastName->text());
    m_pgen->setCompany(ui->lineEditCompany->text());
    if (ui->lineEditPrefixSymbols->text().length()>0){
        qDebug() << "Prefix Symbols not null so adding to m_pgen";
        m_pgen->setPrefixes(ui->lineEditPrefixSymbols->text().split(','));
    }
    if (ui->lineEditSuffixSymbols_2->text().length()>0){
        qDebug() << "Suffix Symbols not null so adding to m_pgen";
        m_pgen->setSuffixes(ui->lineEditSuffixSymbols_2->text().split(','));
    }
    if (ui->lineEditPasswordJoinChars->text().length()>0){
        qDebug() << "Suffix Symbols not null so adding to m_pgen";
        m_pgen->setComboList(ui->lineEditPasswordJoinChars->text().split(','));
    }
    if (ui->lineEditPadLength->text().length()>0){
        qDebug() << "Auto Padding  not null so adding to m_pgen";
		m_pgen->do_pad = true;
        m_pgen->setPadLength(ui->lineEditPadLength->text().toInt());
    }


    ui->statusBar->setStatusTip("Generating please wait...");
    ui->labelGeneratedPasswords->setText("Please wait...");
    emit readyToStartGenerating();
}

void MainWindow::startGenerating(){

}

void MainWindow::generationComplete(){
     ui->lcdNumber->display(m_pgen->password_list.count());
     ui->statusBar->setStatusTip("Done please save passwords to file.");
     ui->labelGeneratedPasswords->setText("Passwords generated.");
}

void MainWindow::on_pushButtonSavePasswords_clicked()
{
    QString file_name;
    file_name = QFileDialog::getSaveFileName(this,
         tr("Save Passwords"),"", tr("TXT Files (*.txt)"));
    QFile file(file_name);
       file.open(QIODevice::WriteOnly | QIODevice::Text);
    QTextStream out(&file);
    foreach (QString password, m_pgen->password_list){
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
