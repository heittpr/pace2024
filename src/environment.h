/******************************************************************************
 * Top contributors (to current version):
 *   Alan Prado
 *
 * This file is part of Banana, a one-sided crossing minimization solver.
 *
 * Copyright (c) 2024 by the authors listed in the file AUTHORS in the
 * top-level source directory and their institutional affiliations. All rights
 * reserved. See the file LICENSE.md in the top-level source directory for
 * licensing information.
 * ****************************************************************************
 *
 * Global environment
 */

#ifndef __PACE2024__ENVIRONMENT_HPP
#define __PACE2024__ENVIRONMENT_HPP

#include "options.h"

#include <memory>

namespace banana {

class Environment
{
 public:
  Environment() = default;
  ~Environment() = default;
  static void setOptions(int argc, char* argv[]);
  static options::Options options();

 protected:
  static inline options::Options m_options = options::Options();
};

} // namespace banana

#endif  // __PACE2024__ENVIRONMENT_HPP
