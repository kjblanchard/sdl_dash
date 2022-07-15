#pragma once
#include <supergoon_engine_export.h>
#include <supergoon_engine/interfaces/i_update.hpp>
#include <supergoon_engine/interfaces/i_initialize.hpp>
#include <supergoon_engine/interfaces/i_debug.hpp>
#include <supergoon_engine/interfaces/i_draw.hpp>
#include <supergoon_engine/primitives/vector2.hpp>
#include <supergoon_engine/engine/component.hpp>
#include <vector>
#include <memory>
#include <algorithm>

class World;
class Camera;
class Level;
/**
 * Base class for all objects in the engine, has a location, and a list of components.
 */
class SUPERGOON_ENGINE_EXPORT GameObject : public IUpdate, public IInitialize, public IDebug, public IDraw
{
private:
protected:
    /**
     * Pointer to world, as a convenience function.
     */
    static World *world;
    /**
     * Pointer to Main Camera, as a convenience function.
     */
    static Camera *main_camera;
    /**
     * List of components on the gameObject
     *
     * This is in Shared pointer, so it is destructed automatically when this gameobject is destroyed.
     */
    std::vector<std::shared_ptr<Component>> components_;

public:
    Vector2 location;
    GameObject(Vector2 loc = Vector2());
    virtual ~GameObject() override;

    Level* GetLevel();

    void Initialize() override;
    /**
     * Calls update on all components on this gameobject.
     * @param gametime Reference to the gametime
     */
    void Update(const Gametime &gametime) override;
    /**
     * Calls Draw all components on this gameobject.
     * @param Spritebatch the spritebatch
     */
    void Draw(Graphics::SpriteBatch &spritebatch) override;
    /**
     * Adds a component to this gameobject, and then sorts them.
     * @param component pointer to the component to add.
     */
    inline void AddComponent(Component *component)
    {
        components_.push_back(std::unique_ptr<Component>(component));
        std::sort(components_.begin(), components_.end());
    }
    inline Component* GetComponent(int tag)
    {
        for (auto &component : components_)
        {
            if (component->HasTag(tag))
            {
                return component.get();
            }
        }
        return nullptr;
    }

    // inline GameObject(GameObject &&other)
    //     : components_(std::move(other.components_))
    // {
    // }

    // inline GameObject &operator=(GameObject other)
    // {
    //     swap(*this, other);
    //     return *this;
    // }

    // inline friend void swap(GameObject &lhs, GameObject &rhs)
    // {
    //     using std::swap;
    //     swap(lhs.components_, rhs.components_);
    // }
    // friend Component;
};