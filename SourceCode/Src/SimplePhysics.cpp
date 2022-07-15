#include "SimplePhysics.h"
#include <iostream>

SimplePhysics::SimplePhysics()
{
}

SimplePhysics::~SimplePhysics()
{
}
float SimplePhysics::get_entity_velocity_x(size_t idx)
{
	if (idx >= objects_.size())
	{
		return 0.f;
	}
	return objects_.at(idx)->velocity.x();
}
float SimplePhysics::get_entity_velocity_y(size_t idx)
{
	if (idx >= objects_.size())
	{
		return 0.f;
	}
	return objects_.at(idx)->velocity.y();
}
//void SimplePhysics::add_entity(std::string name)
//{
//	auto sp = new CSprite(name.c_str());
//	auto box = Box();
//	box.height = sp->GetSpriteHeight();
//	box.width = sp->GetSpriteWidth();
//	box.position = Eigen::Vector2f(sp->GetSpritePositionX(), sp->GetSpritePositionY());
//
//	auto obj = Object();
//	obj.velocity = Eigen::Vector2f(0, 0);
//	obj.force = Eigen::Vector2f(0, 0);
//	obj.mass = 10.0;
//	obj.hit_box = box;
//	obj.type = ObjType::ENTITY;
//	obj.velocity_handeler = NULL;
//	objects_.push_back(&obj);
//
//}

void SimplePhysics::add_entity(std::string name, std::function<void(float, float)> vel_fun)
{
	auto entity = new CSprite(name.c_str());
	auto hit_box = new Box();
	hit_box->height = entity->GetSpriteHeight();
	hit_box->width = entity->GetSpriteWidth();
	hit_box->position = Eigen::Vector2f(entity->GetSpritePositionX(), entity->GetSpritePositionY());

	auto obj = new Object();
	obj->sprite = entity;
	obj->velocity = Eigen::Vector2f(0, 0);
	obj->force = Eigen::Vector2f(0, 0);
	obj->mass = 1.0;
	obj->hit_box = hit_box;
	obj->type = ObjType::ENTITY;
	obj->velocity_handeler = vel_fun;
	objects_.push_back(obj);
}

void SimplePhysics::set_force_1(std::string name, float x, float y)
{
	Object* obj = NULL;
	// find the spirite with the name in vector
	for (auto& item : objects_)
	{
		if (strcmp(name.c_str(), item->sprite->GetName()) == 0)
		{
			obj = item;
		}
	}

	if (obj)
	{
		obj->force_1 << x, y;
	}
	else
	{
		return;
	}
}

void SimplePhysics::init()
{
	for (auto& item : objects_)
	{
		item->hit_box->height = item->sprite->GetSpriteHeight();
		item->hit_box->width = item->sprite->GetSpriteWidth();
		item->hit_box->position << item->sprite->GetSpritePositionX(), item->sprite->GetSpritePositionY();
	}
}

void SimplePhysics::on_colid_callback(std::string src_name, std::string tar_name)
{
	int src_idx = -1;
	int tar_idx = -1;
	for (size_t i = 0; i < objects_.size(); i++)
	{
		if(strcmp(src_name.c_str(), objects_[i]->sprite->GetName()) == 0)
			src_idx = i;
		if (strcmp(tar_name.c_str(), objects_[i]->sprite->GetName()) == 0)
			tar_idx = i;
	}

	if (src_idx == -1 || tar_idx == -1)
	{
		// not managed
		return;
	}
	if (src_idx == tar_idx)
	{
		// I have no idea when will this happen
		std::cout << "wtf" << std::endl;
		return;
	}

	auto src = objects_[src_idx];
	auto tar = objects_[tar_idx];

	if (src->type == ObjType::ENTITY && tar->type == ObjType::MAP_TILE)
	{
		// someone hit someting, bang!

		// determin the direction of the hit
		auto col_stat = test_collision_(src->hit_box, tar->hit_box);

		// get the component of velocity on each axis
		Eigen::Vector2f e_left;
		e_left<< -1, 0;
		Eigen::Vector2f left_component = relu(e_left.dot(src->velocity)) * e_left;

		Eigen::Vector2f e_right;
		e_right<< 1, 0;
		Eigen::Vector2f right_component = relu(e_right.dot(src->velocity)) * e_right;

		Eigen::Vector2f e_up;
		e_up<< 0, -1;
		Eigen::Vector2f up_component = relu(e_up.dot(src->velocity)) * e_up;

		Eigen::Vector2f e_down;
		e_down<< 0, 1;
		Eigen::Vector2f down_component = relu(e_down.dot(src->velocity)) * e_down;

		// remove the component of velocity on coliding axis
		switch (col_stat)
		{
		case CollisionStatus::RIGHT:
			src->velocity -= right_component;
			break;
		case CollisionStatus::LEFT:
			src->velocity -= left_component;
			break;
		case CollisionStatus::UP:
			src->velocity -= up_component;
			break;
		case CollisionStatus::DOWN:
			src->velocity -= down_component;
			break;
		}

	}
}

