/**
 * @file group.hpp
 * @author Adam Berkeš <berkeada@fit.cvut.cz>
 * @date 2023-05-08
 */

#pragma once

#include "object.hpp"
#include "../vec2.hpp"

#include <list>

/**
 * @brief Group of objects given by it's offset from the origin, scale
 * of the objects it contains and finally object themselves, which can be
 * any class derived from Object
 */
class Group : public Object
{
    Coords offset;
    ScaleFactor scale = ScaleFactor(1, 1);
    std::list<std::unique_ptr<Object>> objects;

public:
    /** Construct a new Group object with default values */
    Group();

    /**
     * @brief Construct a new Group object with given values
     *
     * @param offset_ Offset from the origin (0,0)
     * @param scale_ Scale in either axis (e.g. (-1,2.5))
     * @param objects_ List of objects the group contains
     */
    Group(const Coords &offset_, const ScaleFactor &scale_,
          const std::list<std::unique_ptr<Object>> &objects_);

    /** Construct a new Group object by creating a deep-copy of src */
    Group(const Group &src);

    ~Group() override;

    /** Clone the Group along with all of its objects */
    std::unique_ptr<Object> clone() const override;

    /**
     * @brief Render all objects this group contains into the given
     * image
     *
     * @param image
     * @param parent_offset Offset of the parent group or (0,0) if this group
     * is a top-level object
     * @param parent_scale Scale of the parent group or (1,1) if this group
     * is a top-level object
     */
    void render(Image &image, const Coords &parent_offset,
                const ScaleFactor &parent_scale) const override;

    /**
     * @brief Add an object into the group
     *
     * @param obj Object to be added
     * @return Group&
     */
    Group &add_object(const Object &obj);

    /**
     * @brief Add parameters (Offset and Scale) parsed from a source string
     *
     * @throws std::invalid_argument If unknown parameter is in the source sttring
     * @param params Source string to be parsed into parameters
     */
    void add_params(const std::string &params);

    Group &operator=(Group src);
};
