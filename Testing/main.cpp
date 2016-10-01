#include <QCoreApplication>

#include <QDebug>

#include <orm.h>
#include <ormdatabase.h>

#include <user.h>

#include <simplecrypt.h>

#include <botanwrapper.h>

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);

    QString password = "abcdefg1234567890°!#$%&/()=?¡¿;,.-}{[]+´";


    BotanWrapper crypt;
    crypt.setPassword(password);
    crypt.setSalt(password);



    BotanWrapper crypt2;
    crypt2.setPassword(password);
    crypt2.setSalt(password);


    ORMDatabase db("QMYSQL");
    db.setUserName("root");
    db.setPassword("qhipa");
    db.open();

    db.dropDatabase("testing");

    db.createDatabase("testing");
    db.setDatabaseName("testing");
    User user;
    user.dropTable();
    if(!db.tables().contains(user.metaObject()->className())){
        user.createTable();
        qDebug()<<"created table";
    }
    //SimpleCrypt crypto(Q_UINT64_C(0x0c2ad4a4acb9f023));

    QString result;
    QString username;
    for(int i =0; i< 100; i++){
        username = "qhipa"+QString::number(i);
        user.setusername(username);
        result = crypt.encrypt(username);//crypto.encryptToString("qhipa"+QString::number(i));
        user.setpassword(result);
        if(user.save())
            qDebug()<<"saved";
    }

    QList< User *> users = user.findAll();
    foreach (User* us, users) {
        qDebug() << us->getusername()<< ":"<<crypt2.decrypt(us->getpassword());//crypto.decryptToString(us->getpassword());
    }

    return 0;
}
