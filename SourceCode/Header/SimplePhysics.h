#pragma once
#include <Eigen/Dense>
#include <vector>
#include "CommonClass.h"
#include "LibParallexScroll.h"

class SimplePhysics
{
enum CollisionStatus
{
	NONE = 0, UP = 1, DOWN = 2, LEFT = 3, RIGHT = 4
};

enum ObjType
{
	MAP_TILE = 0, ENTITY = 1
};

struct Box {
	Eigen::Vector2f position;
	float width;
	float height;
};


struct Object {
	Eigen::Vector2f velocity;
	Eigen::Vector2f vel_tmp;
	Eigen::Vector2f vel_1;
	Eigen::Vector2f force;
	Eigen::Vector2f force_1;
	Eigen::Vector2f force_tmp;
	Eigen::Vector2f tmp_col_vel_intergral;
	int col_update_span;
	Box* hit_box;
	float mass;
	int type;
	std::function<void(float, float)> velocity_handeler;
	CSprite* sprite;
	bool is_against_left;
	bool is_against_right;
	bool is_against_up;
	bool is_against_down;
};

struct Transform { // Describes an objects location
	Eigen::Vector2f Position;
	Eigen::Vector2f Scale;
	Eigen::Quaterniond Rotation;
};

public:
	SimplePhysics();
	~SimplePhysics();

	float get_entity_velocity_x(size_t idx);
	float get_entity_velocity_y(size_t idx);
	void add_map_tile(std::string name);
	void add_map_tile(std::vector<std::string> names);
	void add_entity(std::string name);
	void add_entity(std::string name, std::function<void(float, float)> vel_fun);
	// a constant force offset, before force summing
	void set_force_1(std::string name, float x, float y);
	// temporaty force, reset to 0 after one step 
	void set_force_temp(std::string name, float x, float y);
	// a constant velocity offset, after summing, before cliping and limiting
	void set_vel_offset(std::string name, float x, float y);
	// temporary velocity, reset to 0 after one step
	void set_vel_temp(std::string name, float x, float y);
	// change the velocity of object
	void set_vel_override(std::string name, float x, float y);
	void set_parallex_instance(LibParallexScroll* ps);

	bool get_is_on_ground();
	
	void init();
	void on_colid_callback(Object* src, Object* tar);
	void on_colid_callback(std::string src_name, std::string tar_name);
	void main_loop(float dt);

private:
	std::vector<Object*> objects_;
	//Eigen::Vector2f gravity_ = Eigen::Vector2f(0.0, 0.0);
	Eigen::Vector2f gravity_ = Eigen::Vector2f(0.0, 298.0);
	float dt_;
	float damping_factor_ = 0.9999f;
	float fric_factor_ = 0.0f;
	float drag_factor_ = 0.05f;
	float collision_cancel_epsilon_ = 0.001;

	void test_collision_(Object* a , Object* b);
	void handel_collisions_();
	void process_collisions_();
	void update_col_intergral(Object* obj);
	void remove_aix_component_(Object* obj, int direction);
	void reset_col_(Object* obj);
	bool is_col_(Box* a, Box* b);
	Eigen::Vector2f get_aix_component_(Eigen::Vector2f input, int direction);
	LibParallexScroll* parallex_instance_;
	
	inline float relu(float input)
	{
		return input > 0 ? input : 0;
	}
};

