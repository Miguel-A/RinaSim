// The MIT License (MIT)
//
// Copyright (c) 2014-2016 Brno University of Technology, PRISTINE project
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.

/*
 * Utils.h
 *
 *  Created on: Mar 5, 2015
 *      Author: gaixas1
 */

#ifndef UTILS_H_
#define UTILS_H_

#include <string>
#include <sstream>
#include <vector>

#include "omnetpp.h"

/*
 * Explode a string into a vector of strings, given a delimiter
 *
 */
std::vector<std::string> &split(const std::string &s, char delim, std::vector<std::string> &elems);
std::vector<std::string> split(const std::string &s, char delim);

/*
 * Implode the first n values of a vector of string into a strings, separated by a delimiter
 *
 */
std::string join(const std::vector<std::string> &elems, const unsigned int n, const char delim);


/*
 * Check if the first value is a prefix of the second
 *
 */
bool isPrefix(std::string prefix, std::string s);

/**
 * Display the selected policy next to given policy module.
 *
 * @param mod target instance
 */
inline void setPolicyDisplayString(cModule* mod, const char* str = nullptr)
{
    if (ev.isGUI())
    {
        cDisplayString& disp = mod->getDisplayString();
        disp.setTagArg("t", 1, "t");
        disp.setTagArg("t", 0, (str == nullptr ? mod->getClassName() : str));
        disp.setTagArg("b", 0, "45");
        disp.setTagArg("b", 1, "45");
        disp.setTagArg("b", 2, "rect");
        disp.setTagArg("b", 3, "grey");
        disp.setTagArg("b", 4, "cyan");
        disp.setTagArg("b", 5, "1");
    }
}

/**
 * A getModuleByPath wrapper accepting individual modules in the path as variables.
 * e.g. TMod* newMod = (TMod*)parentMod->getModuleByPath("^.^.a.b")
 *      ==
 *      getRINAModule<TMod*>(parentMod, 2, {"a", "b"})
 *
 * @tparam target module type
 * @param curMod starting module
 * @param parentLevel initial getParentModule() invocation count
 * @param modPath path of modules to descent into
 * @return pointer to the retrieved module
 */
template<typename modType>
modType getRINAModule(cModule* curMod, int parentLevel, std::initializer_list<const char*> modPath)
{
    std::ostringstream modulePath;
    while (parentLevel--) { modulePath << ".^"; }
    for (auto elem : modPath) { modulePath << "." << elem; }
    return check_and_cast<modType>(curMod->getModuleByPath(modulePath.str().c_str()));
}


#endif /* UTILS_H_ */
