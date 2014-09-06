#ifndef PASSWORDLISTGENERATOR_H
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

#define PASSWORDLISTGENERATOR_H
#include <QList>
#include <QString>
class PasswordListGenerator
{
public:
    PasswordListGenerator();
    bool do_case;
    bool do_username_combo;
    bool do_password_join;
    bool do_leet;
    bool do_leet_all;
    bool do_number;
    bool do_symbol;
    bool do_sort;
    QString getFName();
    void setFName(QString f_name);
    QString getLName();
    void setLName(QString l_name);
    QString getCompany();
    void setCompany(QString company);
    QList<QString> getKeywords();
    void setKeywords(QList<QString> keywords);
    QList<QString> generatePasswords();

private:
    QString m_f_name;
    QString m_l_name;
    QString m_company;
    QList<QString> m_keywords;

};

#endif // PASSWORDLISTGENERATOR_H
