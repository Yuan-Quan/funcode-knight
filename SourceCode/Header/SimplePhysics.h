#pragma once
#include <Eigen/Dense>
#include <vector>
#include "CommonClass.h"

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
	Eigen::Vector2f force;
	Eigen::Vector2f force_1;
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

struct Collision{
	Object* a;
	Object* b;
	int col_status;

	Collision(Object* a, Object* b, int col_status)
	{
		this->a = a;
		this->b = b;
		this->col_status = col_status;
	}
};

public:
	SimplePhysics();
	~SimplePhysics();

	float get_entity_velocity_x(size_t idx);
	float get_entity_velocity_y(size_t idx);
	void add_map_tile(std::string name);
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
	
	void init();
	void on_colid_callback(std::string src_name, std::string tar_name);
	void main_loop(float dt);

private:
	std::vector<Object*> objects_;
	Eigen::Vector2f gravity_ = Eigen::Vector2f(0.0, 9.8);

	int test_collision_(Box* a , Box* b);
	std::vector<Collision> collisions_;
	void handel_collisions_();
	
	inline float relu(float input)
	{
		return input > 0 ? input : 0;
	}
};

