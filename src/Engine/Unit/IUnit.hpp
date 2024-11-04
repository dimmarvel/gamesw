#pragma once
#include <unordered_map>
#include <typeindex>
#include <memory>
#include <Engine/Unit/Components/IComponent.hpp>

class IUnit 
{
private:
	size_t _id;
	std::unordered_map<std::type_index, std::shared_ptr<IComponent>> components;

public:
	template<typename T, typename... Args>
	void addComponent(Args&&... args) 
	{
		components[typeid(T)] = std::make_unique<T>(std::forward<Args>(args)...);
	}

	template<typename T>
	std::shared_ptr<T> getComponent() {
		auto it = components.find(typeid(T));
		if (it != components.end()) 
		{
			return std::dynamic_pointer_cast<T*>(it->second.get());
		}
		return nullptr;
	}

	size_t get_id() { return _id; }
	void set_id(size_t id) { _id = id; }
};