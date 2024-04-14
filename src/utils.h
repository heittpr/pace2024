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
 * Utilities. I/O, etc.
 */

#include "bipartite_graph.h"

#include <cassert>
#include <iostream>
#include <memory>
#include <sstream>

inline void readNextLine(std::istringstream& in)
{
	std::string line;
	while (std::getline(std::cin, line)) {
		if (line[0] == 'c') continue;
		in = std::istringstream(line);
		return;
	}
	assert(false);
}

inline void readBipartiteGraph(std::unique_ptr<BipartiteGraph> input_graph)
{
	std::istringstream in;
	readNextLine(in);

	std::string discard;
	int n_a, n_b, edge_count;
	in >> discard >> discard >> n_a >> n_b >> edge_count;

	input_graph = std::make_unique<BipartiteGraph> (n_a, n_b);

	for (unsigned i = 0; i < (unsigned) edge_count; i++)
  {
		readNextLine(in);
		int a, b;
		in >> a >> b;
		input_graph->addEdge(a - 1, b - 1);
	}
}
