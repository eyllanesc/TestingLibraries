#ifndef USER_H
#define USER_H

#include <ormobject.h>

class User: public ORMObject<User>
{
    Q_OBJECT
    ORM_PROPERTY(QString, username)
    ORM_PROPERTY(QString, password)
public:
    User(){}
};

#endif // USER_H
