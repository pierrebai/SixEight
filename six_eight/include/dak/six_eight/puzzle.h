#pragma once

#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers

#include "dak/six_eight/position.h"
#include "dak/six_eight/tile.h"

#include <vector>
#include <algorithm>
#include <optional>


namespace dak::six_eight
{
   struct solution_t;

   ////////////////////////////////////////////////////////////////////////////
   //
   // Sub puzzle

   struct sub_puzzle_t
   {
      tile_t               tile_to_place;
      std::vector<tile_t>  other_tiles;
      position_t           position_to_fill;
   };

   ////////////////////////////////////////////////////////////////////////////
   //
   // Puzzle, provide tiles and next position to try to the solver.

   struct puzzle_t
   {
      using tiles_t = std::vector<tile_t>;

      // Create a puzzle.
      puzzle_t();
      puzzle_t(const std::vector<tile_t>& some_tiles);

      // Solver interaction.

      // Create the initial list of sub-puzzles to solve.
      std::vector<sub_puzzle_t> create_initial_sub_puzzles() const;

      // Create sub-puzzles from a given sub-puzzle that has its tile placed.
      std::vector<sub_puzzle_t> create_sub_puzzles(const sub_puzzle_t& a_current_sub_puzzle, const solution_t& a_partial_solution) const;

      // Get the list of potential position for the tile-to-be-placed of the given sub-puzzle.
      std::vector<position_t> get_sub_puzzle_positions(const sub_puzzle_t& a_current_sub_puzzle, const solution_t& a_partial_solution) const;

      // Verify if there are more sub-puzzles to be created from the given sub-puzzle.
      bool has_more_sub_puzzles(const sub_puzzle_t& a_current_sub_puzzle) const;

      // Verify if the solution satisfies the initial puzzle.
      bool is_solution_valid(const solution_t& a_solution) const;

      // The description of the puzzle.

      // The list of tiles to place.
      const tiles_t& initial_tiles() const { return my_initial_tiles; }
      size_t initial_tiles_count() const { return my_initial_tiles.size(); }

   protected:
      tiles_t           my_initial_tiles;
   };

}

