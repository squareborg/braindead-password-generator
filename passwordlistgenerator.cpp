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

#include "passwordlistgenerator.h"
#include <QDebug>
#include <QHash>

PasswordListGenerator::PasswordListGenerator()
{
}

QString PasswordListGenerator::getFName(){
    return m_f_name;
}

void PasswordListGenerator::setFName(QString f_name){
    m_f_name = f_name;
}

QString PasswordListGenerator::getLName(){
    return m_l_name;
}

void PasswordListGenerator::setLName(QString l_name){
    m_l_name = l_name;
}

QString PasswordListGenerator::getCompany(){
    return m_company;
}

void PasswordListGenerator::setCompany(QString company){
    m_company = company;
}

QList<QString> PasswordListGenerator::getKeywords(){
    return m_keywords;
}

void PasswordListGenerator::setKeywords(QList<QString> keywords){
    m_keywords = keywords;
}

QList<QString> PasswordListGenerator::getPrefixes(){
    return m_prefixes;
}
void PasswordListGenerator::setPrefixes(QList<QString> prefixes){
    m_prefixes = prefixes;
}
QList<QString> PasswordListGenerator::getSuffixes(){
    return m_suffixes;
}
void PasswordListGenerator::setSuffixes(QList<QString> suffixes){
    m_suffixes = suffixes;
}
QList<QString> PasswordListGenerator::generatePasswords(){
    QList<QString> password_list;
    password_list.append(m_company);
    if(do_username_combo){
        //generate passwords based on possible username
        QList<QString> username_list;
        qDebug() << "Doing username";
        username_list.append(m_f_name);
        username_list.append(m_l_name);
        username_list.append(m_f_name+m_l_name);
        username_list.append(m_f_name+"."+m_l_name);
        username_list.append(m_f_name+"_"+m_l_name);
        username_list.append(m_f_name[0]+m_l_name);
        username_list.append(m_l_name+m_f_name[0]);
        username_list.append(m_f_name+m_l_name[0]);
        username_list.append(m_f_name[0]+"."+m_l_name);
        username_list.append(m_f_name[0]+"_"+m_l_name);
        username_list.append(m_l_name+"."+m_f_name[0]);
        username_list.append(QString(m_f_name[0])+QString(m_l_name[0]));
        username_list.append(QString(m_f_name[0])+"."+QString(m_l_name[0]));
        username_list.append(QString(m_f_name[0])+"_"+QString(m_l_name[0]));
        password_list.append(username_list);
    }

    if(!m_keywords.empty()){
        qDebug() << "Adding keywords";
        password_list.append(m_keywords);
    }





    if(do_leet){
        QHash<QChar,QChar> leet_map;
        QList<QString> leeted_list;
        leet_map['A']='4';
        leet_map['E']='3';
        leet_map['I']='1';
        leet_map['O']='0';
        leet_map['L']='1';
        leet_map['S']='5';
        leet_map['T']='7';

        foreach(QString s, password_list){
            //count the leetable chars
            QString::iterator i;
            int count =0;
            QHash<int,QChar> leetable_index;
            for(i = s.begin(); i != s.end();i++){
                //iterate over the word letter by letter and record index of leetable char
                if (leet_map.contains(i->toUpper())){
                    //qDebug() << "Leetable: " << *i;
                    //This letter is leetable log it in the map
                    leetable_index[count]=i->toUpper();
                }
                count++;
            }
            //okay now to leet the letters

            QString temp_password_all=s;
            for(int i2 = 0; i2!= leetable_index.count(); i2++){
                QString temp_password=s;
                //for each leetable in leetable_index leet the char
                //qDebug() << "Key: " << leetable_index.keys()[i2];
                //qDebug() << "Value: " << leetable_index[leetable_index.keys()[i2]];
                temp_password[leetable_index.keys()[i2]] = leet_map[leetable_index[leetable_index.keys()[i2]]];
                temp_password_all[leetable_index.keys()[i2]] = leet_map[leetable_index[leetable_index.keys()[i2]]];
                //qDebug() << "Temp password: "+temp_password;
                leeted_list.append(temp_password);
                if(do_leet_all)
                    leeted_list.append(temp_password_all);
                //s[]
            }


        }
    password_list.append(leeted_list);
    }




    if (do_password_join){
        qDebug() << "Joining: ";
        QList<QString> joined_list;
        foreach(QString p,password_list){
            //qDebug() << "word: " << p;
            foreach(QString ps,password_list){
                joined_list.append(p+ps);

            }
        }
        password_list.append(joined_list);
    }

    if (!m_prefixes.isEmpty() || !m_suffixes.empty()){
        QList<QString> prefixed_list;
        foreach (QString p,password_list){
            if (!m_prefixes.isEmpty()){
            foreach (QString pre, m_prefixes){
                prefixed_list.append(pre+p);
                if (!m_suffixes.isEmpty()){
                    foreach (QString suf,m_suffixes){
                    prefixed_list.append(QString(pre+p+suf));
                    prefixed_list.append(p+suf);
                    }
                }

                }
            }
            //no prefixes just do the suffixes
            else {
                foreach (QString suf, m_suffixes){
                    prefixed_list.append(p+suf);
                }
            }
        }



    password_list.append(prefixed_list);
    }

    //last
    if (do_case){
        qDebug() << "Doing case";
        QList<QString> cased_list;
        foreach (QString s, password_list){
            if(do_case){
            cased_list.append(s.toUpper());
            cased_list.append(s.toLower());
            cased_list.append(s.toCaseFolded());
            }
        }


    password_list.append(cased_list);
    }


    if(do_sort){
        qDebug() << "Sorting...";
        qSort(password_list.begin(),password_list.end());
    }

    foreach (QString s, password_list){
       //qDebug() << s;
    }
    qDebug() << "Done";
    qDebug() << "Generated: " << password_list.count();
    return password_list;
}
