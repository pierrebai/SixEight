#include "dak/six_eight/six_eight.h"
#include "dak/utility/progress.h"
#include "dak/six_eight_tests/helpers.h"

#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace dak::six_eight;
using namespace dak::utility;

namespace dak::six_eight::tests
{
   TEST_CLASS(solve_tests)
   {
   public:
      
      TEST_METHOD(solve_simple_puzzle)
      {
         const std::vector<tile_t> simple_tiles = { 3, 5, 8, 12, 14, 43, 46, 50, 52, 54, };
         const std::vector<color_t> simple_loops = { color_t::blue(), };
         const bool simple_must_be_loops = true;
         any_shape_puzzle_t simple_puzzle(simple_tiles, simple_loops, simple_must_be_loops);

         struct dummy_progress_t : progress_t
         {
            void update_progress(size_t a_total_count_so_far) override {}
         };
         dummy_progress_t progress;
         auto simple_solutions = solve(simple_puzzle, progress);

         Assert::AreEqual<size_t>(48, simple_solutions.size());
      }
   };
}
