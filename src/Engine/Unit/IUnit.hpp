#pragma once
#include <Engine/Unit/Components/IComponent.hpp>
#include <Engine/Unit/Components/MovementComponent.hpp>

#include <unordered_map>
#include <typeindex>
#include <memory>
#include <vector>

namespace sw::engine
{
	class IUnit;
	class Position;

	using ComponentType = std::type_index;
	using ComponentMap = std::unordered_map<ComponentType, std::vector<std::shared_ptr<IComponent>>>;
	using unitId = uint32_t;
	using unitPtrVec = std::vector<std::shared_ptr<IUnit>>;
	/**
	 * @class IUnit
	 * @brief Interface representing a game unit with components and a unique ID.
	 * 
	 * IUnit defines the basic structure for game units, supporting components for 
	 * various capabilities such as movement, health, and attack. Components are stored
	 * and managed in a map, enabling flexible unit customization.
	 */
	class IUnit
	{
	public:

	private:
		unitId _id;
		ComponentMap components;

	public:
		virtual ~IUnit() = default;

		/**
		 * @brief Adds a new component to the unit.
		 * @tparam ComponentT The type of component being added.
		 * @tparam Args Argument types to construct the component.
		 * @param args Arguments to initialize the component.
		 * 
		 * This method constructs a new component of type `ComponentT` with the given arguments
		 * and adds it to the unit's component map.
		 */
		template<typename ComponentT, typename... Args>
		void addComponent(Args&&... args)
		{
			components[typeid(ComponentT)].push_back(std::make_shared<ComponentT>(std::forward<Args>(args)...));
		}

		/**
		 * @brief Retrieves the first component of a specific type.
		 * @tparam ComponentT The type of component to retrieve.
		 * @return A shared pointer to the first component of type `ComponentT`, or `nullptr` if not found.
		 */
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

		/**
		 * @brief Retrieves all components of a specific type.
		 * @tparam ComponentT The type of components to retrieve.
		 * @return A vector of shared pointers to all components of type `ComponentT`, or an empty vector if none found.
		 */
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

		inline unitId getId() const noexcept { return _id; }
		inline void setId(unitId id) noexcept { _id = id; }

		/**
		 * @brief Checks if the unit is movable.
		 * @return `true` if the unit can move, `false` otherwise.
		 */
		bool isMovable();

		/**
		 * @brief Retrieves the unit's current position.
		 * @return The position of the unit as a `Position` object.
		 */
		virtual Position getPosition();
	};
}