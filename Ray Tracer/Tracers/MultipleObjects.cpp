#include "MultipleObjects.h"
#include "World.h"

// -------------------------------------------------------------------- default constructor

MultipleObjects::MultipleObjects(void)
	: Tracer()
{}


// -------------------------------------------------------------------- constructor
		
MultipleObjects::MultipleObjects(World* _worldPtr)
	: Tracer(_worldPtr)
{}


// -------------------------------------------------------------------- destructor

MultipleObjects::~MultipleObjects(void) {}


// -------------------------------------------------------------------- trace_ray

MyRGBColor	
MultipleObjects::trace_ray(const Ray& ray) const {
	ShadeRec sr(world_ptr->hit_bare_bones_objects(ray)); // sr is copy constructed
		
	if (sr.hit_an_object)   
		return (sr.color);   
	else
		return (world_ptr->background_color);
}

// --------------------------------------- DEPTH NOT USED YET 

MyRGBColor	
MultipleObjects::trace_ray(const Ray ray, const int depth) const {
	ShadeRec sr(world_ptr->hit_bare_bones_objects(ray)); // sr is copy constructed
	
	if (sr.hit_an_object)   
		return (sr.color);   
	else
		return (world_ptr->background_color);
}

