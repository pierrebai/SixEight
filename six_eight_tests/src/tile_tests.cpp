#include "dak/six_eight/tile.h"
#include "dak/six_eight_tests/helpers.h"

#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace dak::six_eight;

namespace dak::six_eight::tests
{
   TEST_CLASS(tile_tests)
   {
   public:
      
      TEST_METHOD(compare_tiles)
      {
         Assert::AreEqual(tile_t(), tile_t(0));

         for (std::uint8_t id = 0; id <= 56; ++id)
            Assert::AreEqual(tile_t(id), tile_t(id));

         for (std::uint8_t id = 0; id <= 56; ++id)
            for (std::uint8_t other_id = 0; other_id <= 56; ++other_id)
               if (other_id != id)
                  Assert::AreNotEqual(tile_t(id), tile_t(other_id));
      }

      TEST_METHOD(tile_id)
      {
         Assert::AreEqual<int>(tile_t().id(), 0);

         for (std::uint8_t id = 0; id <= 56; ++id)
            Assert::AreEqual<int>(tile_t(id).id(), id);
      }

      TEST_METHOD(rotate_tile)
      {
         for (std::uint8_t id = 1; id <= 56; ++id)
         {
            for (int rot = 1; rot < 20; ++rot)
            {
               const auto t1 = tile_t(id);
               const auto c1 = t1.color(direction_t(0));
               const auto t2 = tile_t(id).rotate(rot);
               const auto c2 = t2.color(direction_t(rot));
               Assert::AreEqual(c1, c2);
            }
         }
      }

      TEST_METHOD(rotate_in_place_tile)
      {
         for (std::uint8_t id = 1; id <= 56; ++id)
         {
            for (int rot = 1; rot < 20; ++rot)
            {
               auto t1 = tile_t(id);
               const auto c1 = t1.color(direction_t(0));
               t1.rotate_in_place(rot);
               const auto c2 = t1.color(direction_t(rot));
               Assert::AreEqual(c1, c2);
            }
         }
      }

      TEST_METHOD(is_same_tile)
      {
         for (std::uint8_t id = 0; id <= 56; ++id)
            for (int rot = 1; rot < 6; ++rot)
               Assert::AreEqual(true, tile_t(id).is_same(tile_t(id).rotate(rot)));

         for (std::uint8_t id = 0; id <= 56; ++id)
            for (std::uint8_t other_id = 0; other_id <= 56; ++other_id)
               if (other_id != id)
                  for (int rot = 1; rot < 6; ++rot)
                     Assert::AreEqual(false, tile_t(id).is_same(tile_t(other_id).rotate(rot)));
      }
   };
}
