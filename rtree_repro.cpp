#include <vector>

#include <boost/geometry/index/rtree.hpp>
#include <boost/geometry.hpp>

namespace bg = boost::geometry;
namespace bgi = boost::geometry::index;

namespace demo {

using Point3D = bg::model::point<double, 3, bg::cs::cartesian>;
using Box3D = bg::model::box<Point3D>;

struct Sphere {
  std::array<double, 3> center;
  double radius;
};


std::vector<Sphere> make_spheres() {
  auto dummy_value = Sphere{{0.0, 0.0, 0.0}, 1.0};
  return std::vector<Sphere>(1000, dummy_value);
}

}


namespace boost { namespace geometry { namespace index {

template <>
struct indexable<demo::Sphere> {
  typedef demo::Sphere V;
  typedef demo::Box3D const result_type;

  result_type operator()(const demo::Sphere& sphere) const {
    auto [x, y, z] = sphere.center;
    auto r = sphere.radius;
    return {{x - r, y - r, z - r}, {x + r, y + r, z + r}};
  }
};

}}}



int main() {
  auto spheres = demo::make_spheres();

  {
    // No ASAN error observed:
    auto index = bgi::rtree<demo::Sphere, bgi::linear<16, 4>>(spheres);
  }

  {
    // Generates an ASAN error 'use-after-scope'.
    auto index = bgi::rtree<demo::Sphere, bgi::linear<16, 4>>();
    index.insert(spheres.begin(), spheres.end());
  }

  return 0;
}
