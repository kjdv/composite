#pragma once

#include "composite.hh"
#include "make.hh"

namespace composite {
namespace {

// sample composite, using pretty much all features
const composite sample = make_map(
            "scalars", make_seq(
                none{},
                true,
                false,
                1,
                3.14,
                "foo"),
            "sequences", make_map(
                "1d", make_seq(1, 2, 3),
                "2d", make_seq(
                    make_seq(1, 2),
                    make_seq(3, 4),
                    make_seq(5, 6)),
                "map", make_seq(
                    make_map("foo", "bar"),
                    make_map("bar", "foo"))),
            "mappings", make_map(
                "1d", make_map("foo", "bar"),
                "2d", make_map(
                        "a", make_map("pi", 3.14),
                        "b", make_map("e", 2.72)),
                "seq", make_map("spacedogs", make_seq(
                                    "Laika",
                                    "Belka",
                                    "Strelka"))));

}
}
