#include "dak/six_eight/solution.h"

#include <algorithm>
#include <set>
#include <map>
#include <exception>


namespace dak::six_eight
{
   ////////////////////////////////////////////////////////////////////////////
   //
   // Solution that places all the given tiles.
   //
   // We can:
   //    - Rotate a solution of a given amount (increment of quarter of a turn).
   //    - Check if a position is already occupied.
   //    - Check if a tile at a given position would be compatible with the solution.
   //    - Check if two solutions are the exactly the same.
   //    - Check if vector of solutions already contains a solution.
   //    - Add a solution if it is not already known.
   solution_t::solution_t()
   {
      memset(my_tiles_at_pos, 0, 6 * 8 * sizeof(tile_t::id_t));
   }

   void solution_t::add_tile(const tile_t& a_tile, const position_t& a_pos)
   {
      my_tiles[my_tiles_count].pos = a_pos;
      my_tiles[my_tiles_count].tile = a_tile;
      my_tiles_count += 1;
      for (const position_t& tile_block_pos : a_tile.get_positions().block_positions) {
         const position_t placed_block_pos = a_pos.move(tile_block_pos);
         #ifdef WAWA_DEBUG
            if (placed_block_pos.x() < 0 || placed_block_pos.x() >= 6)
               return throw std::exception("invalid tile position");

            if (placed_block_pos.y() < 0 || placed_block_pos.x() >= 8)
               return throw std::exception("invalid tile position");
         #endif

         my_tiles_at_pos[placed_block_pos.x()][placed_block_pos.y()] = a_tile.id();
      }
   }

   tile_t& solution_t::internal_tile_at(const position_t& a_pos) const
   {
      static tile_t invalid(0);

      if (a_pos.x() < 0 || a_pos.x() >= 6)
         return invalid;

      if (a_pos.y() < 0 || a_pos.y() >= 8)
         return invalid;
      
      const char id = my_tiles_at_pos[a_pos.x()][a_pos.y()];
      if (id == 0)
         return invalid;

      for (size_t i = 0; i < my_tiles_count; ++i) {
         const placed_tile_t& placed_tile = my_tiles[i];
         if (placed_tile.tile.id() == id)
            return const_cast<tile_t &>(placed_tile.tile);
      }
      
      return invalid;
   }

   bool solution_t::is_occupied(const position_t& a_pos) const
   {
      if (a_pos.x() < 0 || a_pos.x() >= 6)
         return true;

      if (a_pos.y() < 0 || a_pos.y() >= 8)
         return true;
      
      return internal_tile_at(a_pos).id() != 0;
   }

   position_t solution_t::get_next_position_to_fill() const
   {
      for (int y = 0; y < 8; ++y) {
         for (int x = 0; x < 6; ++x) {
            position_t position_to_fill = position_t(x, y);
            if (!is_occupied(position_to_fill)) {
               return position_to_fill;
            }
         }
      }

      return position_t(-1000, -1000);
   }

   bool solution_t::is_compatible(const tile_t& a_tile, const position_t a_pos) const
   {
      for (const position_t& tile_block_pos : a_tile.get_positions().block_positions) {
         const position_t placed_block_pos = a_pos.move(tile_block_pos);
         if (is_occupied(placed_block_pos))
            return false;
      }
      return true;
   }

   void solution_t::normalize()
   {
      std::sort(my_tiles, my_tiles + my_tiles_count);
   }

   bool solution_t::is_valid() const
   {
      return my_tiles_count == 8;
   }
  
}
