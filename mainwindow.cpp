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
    if (ui->checkBoxUsernameCombo->isChecked())
            pgen.do_username_combo = true;
    if (ui->checkBoxPasswordJoin->isChecked())
            pgen.do_password_join = true;
    if (ui->checkBoxLeet->isChecked())
            pgen.do_leet = true;
    if (ui->checkBoxLeetAll->isChecked())
            pgen.do_leet_all = true;
    if (ui->checkBoxAdd1->isChecked())
            pgen.do_number = true;
    if (ui->checkBoxAddBang->isChecked())
            pgen.do_symbol = true;
    if (ui->checkBoxSortPasswords->isChecked())
            pgen.do_sort = true;
    QString keywords_text = ui->plainTextEditKeywords->toPlainText();
    pgen.setKeywords(keywords_text.split('\n'));
    pgen.setFName(ui->lineEditFirstName->text());
    pgen.setLName(ui->lineEditLastName->text());
    pgen.setCompany(ui->lineEditCompany->text());
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
