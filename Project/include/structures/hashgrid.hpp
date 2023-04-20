#pragma once

#include <algorithm>
#include <cmath>
#include <vector>
#include <iterator>
#include <unordered_set>
#include <deque>

#include "math.hpp"

namespace structures {
    template<typename T>
    class HashGrid final {
    private:
        using cell_type = std::vector<std::pair<math::vec3, T>>;

        template<class GridT>
        requires std::same_as<std::remove_const_t<GridT>, HashGrid>
        struct cell_gen_ref final {
            std::reference_wrapper<GridT> grid;
            math::ivec3 idx;

            // Returns `false` if the sphere with `center` and `radius` definetly does not intersect with this cell.
            [[nodiscard]] auto may_intersect_sphere(math::vec3 center, math::f32 radius) const noexcept -> bool {
                // For a simpler implementation we get the sphere that completely encompasses the cell rectangle. Then
                // we just check if that sphere has any intersection with the `position` and `radius` sphere. If there
                // is, we check every element in that cell.
                const auto max_dim = std::max(grid.get()._cellsize.x, std::max(grid.get()._cellsize.y, grid.get()._cellsize.z));
                const auto cell_radius = math::sqrt(2 * max_dim * max_dim);

                auto cell_center = math::vec3{
                    grid.get()._pos.x + idx.x * grid.get()._cellsize.x + grid.get()._cellsize.x / 2.0,
                    grid.get()._pos.y + idx.y * grid.get()._cellsize.y + grid.get()._cellsize.y / 2.0,
                    grid.get()._pos.z + idx.z * grid.get()._cellsize.z + grid.get()._cellsize.z / 2.0,
                };

                auto dist = math::distance(center, cell_center);
                return dist <= radius + cell_radius;
            }

            [[nodiscard]] auto cell_idx() const noexcept -> size_t {
                return idx.x + idx.y * grid.get()._ncells.x + idx.z * grid.get()._ncells.x * grid.get()._ncells.y;
            }

            auto insert(math::vec3 position, T element) -> void
            requires (!std::is_const_v<GridT>)
            {
                grid.get()._cells[cell_idx()].push_back(std::make_pair(position, element));
            }

            template<std::output_iterator<std::pair<math::vec3, const T&>> It>
            auto copy_if_inside(math::vec3 position, math::f32 radius, It out) const -> void {
                // TODO: Can this be a `copy_if`. Seems like it should be something like `transform_if`, but that's not in the stdlib.
                auto const& cell = grid.get()._cells[cell_idx()];
                for (auto const& el : cell) {
                    auto dist = math::distance(el.first, position);
                    if (dist <= radius) {
                        math::vec3 pos = el.first;
                        *out++ = std::pair<math::vec3, const T&>(pos, el.second);
                    }
                }
            }
        };

        using cell_ref = cell_gen_ref<HashGrid<T>>;
        using cell_cref = cell_gen_ref<HashGrid<T> const>;

    public:
        HashGrid(math::vec3 pos, math::vec3 size, math::vec3 cellsize)
            : _pos(pos)
            , _size(size)
            , _cellsize(cellsize)
            , _ncells(std::ceil(_size.x / _cellsize.x),
                      std::ceil(_size.y / _cellsize.y),
                      std::ceil(_size.z / _cellsize.z))
            , _cells(_ncells.x * _ncells.y * _ncells.z)
        {}

        // TODO(calango): Should this be `[[nodiscard]]`?
        auto insert(math::vec3 position, T element) -> bool {
            auto idx = point_to_idx(position);
            if (!in_bounds(idx)) return false;
            cell_from_idx(idx).insert(position, std::move(element));
            return true;
        }

        template<std::output_iterator<std::pair<math::vec3, const T&>> It>
        auto query(math::vec3 position, math::f32 radius, It out) const -> void {
            auto vis = std::unordered_set<size_t>();
            auto queue = std::deque<math::ivec3>();
            queue.push_back(point_to_idx(position));
            while (!queue.empty()) {
                auto idx = queue.front();
                queue.pop_front();
                if (!in_bounds(idx)) continue;
                auto cell = cell_from_idx(idx);
                auto i = cell.cell_idx();
                if (!cell.may_intersect_sphere(position, radius) || vis.contains(i)) continue;
                vis.insert(i);
                cell.copy_if_inside(position, radius, out);

                queue.push_back({idx.x - 1, idx.y    , idx.z    });
                queue.push_back({idx.x + 1, idx.y    , idx.z    });
                queue.push_back({idx.x    , idx.y - 1, idx.z    });
                queue.push_back({idx.x    , idx.y + 1, idx.z    });
                queue.push_back({idx.x    , idx.y    , idx.z - 1});
                queue.push_back({idx.x    , idx.y    , idx.z + 1});
            }
        }

    private:
        math::vec3 _pos;
        math::vec3 _size;
        math::vec3 _cellsize;
        math::ivec3 _ncells;
        std::vector<cell_type> _cells;

        [[nodiscard]] auto point_to_idx(math::vec3 point) const noexcept -> math::ivec3 {
            return math::ivec3{
                std::floor((point.x - _pos.x) / _cellsize.x),
                std::floor((point.y - _pos.y) / _cellsize.y),
                std::floor((point.z - _pos.z) / _cellsize.z),
            };
        }

        [[nodiscard]] auto cell_from_idx(math::ivec3 idx) noexcept -> cell_ref {
            return cell_ref { .grid = std::ref(*this), .idx = idx };
        }

        [[nodiscard]] auto cell_from_idx(math::ivec3 idx) const noexcept -> cell_cref {
            return cell_cref { .grid = std::cref(*this), .idx = idx };
        }

        [[nodiscard]] auto in_bounds(math::ivec3 idx) const noexcept -> bool {
            return idx.x > 0 && idx.x < _ncells.x
                && idx.y > 0 && idx.y < _ncells.y
                && idx.z > 0 && idx.z < _ncells.z;
        }
    };
}
