/* Copyright 2017 R. Thomas
 * Copyright 2017 Quarkslab
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#include "pyPE.hpp"

#include "LIEF/visitors/Hash.hpp"
#include "LIEF/PE/RichEntry.hpp"

#include <string>
#include <sstream>

template<class T>
using getter_t = T (RichEntry::*)(void) const;

template<class T>
using setter_t = void (RichEntry::*)(T);

void init_PE_RichEntry_class(py::module& m) {
  py::class_<RichEntry>(m, "RichEntry")
    .def(py::init<>())
    .def(py::init<uint16_t, uint16_t, uint32_t>())

    .def_property("id",
        static_cast<getter_t<uint16_t>>(&RichEntry::id),
        static_cast<setter_t<uint16_t>>(&RichEntry::id),
        "Type of the entry")

    .def_property("build_id",
        static_cast<getter_t<uint16_t>>(&RichEntry::build_id),
        static_cast<setter_t<uint16_t>>(&RichEntry::build_id),
        "Builder number of the tool (if any)")

    .def_property("count",
        static_cast<getter_t<uint32_t>>(&RichEntry::count),
        static_cast<setter_t<uint32_t>>(&RichEntry::count),
        "*Occurrence* count")

    .def("__eq__", &RichEntry::operator==)
    .def("__ne__", &RichEntry::operator!=)
    .def("__hash__",
        [] (const RichEntry& entry) {
          return LIEF::Hash::hash(entry);
        })

    .def("__str__", [] (const RichEntry& entry)
        {
          std::ostringstream stream;
          stream << entry;
          std::string str = stream.str();
          return str;
        });



}