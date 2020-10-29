#pragma once
#include <box2d/box2d.h>

class ContactListener : public b2ContactListener
{
    private:
        
    public:
        ContactListener();
        ~ContactListener();
        
        void BeginContact(b2Contact*);
        void EndContact(b2Contact*);
};