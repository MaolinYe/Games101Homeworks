 #include <iostream>
#include <vector>

#include "CGL/vector2D.h"

#include "mass.h"
#include "rope.h"
#include "spring.h"

namespace CGL {

    Rope::Rope(Vector2D start, Vector2D end, int num_nodes, float node_mass, float k, vector<int> pinned_nodes)
    {
        // TODO (Part 1): Create a rope starting at `start`, ending at `end`, and containing `num_nodes` nodes.

//        Comment-in this part when you implement the constructor
        for(int i=0;i<num_nodes;i++){
            auto position=start+(end-start)*i/(num_nodes-1.0);
            masses.push_back(new Mass(position,node_mass,false));
        }
        for(int i=0;i<num_nodes-1;i++){
            springs.push_back(new Spring(masses[i],masses[i+1],k));
        }
        for (auto &i : pinned_nodes) {
            masses[i]->pinned = true;
        }
    }

    void Rope::simulateEuler(float delta_t, Vector2D gravity)
    {
        for (auto &s : springs)
        {
            // TODO (Part 2): Use Hooke's law to calculate the force on a node
            auto length=(s->m1->position-s->m2->position).norm();
            auto force=s->k*(s->m1->position-s->m2->position)/length*(length-s->rest_length);
            s->m1->forces-=force;
            s->m2->forces+=force;
        }

        for (auto &m : masses)
        {
            if (!m->pinned)
            {
                // TODO (Part 2): Add the force due to gravity, then compute the new velocity and position
                auto a=(m->forces-0.005*m->velocity)/m->mass+gravity;
                m->velocity+=a*delta_t;
                m->position+=m->velocity*delta_t;
                // TODO (Part 2): Add global damping
            }

            // Reset all forces on each mass
            m->forces = Vector2D(0, 0);
        }
    }

    void Rope::simulateVerlet(float delta_t, Vector2D gravity)
    {
        for (auto &s : springs)
        {
            // TODO (Part 3): Simulate one timestep of the rope using explicit Verlet （solving constraints)
            auto ab=s->m2->position-s->m1->position;
            auto direction=ab.unit();
            auto length=ab.norm();
            int a=1,b=1;
            if(s->m1->pinned)
                a=0;
            if(s->m2->pinned)
                b=0;
            if(!a&&!b)
                continue;
            s->m1->position+=direction*(length-s->rest_length)*a/(a+b);
            s->m2->position-=direction*(length-s->rest_length)*b/(a+b);
        }

        for (auto &m : masses)
        {
            if (!m->pinned)
            {
                Vector2D temp_position = m->position;
                // TODO (Part 3.1): Set the new position of the rope mass
                m->position=m->position+0.99995*(m->position-m->last_position)+gravity*delta_t*delta_t;
                m->last_position=temp_position;
                // TODO (Part 4): Add global Verlet damping
            }
        }
    }
}
