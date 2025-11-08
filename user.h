#ifndef USER_H
#define USER_H

class User
{
public:
    virtual void browse()=0;
    virtual void borrowItem()=0;
    virtual void returnItem()=0;
    virtual void placeHold()=0;
    virtual void cancelHold()=0;
};

#endif // USER_H
