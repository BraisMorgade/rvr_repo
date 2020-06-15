#ifndef GameContactListener_h
#define GameContactListener_h

#include "box2d/box2d.h"
#include "box2d/b2_collision.h"
#include "box2d/b2_contact_manager.h"
#include "PhysicsObject.h"

class GameContactListener: public b2ContactListener{
public:
    void BeginContact(b2Contact* contact){
        void* dataA=contact->GetFixtureA()->GetBody()->GetUserData();
        void* dataB=contact->GetFixtureB()->GetBody()->GetUserData();
        
        PhysicsObject* objectA=nullptr;
        PhysicsObject* objectB=nullptr;

        if(dataA) 
            objectA=static_cast<PhysicsObject*>(dataA);
        if(dataB)
            objectB=static_cast<PhysicsObject*>(dataB);
        
        objectA->OnCollisionEnter(objectB);
        objectB->OnCollisionEnter(objectA);

    };
    void EndContact(b2Contact* contact){
        void* dataA=contact->GetFixtureA()->GetBody()->GetUserData();
        void* dataB=contact->GetFixtureB()->GetBody()->GetUserData();
            
        PhysicsObject* objectA=nullptr;
        PhysicsObject* objectB=nullptr;

        if(dataA) 
            objectA=static_cast<PhysicsObject*>(dataA);
        if(dataB)
            objectB=static_cast<PhysicsObject*>(dataB);
            
        objectA->OnCollisionExit(objectB);
        objectB->OnCollisionExit(objectA);

    };

};

#endif
