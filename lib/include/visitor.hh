#pragma once

#include "composite.hh"

namespace composite {

// visitor, more elaborate than composite::visit(), recursive
class visitor
{
public:
    virtual ~visitor() = default;

    virtual void visit(void_t)   = 0;
    virtual void visit(bool_t)   = 0;
    virtual void visit(int_t)    = 0;
    virtual void visit(uint_t) = 0;
    virtual void visit(float_t) = 0;
    virtual void visit(std::string_view)     = 0;

    virtual void index(std::size_t);    // called before visiting a sequence element
    virtual void key(std::string_view); // called before visiting a mapping element
    virtual void start_sequence();      // indicate the start of a sequence
    virtual void start_mapping();       // indicate the start of a mapping
    virtual void end_sequence();        // indicate the end of a sequence
    virtual void end_mapping();         // indicate the end of a mapping

    [[deprecated("please use end_sequence or end_mapping")]] virtual void sentinel();            // indicate the end of a sequence or mapping
};

void apply(const composite& c, visitor& v);

} // namespace composite
