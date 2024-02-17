//
// Created by Göksu Güvendiren on 2019-05-14.
//

#include "Scene.hpp"


void Scene::buildBVH() {
    printf(" - Generating BVH...\n\n");
    this->bvh = new BVHAccel(objects, 1, BVHAccel::SplitMethod::NAIVE);
}

Intersection Scene::intersect(const Ray &ray) const
{
    return this->bvh->Intersect(ray);
}

void Scene::sampleLight(Intersection &pos, float &pdf) const
{
    float emit_area_sum = 0;
    for (uint32_t k = 0; k < objects.size(); ++k) {
        if (objects[k]->hasEmit()){
            emit_area_sum += objects[k]->getArea();
        }
    }
    float p = get_random_float() * emit_area_sum;
    emit_area_sum = 0;
    for (uint32_t k = 0; k < objects.size(); ++k) {
        if (objects[k]->hasEmit()){
            emit_area_sum += objects[k]->getArea();
            if (p <= emit_area_sum){
                objects[k]->Sample(pos, pdf);
                break;
            }
        }
    }
}

bool Scene::trace(
        const Ray &ray,
        const std::vector<Object*> &objects,
        float &tNear, uint32_t &index, Object **hitObject)
{
    *hitObject = nullptr;
    for (uint32_t k = 0; k < objects.size(); ++k) {
        float tNearK = kInfinity;
        uint32_t indexK;
        Vector2f uvK;
        if (objects[k]->intersect(ray, tNearK, indexK) && tNearK < tNear) {
            *hitObject = objects[k];
            tNear = tNearK;
            index = indexK;
        }
    }


    return (*hitObject != nullptr);
}

// Implementation of Path Tracing
Vector3f Scene::castRay(const Ray &ray, int depth) const
{
    // TO DO Implement Path Tracing Algorithm here
    Intersection shadingPoint=Scene::intersect(ray);
    if(!shadingPoint.happened)
        return {0,0,0};
    if(shadingPoint.m->hasEmission())
        return shadingPoint.m->getEmission();
    Intersection lightPoint;
    float pdf;
    sampleLight(lightPoint,pdf);
    auto lightDirection=(shadingPoint.coords-lightPoint.coords).normalized();
    float lightDistance=intersect(Ray(lightPoint.coords,lightDirection)).distance;
    float objDistance=(lightPoint.coords-shadingPoint.coords).norm();
    Vector3f direct={0,0,0};
    if(fabsf(lightDistance-objDistance)<0.001){ // 无物体遮挡光源
        auto L_i=lightPoint.emit;
        auto f_r=shadingPoint.m->eval(ray.direction,-lightDirection,shadingPoint.normal);
        float cos= dotProduct(shadingPoint.normal,-lightDirection);
        float cosPrime= dotProduct(lightPoint.normal,lightDirection);
        direct=L_i*f_r*cos*cosPrime/(objDistance*objDistance)/pdf;
    }
    if(static_cast<float >(rand())/RAND_MAX>RussianRoulette)
        return direct;
    Vector3f indirect={0,0,0};
    auto boundDirection=shadingPoint.m->sample(ray.direction,shadingPoint.normal).normalized();
    auto boundRay=Ray(shadingPoint.coords,boundDirection);
    auto boundPoint= intersect(boundRay);
    if(boundPoint.happened&&!boundPoint.m->hasEmission()){
        auto f_r=shadingPoint.m->eval(ray.direction,boundDirection,shadingPoint.normal);
        float cos= dotProduct(shadingPoint.normal,boundDirection);
        float pdf_hemi=shadingPoint.m->pdf(ray.direction,boundDirection,shadingPoint.normal);
        indirect= castRay(boundRay,depth+1)*f_r*cos/pdf_hemi/RussianRoulette;
    }
    return direct+indirect;
}