void SimplePhysics::add_map_tile(std::string name)
{
	auto map_tile = new CSprite(name.c_str());
	auto box = new Box();
	box->height = map_tile->GetSpriteHeight();
	box->width = map_tile->GetSpriteWidth();
	box->position = Eigen::Vector2f(map_tile->GetSpritePositionX(), map_tile->GetSpritePositionY());

	auto obj = new Object();
	 obj->sprite = map_tile;
	obj->velocity = Eigen::Vector2f(0, 0);
	obj->force = Eigen::Vector2f(0, 0);
	obj->mass = 10.0;
	obj->hit_box = box;
	obj->type = ObjType::MAP_TILE;
	objects_.push_back(obj);
}

void SimplePhysics::main_loop(float dt)
{
	collisions_.clear();
	for (Object* obj : objects_) {
		// update hit_box info
		obj->hit_box->position << obj->sprite->GetSpritePositionX(), obj->sprite->GetSpritePositionY();

		if (obj->type == ObjType::MAP_TILE)
		{
			continue;
		}

		obj->force += obj->force_1;
		obj->force += obj->mass * gravity_; // apply a force

		obj->velocity += obj->force / obj->mass * dt;
		//obj->Position += obj->Velocity * dt;

		obj->force << 0, 0; // reset net force at the end
	}
	for (Object* a : objects_) {
		for (Object* b : objects_) {
			if (a == b)
			{
				continue;
			}
			auto col = test_collision_(a->hit_box, b->hit_box);
			if (col != 0)
			{
				
				collisions_.emplace_back(a, b, col);
			}
		}
	}

	// handel collisions
	// handel_collisions_();

	// update speed
	for (auto& item : objects_)
	{
		if (item->velocity_handeler)
		{
			item->velocity_handeler(item->velocity.x(), item->velocity.y());
		}
	}
}

int SimplePhysics::test_collision_(Box* a, Box* b)
{
	Eigen::Vector2f tf = b->position - a->position;
	double dx = tf.x();
	double dy = tf.y();
	return CollisionStatus::DOWN;
}

void SimplePhysics::handel_collisions_()
{
	for (auto& item : collisions_)
	{
		if (item.a->type == ObjType::ENTITY
			&& item.b->type == ObjType::MAP_TILE)
		{
			// someone hit someting, bang!
			// get the component of velocity on each axis
			Eigen::Vector2f e_left;
			e_left<< -1, 0;
			Eigen::Vector2f left_component = relu(e_left.dot(item.a->velocity)) * e_left;

			Eigen::Vector2f e_right;
			e_right<< 1, 0;
			Eigen::Vector2f right_component = relu(e_right.dot(item.a->velocity)) * e_right;

			Eigen::Vector2f e_up;
			e_up<< 0, 1;
			Eigen::Vector2f up_component = relu(e_up.dot(item.a->velocity)) * e_up;

			Eigen::Vector2f e_down;
			e_down<< 0, -1;
			Eigen::Vector2f down_component = relu(e_down.dot(item.a->velocity)) * e_down;

			// remove the component of velocity on coliding axis
			switch (item.col_status)
			{
			case CollisionStatus::RIGHT:
				item.a->velocity -= right_component;
				break;
			case CollisionStatus::LEFT:
				item.a->velocity -= left_component;
				break;
			case CollisionStatus::UP:
				item.a->velocity -= up_component;
				break;
			case CollisionStatus::DOWN:
				item.a->velocity -= down_component;
				break;
			}

			// move the object to the edge of the colliding object
			// maybe in the future
		}
	}


}


