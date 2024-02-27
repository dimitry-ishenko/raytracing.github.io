#ifndef BVH_HPP
#define BVH_HPP

#include "object.hpp"
#include "random.hpp"

#include <algorithm>
#include <iterator>
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
    template<typename Iter>
    bvh_node(Iter begin, Iter end)
    {
        static rnd_gen rnd{0, 3};
        auto less = [ax = rnd()](auto&& l, auto&& r) { return l->bbox[ax].min < r->bbox[ax].min; };

        switch (auto size = std::distance(begin, end))
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

            auto mid = begin + size / 2;
            child_0.reset(new bvh_node{ begin, mid });
            child_1.reset(new bvh_node{ mid,   end });
        }

        bbox = merge(child_0->bbox, child_1->bbox);
    }

    std::shared_ptr<object> child_0, child_1;
};

#endif
