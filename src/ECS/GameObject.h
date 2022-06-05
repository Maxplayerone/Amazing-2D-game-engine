#pragma once
#include"Audio.h"
#include"SpriteRenderer.h"
#include"Transform.h"

#include<vector>

class GameObject {
private:
	Audio* audio;
	SpriteRenderer* spriteRend;
	Transform* transform;
	
	const static unsigned int componentTypes = 3;
	std::vector<Component*> m_components;

	template<typename Base, typename T>
	inline bool Instanceof(const T* ptr) {
		return dynamic_cast<const Base*>(ptr) != nullptr;
	}

public:
	//adds a component to the game object
	template<typename T>
	int AddComponent(T& component) {
		if (!Instanceof<Component>(component)) {
			std::cout << "You need to pass a class with sub class component" << std::endl;
			return -1;
		}
		if (std::find(m_components.begin(), m_components.end(), component) != m_components.end()) {
			std::cout << "An object cannot have more than one component of the same type" << std::endl;
			return -1;
		}

		m_components.push_back(component);
		std::cout << "Vector size is now " << m_components.size() << std::endl;
		return 0;
	}


	//returns a component from the game object
	template<typename ComponentType>
	ComponentType* GetComponent() {
		for (unsigned int i = 0; i < m_components.size(); i++) {
			if (ComponentType* cmp = dynamic_cast<ComponentType*>(m_components[i])) {
				return cmp;
			}
		}
		return nullptr;
	}

	//removes component from m_components vector and returns it
	template<typename ComponentType>
	ComponentType* RemoveComponent() {
		for (unsigned int i = 0; i < m_components.size(); i++) {
			if (ComponentType* cmp = dynamic_cast<ComponentType*>(m_components[i])) {
				ComponentType* cmpCpy = cmp;
				
				m_components.erase(m_components.begin() + i);
				std::cout << "m_components length " << m_components.size() << std::endl;
				return cmpCpy;
			}
		}
	}
};