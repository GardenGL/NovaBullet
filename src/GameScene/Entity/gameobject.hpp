#ifndef GAMEOBJECT_HPP
#define GAMEOBJECT_HPP

#include <vector>
#include <cstdlib>
#include <string>
#include <functional> // Добавлен этот заголовок
#include <algorithm>  // Добавлен для std::remove_if

class GameObject
{
public:
    inline virtual void draw() {};
    inline virtual void drawUI() {};
    inline virtual void update() {};
    inline virtual void takeDamage(int damage) {};


    GameObject(const char *name)
    {
        this->name = name;
    }
    
    virtual ~GameObject()
    {
        for (auto child : children)
        {
            delete child;
        }
        children.clear();
    }

    void add_child(GameObject *child)
    {
        this->children.push_back(child);
        child->parent = this;
    }

    void _update()
    {
        this->update();
        for (auto child : this->children)
            child->_update();
    }

    void _drawUI(){
        this->drawUI();
        for (auto child : this->children)
            child->_drawUI();
    }

    void _draw()
    {
        this->draw();
        for (auto child : this->children)
            child->_draw();
    }

    size_t find_in_parent()
    {
        if (this->parent)
        {
            for (size_t i = 0; i < parent->children.size(); ++i)
            {
                if (parent->children[i] == this)
                    return i;
            }
        }
        return 0;
    }

    void remove_if(const std::function<bool(GameObject *)> &predicate) // Исправленная сигнатура
    {
        children.erase(std::remove_if(children.begin(), children.end(),
                                      [&](GameObject *child)
                                      {
                                          if (predicate(child))
                                          {
                                              delete child;
                                              return true;
                                          }
                                          return false;
                                      }),
                       children.end());
    }

    std::vector<GameObject *> &get_children()
    {
        return this->children;
    }

    const std::string &get_name()
    {
        return this->name;
    }

    void set_name(std::string &value)
    {
        this->name = value;
    }

    void set_name(const char *value)
    {
        this->name = std::string(value);
    }

private:
    GameObject *parent = nullptr;
    std::vector<GameObject *> children;
    std::string name;
};

#endif // GAMEOBJECT_HPP