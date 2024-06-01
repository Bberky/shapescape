/**
 * @file group.cpp
 * @author Adam Berkeš <berkeada@fit.cvut.cz>
 * @date 2023-05-08
 */

#include "group.hpp"
#include "../utils.hpp"

using namespace std;
using namespace utils;

Group::Group() = default;

Group::Group(const Coords &offset_, const ScaleFactor &scale_,
             const list<unique_ptr<Object>> &objects_)
    : offset(offset_), scale(scale_)
{
    for (const unique_ptr<Object> &obj : objects_)
        objects.push_back(obj->clone());
}

Group::Group(const Group &src)
{
    offset = src.offset;
    scale = src.scale;

    for (const unique_ptr<Object> &obj : src.objects)
        objects.push_back(obj->clone());
}

Group::~Group() = default;

unique_ptr<Object> Group::clone() const
{
    return make_unique<Group>(*this);
}

void Group::render(Image &image, const Coords &parent_offset,
                   const ScaleFactor &parent_scale) const
{
    for (const unique_ptr<Object> &obj : objects)
        obj->render(image, offset + parent_offset, scale * parent_scale);
}

Group &Group::add_object(const Object &obj)
{
    objects.push_back(obj.clone());

    return *this;
}

void Group::add_params(const string &params)
{
    const auto &[offset_str, scale_str] = split_str_once(params);

    if (!scale_str.empty())
        scale = ScaleFactor(extract_arg(scale_str, "scale"));

    offset = Vec2(offset_str);
}

Group &Group::operator=(Group src)
{
    std::swap(offset, src.offset);
    std::swap(scale, src.scale);
    std::swap(objects, src.objects);

    return *this;
}
