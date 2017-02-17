/*
 * Copyright 2017 by Heiko Schäfer <heiko@rangun.de>
 *
 * This file is part of fixsrt.
 *
 * fixsrt is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as
 * published by the Free Software Foundation, either version 3 of
 * the License, or (at your option) any later version.
 *
 * fixsrt is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with fixsrt.  If not, see <http://www.gnu.org/licenses/>.
 */
 
#ifndef PARSER_H
#define PARSER_H
 
#include <stdint.h>
#include <iosfwd>
#include <string>
#include <vector>
 
namespace FixSRT {
 
class Fixer {
public:
    typedef std::vector<std::string> LINES;
 
    typedef struct _entry {
       
       inline _entry() : start(0u), end(0u), txt() {}
       
       uint64_t    start;
       uint64_t    end;
       LINES       txt;
    } ENTRY;
 
    typedef std::vector<ENTRY> ENTRIES;
    
    Fixer(std::istream &in);
    
    const ENTRIES &items() const;
    
    static std::string tcode(const ENTRY &e);
    
private:
    void parseTime(const std::string &line, ENTRY &e) const;
    uint64_t parseTimeStamp(const std::string &ts) const;
    static std::string len2tc(uint64_t len);
    
private:
    ENTRIES m_items;
};
 
}
 
#endif /* PARSER_H */
 
// kate: indent-mode cstyle; indent-width 1; replace-tabs on; ;
