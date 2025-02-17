// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef MVVM_STANDARDITEMS_AXISITEMS_H
#define MVVM_STANDARDITEMS_AXISITEMS_H

//! @file axisitems.h
//! Collection of axis items for 1D and 2D data/plotting support.

#include <mvvm/model/compounditem.h>
#include <memory>
#include <vector>

namespace ModelView
{

/*!
@class BasicAxisItem
@brief Base class for all axes items.

Has min, max defined, but nothing else.
*/

class CORE_EXPORT BasicAxisItem : public CompoundItem
{
public:
    static inline const std::string P_MIN = "P_MIN";
    static inline const std::string P_MAX = "P_MAX";

    explicit BasicAxisItem(std::string model_type);

protected:
    void register_min_max();
};

/*!
@class ViewportAxisItem
@brief Item to represent viewport axis.

ViewportAxisItem serve as a counterpart of QCPAxis from QCustomPlot.
Intended to cary title, fonts etc.
*/

class CORE_EXPORT ViewportAxisItem : public BasicAxisItem
{
public:
    static inline const std::string P_TITLE = "P_TITLE";
    static inline const std::string P_IS_LOG = "P_IS_LOG";
    explicit ViewportAxisItem(std::string model_type = Constants::ViewportAxisItemType);

    std::pair<double, double> range() const;

    void set_range(double lower, double upper);

    bool is_in_log() const;
};

/*!
@class BinnedAxisItem
@brief Item to represent an axis with arbitrary binning.

Base class to define an axis with specific binning (fixed, variable). Used in Data1DItem and
Data2Ditem to store 1d and 2d data.  Doesn't carry any appearance info (e.g. axis title, label
size, etc) and thus not intended for direct plotting.
*/

//!

class CORE_EXPORT BinnedAxisItem : public BasicAxisItem
{
public:
    static inline const std::string P_NBINS = "P_NBINS";

    explicit BinnedAxisItem(std::string model_type);

    std::pair<double, double> range() const;

    int size() const;

    virtual std::vector<double> binCenters() const = 0;
};

/*!
@class FixedBinAxisItem
@brief Item to represent fixed bin axis.

Defines an axis with equidistant binning.
*/

//!

class CORE_EXPORT FixedBinAxisItem : public BinnedAxisItem
{
public:
    FixedBinAxisItem();

    static std::unique_ptr<FixedBinAxisItem> create(int nbins, double xmin, double xmax);

    std::vector<double> binCenters() const;
};

} // namespace ModelView

#endif  // MVVM_STANDARDITEMS_AXISITEMS_H
