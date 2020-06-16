#ifndef RayCast_h
#define RayCast_h
#include "box2d/b2_world_callbacks.h"
#include "box2d/box2d.h"


class RayCast: public b2RayCastCallback{
public:
    RayCast():m_fixture(NULL){};
    float ReportFixture(b2Fixture* fixture, const b2Vec2& point, const b2Vec2& normal, float fraction){
        m_fixture=fixture;
        m_point=point;
        m_normal=normal;
        m_fraction=fraction;
        return fraction;
    }
    b2Fixture* m_fixture;
    b2Vec2 m_point;
    b2Vec2 m_normal;
    float m_fraction;
};

#endif