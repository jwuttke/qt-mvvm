// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef MVVM_UTILS_FILEUTILS_H
#define MVVM_UTILS_FILEUTILS_H

#include <mvvm/core/export.h>
#include <string>

namespace ModelView {

namespace Utils {

//! Returns true if file exists.
CORE_EXPORT bool exists(const std::string& fileName);

//! Creates directory in current working directory. If such directory already exists,
//! it will be removed with all its content.
// FIXME do not remove existing directory
CORE_EXPORT void create_dir(const std::string& dir_name);

//! Creates sub directory in given parent directory (should exist).
//! If sub-directory already exists, no action will be taken.
CORE_EXPORT void create_subdir(const std::string& parentName, const std::string& subdirName);

//! Removes recursively directory with given name. Directory name is relative
//! to the parent (working directory of the executable).
CORE_EXPORT bool removeRecursively(const std::string& dirname);

}  // namespace Utils

}  // namespace ModelView

#endif  // MVVM_UTILS_FILEUTILS_H
