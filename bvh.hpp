#ifndef BVH_HPP
#define BVH_HPP

#include "hit.hpp"
#include "interval.hpp"
#include "object.hpp"
#include "ray.hpp"

#include <algorithm>
#include <memory>

struct bvh_node : object
{
    explicit bvh_node(object_list world) :
        bvh_node{world.begin(), world.end()}
    { }

    virtual std::optional<hit> get_hit(const ray3& ray, interval ti) const
    {
        if (!bbox.is_hit(ray, ti)) return { };

        auto hit_0 = child_0->get_hit(ray, ti);
        if (hit_0) ti.max = hit_0->t;

        auto hit_1 = child_1->get_hit(ray, ti);
        return std::move(hit_1 ? hit_1 : hit_0);
    }

private:
    bvh_node(object_list::iterator begin, object_list::iterator end)
    {
        std::for_each(begin, end, [&](auto&& e) { bbox = merge(bbox, e->bbox); });

        auto ax = bbox.longest_axis();
        auto less = [&](auto&& l, auto&& r){ return l->bbox[ax].min < r->bbox[ax].min; };

        switch (auto size = end - begin)
        {
        case 1:
            child_0 = child_1 = *begin;
            break;

        case 2:
            child_0 = *(begin + 0);
            child_1 = *(begin + 1);
            if (less(child_1, child_0)) std::swap(child_1, child_0);
            break;

        default:
            std::sort(begin, end, less);

            child_0.reset(new bvh_node{ begin, begin + size / 2 });
            child_1.reset(new bvh_node{ begin + size / 2,   end });
        }
    }

    shared_object child_0, child_1;
};

#endif
