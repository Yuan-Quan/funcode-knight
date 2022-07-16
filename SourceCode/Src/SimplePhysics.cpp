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

void SimplePhysics::set_force_temp(std::string name, float x, float y)
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

void SimplePhysics::set_vel_offset(std::string name, float x, float y)
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
		obj->vel_1 << x, y;
	}
	else
	{
		return;
	}

}

void SimplePhysics::set_vel_temp(std::string name, float x, float y)
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
		obj->vel_tmp << x, y;
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

void SimplePhysics::on_colid_callback(Object* src, Object* tar)
{
	if (src->type == ObjType::ENTITY && tar->type == ObjType::MAP_TILE)
	{
		// someone hit someting, bang!

		// determin the direction of the hit
		test_collision_(src, tar);

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
		test_collision_(src, tar);

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

void SimplePhysics::add_map_tile(std::vector<std::string> names)
{
	for (auto& item : names)
	{
		add_map_tile(item);
	}
}

void SimplePhysics::main_loop(float dt)
{
	dt_ = dt;
	//collisions_.clear();
	for (Object* obj : objects_) {
		// update hit_box info
		obj->hit_box->position << obj->sprite->GetSpritePositionX(), obj->sprite->GetSpritePositionY();

		if (obj->type == ObjType::MAP_TILE)
		{
			continue;
		}

		Eigen::Vector2f drag = -obj->velocity * drag_factor_ * obj->velocity.norm();
		Eigen::Vector2f fric = -obj->velocity * fric_factor_;

		obj->force += obj->force_1;
		obj->force += obj->force_tmp;
		obj->force += obj->mass * gravity_; // apply a force
		obj->force += drag;
		obj->force += fric;

		obj->velocity *= damping_factor_;
		obj->velocity += obj->force / obj->mass * dt;
		obj->velocity += obj->vel_tmp;
		//obj->Position += obj->Velocity * dt;

		obj->force << 0, 0; // reset net force at the end
		obj->force_tmp << 0, 0;
		obj->vel_tmp << 0, 0;

		reset_col_(obj);
	}


	for (Object* a : objects_) {
		for (Object* b : objects_) {
			if (a == b)
			{
				continue;
			}
			if (is_col_(a->hit_box, b->hit_box))
			{
				on_colid_callback(a, b);
			}
		}
	}

	process_collisions_();

	// handel collisions
	// handel_collisions_();

	// update speed
	for (auto& item : objects_)
	{
		if (item->velocity_handeler)
		{
			item->velocity_handeler(item->velocity.x() + item->vel_1.x(), item->velocity.y() + item->vel_1.y());
		}
	}
}

void SimplePhysics::test_collision_(Object* a, Object* b)
{
	Eigen::Vector2f tf = a->hit_box->position - b->hit_box->position;

	// fix funcode's stupid co-ord system
	tf.y() = -tf.y();

	float angle_tf = atan2(tf.y(), tf.x());
	float angle_top_right = atan2(0.5 * b->hit_box->height, 0.5 * b->hit_box->width);
	float angle_top_left = atan2(0.5 * b->hit_box->height, -0.5 * b->hit_box->width);
	float angle_bottom_right = atan2(-0.5 * b->hit_box->height, 0.5 * b->hit_box->width);
	float angle_bottom_left = atan2(-0.5 * b->hit_box->height, -0.5 * b->hit_box->width);

	if (angle_bottom_right <= angle_tf && angle_tf <= angle_top_right)
	{
		a->is_against_left = true;
	}
	if (angle_top_right <= angle_tf && angle_tf <= angle_top_left)
	{
		a->is_against_down = true;
	}
	// this is annoying
	if (angle_top_left <= angle_tf || angle_tf <= angle_bottom_left)
	{
		a->is_against_right = true;
	}
	if (angle_bottom_left <= angle_tf && angle_tf <= angle_bottom_right)
	{
		a->is_against_up = true;
	}

}

//@DEPRECATED
//void SimplePhysics::handel_collisions_()
//{
//	for (auto& item : collisions_)
//	{
//		if (item.a->type == ObjType::ENTITY
//			&& item.b->type == ObjType::MAP_TILE)
//		{
//			// someone hit someting, bang!
//			// get the component of velocity on each axis
//			Eigen::Vector2f e_left;
//			e_left<< -1, 0;
//			Eigen::Vector2f left_component = relu(e_left.dot(item.a->velocity)) * e_left;
//
//			Eigen::Vector2f e_right;
//			e_right<< 1, 0;
//			Eigen::Vector2f right_component = relu(e_right.dot(item.a->velocity)) * e_right;
//
//			Eigen::Vector2f e_up;
//			e_up<< 0, 1;
//			Eigen::Vector2f up_component = relu(e_up.dot(item.a->velocity)) * e_up;
//
//			Eigen::Vector2f e_down;
//			e_down<< 0, -1;
//			Eigen::Vector2f down_component = relu(e_down.dot(item.a->velocity)) * e_down;
//
//			// remove the component of velocity on coliding axis
//			switch (item.col_status)
//			{
//			case CollisionStatus::RIGHT:
//				item.a->velocity -= right_component;
//				break;
//			case CollisionStatus::LEFT:
//				item.a->velocity -= left_component;
//				break;
//			case CollisionStatus::UP:
//				item.a->velocity -= up_component;
//				break;
//			case CollisionStatus::DOWN:
//				item.a->velocity -= down_component;
//				break;
//			}
//
//			// move the object to the edge of the colliding object
//			// maybe in the future
//		}
//	}
//
//
//}

void SimplePhysics::process_collisions_()
{
	for (auto& item : objects_)
	{
		item->col_update_span++;
		if (item->is_against_down || item->is_against_left || item->is_against_right || item->is_against_up)
		{
			update_col_intergral(item);
			if (item->is_against_left)
				remove_aix_component_(item, CollisionStatus::LEFT);
			if (item->is_against_right)
				remove_aix_component_(item, CollisionStatus::RIGHT);
			if (item->is_against_up)
				remove_aix_component_(item, CollisionStatus::UP);
			if (item->is_against_down)
				remove_aix_component_(item, CollisionStatus::DOWN);
		}
		//if (item->col_update_span >= 5)
		//{
		//	reset_col_(item);
		//	continue;
		//}

	}
}

void SimplePhysics::update_col_intergral(Object* obj)
{
	// this is inaccurate but works for now
	//@DEPRECATED
	obj->tmp_col_vel_intergral += dt_ * obj->velocity;

	Eigen::Vector2f e_left;
	e_left<< -1, 0;
	Eigen::Vector2f e_right;
	e_right<< 1, 0;
	Eigen::Vector2f e_up;
	e_up<< 0, -1;
	Eigen::Vector2f e_down;
	e_down<< 0, -1;

	// relu here is not needed
	if (obj->is_against_left)
	{
		if (relu(obj->tmp_col_vel_intergral.dot(e_right)) >= collision_cancel_epsilon_)
		{
			obj->is_against_left = false;
			//obj->tmp_col_vel_intergral << 0, 0;
		}
	}
	if (obj->is_against_right)
	{
		if (relu(obj->tmp_col_vel_intergral.dot(e_left)) >= collision_cancel_epsilon_)
		{
			obj->is_against_right = false;
			//obj->tmp_col_vel_intergral << 0, 0;
		}
	}
	if (obj->is_against_up)
	{
		if (relu(obj->tmp_col_vel_intergral.dot(e_down)) >= collision_cancel_epsilon_)
		{
			obj->is_against_up = false;
			//obj->tmp_col_vel_intergral << 0, 0;
		}
	}
	if (obj->is_against_down)
	{
		if (relu(obj->velocity.dot(e_up)) >= collision_cancel_epsilon_)
		{
			obj->is_against_down = false;
			//obj->tmp_col_vel_intergral << 0, 0;
		}
	}
}

void SimplePhysics::remove_aix_component_(Object* obj, int direction)
{
	obj->velocity -= get_aix_component_(obj->velocity, direction);
	obj->vel_1 -= get_aix_component_(obj->vel_1, direction);
}

void SimplePhysics::reset_col_(Object* obj)
{
	obj->is_against_down = false;
	obj->is_against_up = false;
	obj->is_against_left = false;
	obj->is_against_right = false;

	obj->col_update_span = 0;
}

bool SimplePhysics::is_col_(Box* a, Box* b)
{
	float rect1x = a->position.x() - a->width / 2;
	float rect1y = a->position.y() - a->height / 2;
	float rect1w = a->width;
	float rect1h = a->height;

	float rect2x = b->position.x() - b->width / 2;
	float rect2y = b->position.y() - b->height / 2;
	float rect2w = b->width;
	float rect2h = b->height;

	return (rect1x < rect2x + rect2w &&
		rect1x + rect1w > rect2x &&
		rect1y < rect2y + rect2h &&
		rect1h + rect1y > rect2y);
}

Eigen::Vector2f SimplePhysics::get_aix_component_(Eigen::Vector2f input, int direction)
{
	Eigen::Vector2f e_direction;
	switch (direction)
	{
	case CollisionStatus::UP:
		e_direction << 0, -1;
		break;
	case CollisionStatus::DOWN:
		e_direction << 0, 1;
		break;
	case CollisionStatus::LEFT:
		e_direction << -1, 0;
		break;
	case CollisionStatus::RIGHT:
		e_direction << 1, 0;
		break;
	}

	return relu(e_direction.dot(input)) * e_direction;
}


