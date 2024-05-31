/******************************************************************************
 * Top contributors (to current version):
 *   Alan Prado, Luis Higino
 *
 * This file is part of Banana, a one-sided crossing minimization solver.
 *
 * Copyright (c) 2024 by the authors listed in the file AUTHORS in the
 * top-level source directory and their institutional affiliations. All rights
 * reserved. See the file LICENSE.md in the top-level source directory for
 * licensing information.
 * ****************************************************************************
 *
 * Base solver for the one-sided crossing minimization problem
 */

#include "base_solver.h"
#include "environment.h"
#include "ip_solver_or.h"
#include "ip_solver_gurobi.h"
#include "ip_solver_lpsolve.h"
#include "options.h"
#include "utils.h"

#include <cassert>
#include <iostream>
#include <string>
#include <stdexcept>

namespace banana {
namespace solver {

BaseSolver::BaseSolver(graph::BipartiteGraph graph) : m_graph(graph)
{
  const auto &ip_solver = Environment::options().ip.solverMode;
  const auto &ip_sub_solver = Environment::options().ip.subSolverMode;
  switch (ip_solver)
  {
  #ifdef USE_LPSOLVE
  case options::IPSolverMode::LPSOLVE:
    m_ipSolver = std::make_unique<ip::LPSolveSolver>(graph);
    break;
  #endif
  #ifdef USE_GUROBI
  case options::IPSolverMode::GUROBI:
    m_ipSolver = std::make_unique<ip::GurobiSolver>(graph);
    break;
  #endif
  #ifdef USE_OR_TOOLS
  case options::IPSolverMode::OR_TOOLS:
    m_ipSolver = std::make_unique<ip::OrToolsSolver>(graph, ip_sub_solver);
    break;
  #endif
  default:
    throw std::invalid_argument("Invalid IP Solver!");

  }
}

void BaseSolver::verifySolution(int expected_crossings)
{
  std::string path = Environment::options().verify.verifyPath;
  std::vector<int> order = utils::readSolution<int>(path);
  // TODO: Reimplement the old verify function
  std::vector<Oracle::Vertex> order_oracle;
  for (auto vertex : order)
  {
    order_oracle.emplace_back(vertex - m_graph.countVerticesA(), 1);
  }
  assert(Environment::oracle().verify(order_oracle, expected_crossings));
}

void BaseSolver::runBanana()
{
  int crossings = m_ipSolver->solve();
  std::vector<Oracle::Vertex> order;
  m_ipSolver->explain(order);
  assert(Environment::oracle().verify(order, crossings));
  
  if (Environment::options().verify.verifyMode ==
      banana::options::VerifyMode::COMPLETE)
  {
    verifySolution(crossings);
  }
  for (auto [vertex, _] : order)
  {
    std::cout << vertex + m_graph.countVerticesA() + 1 << "\n";
  }
}

Oracle::SubProblem BaseSolver::recursiveSolver(Oracle::SubProblem &instance) {
  
}

} // namespace solver
} // namespace banana
