#pragma once
#include <unordered_map>
#include <typeindex>
#include <memory>
#include <Engine/Unit/Components/IComponent.hpp>
#include <Engine/Position.hpp>
#include <Engine/Unit/Components/MovementComponent.hpp>
#include <optional>

namespace sw::engine
{
	class IUnit 
	{
	public:
		using ComponentType = std::type_index;
		using ComponentMap = std::unordered_map<ComponentType, std::shared_ptr<IComponent>>;
		using unitId = size_t;

	private:
		unitId _id;
		ComponentMap components;

	public:
		virtual ~IUnit() = default;

		template<typename ComponentT, typename... Args>
		void addComponent(Args&&... args)
		{
			components[typeid(ComponentT)] = std::make_shared<ComponentT>(std::forward<Args>(args)...);
		}

		template<typename ComponentT>
		std::shared_ptr<ComponentT> getComponent() 
		{
			auto it = components.find(typeid(ComponentT));
			if (it != components.end()) 
			{
				return std::dynamic_pointer_cast<ComponentT>(it->second);
			}
			return nullptr;
		}

		inline unitId getId() const { return _id; }
		inline void setId(unitId id) { _id = id; }
		bool isMovable()
		{
			auto movement = getComponent<MovementComponent>();
			if(movement)
				if(movement->isMovable())
					return true;
			return false;
		}

		virtual void move(uint32_t deltaX, uint32_t deltaY)
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