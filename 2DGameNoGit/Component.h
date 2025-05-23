#pragma once
#include <memory>

class GameObject;

class Component {
public:
	virtual ~Component() = default;
	void setOwner(GameObject* gameObject) { this->owner = gameObject; }
	virtual void init() {}
	virtual void update(float dt) {
		if (!enabled) {
			return;
		}
	}
	
	void enable() {
		enabled = true;
	}
	virtual void disable() {
		enabled = false;
	}

protected:
	bool enabled = true;
	GameObject* owner = nullptr;
};
