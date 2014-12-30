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
#include <QFuture>
#include <QtConcurrent>

QString ucFirst(const QString str) {
    if (str.size() < 1) {
        return "";
    }

    QStringList tokens = str.split(" ");
    QList<QString>::iterator tokItr = tokens.begin();

    for (tokItr = tokens.begin(); tokItr != tokens.end(); ++tokItr) {
        (*tokItr) = (*tokItr).at(0).toUpper() + (*tokItr).mid(1);
    }

    return tokens.join(" ");
}



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

void PasswordListGenerator::setComboList(QList<QString> combo_list){
    m_combo_list = combo_list;
}


QList<QString> PasswordListGenerator::getComboList(){
    return m_combo_list;
}

int PasswordListGenerator::getPadLength(){
    return m_pad_length;
}

void PasswordListGenerator::setPadLength(int length){
    m_pad_length = length;
}
void PasswordListGenerator::startPasswordGeneration(){
     QFuture<void> future = QtConcurrent::run(this,&PasswordListGenerator::generatePasswords);

}

void PasswordListGenerator::generatePasswords(){
    qDebug() << "here it is";
    qDebug() << ucFirst("ste");
    qDebug() << "Did it work";

    if (!m_f_name.isEmpty())
        password_list.append(m_f_name);
    if (!m_l_name.isEmpty())
        password_list.append(m_l_name);
    if (!m_company.isEmpty())
        password_list.append(m_company);
    if(!m_keywords.empty()){
        qDebug() << "Adding keywords";
        password_list.append(m_keywords);
    }
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
                if(do_leet_all && temp_password_all!=temp_password)
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
                foreach(QString join_char,m_combo_list){
                    joined_list.append(p+join_char+ps);
                }
                joined_list.append(p+ps);
            }
        }

        password_list.append(joined_list);
    }

    if (!m_prefixes.isEmpty() || !m_suffixes.empty()){
        qDebug() << "Doing prefix/suffix";
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
	// do pad
	if (do_pad){
		qDebug() << "Doing pad";
        QList<QString> padded_list;
        foreach (QString s, password_list){
			if (s.length() < getPadLength()){
				QString str_in_progress = "";
				str_in_progress.append(s);
				int dif = getPadLength() - s.length();
				for (int i=1;i<=dif+1;i++){
					qDebug() << "I: " << i;
					str_in_progress.append(QString::number(i));
				}
				padded_list.append(str_in_progress);
				qDebug() << "pad " << str_in_progress;	
			}
		}

	password_list.append(padded_list);
	}
    //last
    if (do_case){
        qDebug() << "Doing case";
        QList<QString> cased_list;
        foreach (QString s, password_list){
//            qDebug() << "case password:" << s;
            if(do_case){
                if (s!=s.toUpper())
                    cased_list.append(s.toUpper());
                if (s!=s.toLower())
                    cased_list.append(s.toLower());
//                qDebug() << "S: " << s;
//                qDebug() << "S UC: " << ucFirst(s);
                //Input maybe all upper case
                QString lowerCaseS =s.toLower();
                QString ucFirstS = ucFirst(lowerCaseS);
                if (s!=ucFirstS){
                    cased_list.append(ucFirstS);
//                    qDebug() << "appending company";
                }
            }
        }


    password_list.append(cased_list);
    }

    //remove dupes
    QSet<QString> set;
    foreach (QString s, password_list){
       //qDebug() << "Set add: " << s;
       set.insert(s);
    }
    password_list = set.toList();
    if(do_sort){
        qDebug() << "Sorting...";
        qSort(password_list.begin(),password_list.end());
    }

    qDebug() << "Done";
    qDebug() << "Generated: " << password_list.count();
    emit passwordGenerationComplete();


}


