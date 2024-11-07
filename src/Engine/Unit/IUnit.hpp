#pragma once
#include <unordered_map>
#include <typeindex>
#include <memory>
#include <Engine/Unit/Components/IComponent.hpp>
#include <Engine/Position.hpp>
#include <Engine/Unit/Components/MovementComponent.hpp>
#include <optional>
#include <vector>

namespace sw::engine
{
	class IUnit;

	using ComponentType = std::type_index;
	using ComponentMap = std::unordered_map<ComponentType, std::vector<std::shared_ptr<IComponent>>>;
	using unitId = uint32_t;
	using unitPtrVec = std::vector<std::shared_ptr<IUnit>>;

	class IUnit
	{
	public:

	private:
		unitId _id;
		ComponentMap components;

	public:
		virtual ~IUnit() = default;

		inline unitId getId() const { return _id; }
		inline void setId(unitId id) { _id = id; }

		template<typename ComponentT, typename... Args>
		void addComponent(Args&&... args)
		{
			components[typeid(ComponentT)].push_back(std::make_shared<ComponentT>(std::forward<Args>(args)...));
		}

		// Return first component in Vector<IComponents> by ComponentT
		template<typename ComponentT>
		std::shared_ptr<ComponentT> getComponent() 
		{
			auto it = components.find(typeid(ComponentT));
			if (it != components.end()) 
			{
				return std::dynamic_pointer_cast<ComponentT>(it->second.at(0));
			}
			return nullptr;
		}

		// Return Vector<IComponents> by ComponentT
		template<typename ComponentT>
		std::shared_ptr<ComponentT> getAllComponents() 
		{
			auto it = components.find(typeid(ComponentT));
			if (it != components.end()) 
			{
				return std::dynamic_pointer_cast<ComponentT>(it->second);
			}
			return nullptr;
		}

		bool isMovable()
		{
			auto movement = getComponent<MovementComponent>();
			if(movement)
				if(movement->isMovable())
					return true;
			return false;
		}

		virtual void move(int deltaX, int deltaY)
		{
			if(!isMovable())
				throw std::runtime_error("Call move in nonmovable unit");
			getComponent<MovementComponent>()->move(deltaX, deltaY);
		}

		virtual Position getPosition()
		{
			if(!isMovable())
				throw std::runtime_error("Call move in nonmovable unit");
			return getComponent<MovementComponent>()->getPosition();
		}
	};
}