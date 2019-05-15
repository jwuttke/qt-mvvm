// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#ifndef ITEMS_H
#define ITEMS_H

#include "compounditem.h"
#include "groupitem.h"
#include <string>

//! @file items.h
//! Collection of items for our application model.

class MultiLayer : public ModelView::CompoundItem
{
public:
    static const std::string T_LAYERS;
    MultiLayer();
};

// ----------------------------------------------------------------------------

class Layer : public ModelView::CompoundItem
{
public:
    static const std::string P_THICKNESS;
    static const std::string P_COLOR;
    static const std::string T_PARTICLES;
    Layer();
};

// ----------------------------------------------------------------------------

class Particle : public ModelView::CompoundItem
{
public:
    static const std::string P_POSITION;
    static const std::string P_SHAPES;
    Particle();
};

// ----------------------------------------------------------------------------

class InterferenceFunction : public ModelView::CompoundItem
{
public:
    static const std::string P_ROTATION_ANLE;
    static const std::string P_INTEGRATION;
    static const std::string P_LATTICE_TYPE;

    InterferenceFunction();

    void activate() override;

private:
    void update_appearance();
};

// ----------------------------------------------------------------------------

class Cylinder : public ModelView::CompoundItem
{
public:
    static const std::string P_RADIUS;
    static const std::string P_HEIGHT;
    Cylinder();
};

class Sphere : public ModelView::CompoundItem
{
public:
    static const std::string P_RADIUS;
    Sphere();
};

class AnysoPyramid : public ModelView::CompoundItem
{
public:
    static const std::string P_LENGTH;
    static const std::string P_WIDTH;
    static const std::string P_HEIGHT;
    static const std::string P_ALPHA;
    AnysoPyramid();
};

class ShapeGroup : public ModelView::GroupItem
{
public:
    ShapeGroup();
};

#endif // ITEMS_H