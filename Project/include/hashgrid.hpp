#pragma once

#include <algorithm>
#include <cmath>
#include <vector>
#include <iterator>
#include <unordered_set>
#include <deque>

#include "math.hpp"

template<typename T>
class HashGrid final {
private:
    using cell_type = std::vector<std::pair<math::vec3, T>>;

public:
    HashGrid(math::vec3 size, math::vec3 cellsize)
        : _size(size)
        , _cellsize(cellsize)
        , _ncells(std::ceil(_size.x / _cellsize.x),
                  std::ceil(_size.y / _cellsize.y),
                  std::ceil(_size.z / _cellsize.z))
        , _points(_ncells.x * _ncells.y * _ncells.z)
    {}

    // TODO(calango): Should this be `[[nodiscard]]`?
    auto insert(math::vec3 position, T element) -> bool {
        auto idx = point_to_idx(position);
        if (!in_bounds(idx)) return false;
        cell_from_idx(idx).push_back(std::make_pair(position, std::move(element)));
        return true;
    }

    template<std::output_iterator<std::pair<math::vec3, const T&>> It>
    auto query(math::vec3 position, math::f32 radius, It out) const -> void {
        auto idx = point_to_idx(position);
        if (!in_bounds(idx)) return;
        auto vis = std::unordered_set<size_t>();
        auto queue = std::deque<math::ivec3>();
        queue.push_back(cell_idx(idx));
        while (!queue.empty()) {
            idx = queue.pop_front();
            if (vis.contains(idx)) continue;
            vis.insert(idx);
            auto const& cell = cell_from_idx(idx);
            add_points_from_cell(cell, position, radius, out);

            queue.push_back({idx.x, idx.y, idx.z});
        }
    }

private:
    math::vec3 _size;
    math::vec3 _cellsize;
    math::ivec3 _ncells;
    std::vector<cell_type> _points;

    [[nodiscard]] auto point_to_idx(math::vec3 point) const noexcept -> math::ivec3 {
        return math::ivec3{
            std::floor(point.x / _cellsize.x),
            std::floor(point.y / _cellsize.y),
            std::floor(point.z / _cellsize.z),
        };
    }

    [[nodiscard]] auto cell_from_idx(math::ivec3 idx) noexcept -> cell_type& {
        size_t i = idx.x + idx.y * _ncells.x + idx.z * _ncells.x * _ncells.y;
        return _points[i];
    }

    [[nodiscard]] auto cell_from_idx(math::ivec3 idx) const noexcept -> cell_type const& {
        return _points[cell_idx(idx)];
    }

    [[nodiscard]] auto cell_idx(math::ivec3 idx) const noexcept -> size_t {
        return idx.x + idx.y * _ncells.x + idx.z * _ncells.x * _ncells.y;
    }

    [[nodiscard]] auto in_bounds(math::ivec3 idx) const noexcept -> bool {
        return idx.x < _ncells.x
            && idx.y < _ncells.y
            && idx.z < _ncells.z;
    }

    template<std::output_iterator<std::pair<math::vec3, const T&>> It>
    auto add_points_from_cell(cell_type const& cell, math::vec3 position, math::f32 radius, It out) const -> void {
        for (auto const& el : cell) {
            auto dist = math::distance(el.first, position);
            if (dist <= radius) {
                math::vec3 pos = el.first;
                *out++ = std::pair<math::vec3, const T&>(pos, el.second);
            }
        }
    }
};
