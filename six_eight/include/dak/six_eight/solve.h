#pragma once

#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers

#include "dak/six_eight/solution.h"

#include <map>

namespace dak::utility
{
   struct progress_t;
}

namespace dak::six_eight
{
   struct puzzle_t;
   using progress_t = dak::utility::progress_t;

   ////////////////////////////////////////////////////////////////////////////
   //
   // Solve the placement of all given tiles.

   using all_solutions_t = std::map<solution_t, size_t>;

   all_solutions_t solve(const puzzle_t& a_puzzle, progress_t& a_progress);
}

