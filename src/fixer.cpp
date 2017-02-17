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

#include "fixer.h"

#include <algorithm>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <cmath>

using namespace FixSRT;

Fixer::Fixer ( std::istream& in ) : m_items() {

    std::string nr;
    unsigned int p = 0u;
    ENTRY e;

    while ( !in.eof() ) {

        std::string line;
        std::getline ( in, line );

        if ( !line.empty() && p == 0u ) {
            nr = line;
        } else if ( !line.empty() && p == 1u ) {
            parseTime ( line, e );
        } else if ( !line.empty() && p >= 2u ) {
            e.txt.push_back ( line );
        } else if ( line.empty() ) {

            if ( ! ( e.start == e.end || e.txt.empty() ) ) {

                if ( m_items.empty() ||
                        !std::equal ( m_items.back().txt.begin(), m_items.back().txt.end(),
                                      e.txt.begin() ) ) {
                    m_items.push_back ( e );
                } else {

                    std::cerr << "Fixed timecode #" << nr << " from \""
                              << tcode ( m_items.back() ) << "\" to \"" << tcode ( e ) << "\""
                              << std::endl;

                    m_items.back().start = e.start;
                    m_items.back().end   = e.end;
                }

            } else {
                std::cerr << "Discarded subtitle #" << nr << std::endl;
            }

            e.txt.clear();
        }

        p = line.empty() ? 0u : p+1u;
    }
}

std::string Fixer::len2tc ( uint64_t len ) {

    std::ostringstream os;
    double x;

    const double   fl = ( double ) len/1000.0;
    const uint64_t um = fl/60u;
    const uint64_t uh = um/60u;

    os << std::setfill ( '0' ) << std::setw ( 2 ) << uh
       << ":" << std::setfill ( '0' ) << std::setw ( 2 ) << ( um % 60u )
       << ":" << std::setfill ( '0' ) << std::setw ( 2 ) << ( ( ( uint64_t ) fl ) % 60u )
       << "," << std::setfill ( '0' ) << std::setw ( 3 )
       << ( uint64_t ) round ( ( std::modf ( fl, &x ) * 1000.0 ) );

    return os.str();
}

std::string Fixer::tcode ( const ENTRY &e ) {
    return len2tc ( e.start ).append ( " --> " ).append ( len2tc ( e.end ) );
}

uint64_t Fixer::parseTimeStamp ( const std::string &ts ) const {

    std::istringstream sh ( ts.substr ( 0, 2 ) );
    std::istringstream sm ( ts.substr ( 3, 2 ) );
    std::istringstream ss ( ts.substr ( 6, 2 ) );
    std::istringstream sss ( ts.substr ( 9 ) );

    uint64_t h, m, s, sub;

    sh >> h;
    sm >> m;
    ss >> s;
    sss >> sub;

    return ( h * 3600000u ) + ( m * 60000u ) + ( s * 1000u ) + sub;
}

void Fixer::parseTime ( const std::string& line, Fixer::ENTRY& e ) const {

    const std::string::size_type arrow ( line.find ( " --> " ) );

    e.start = parseTimeStamp ( line.substr ( 0, arrow ) );
    e.end = parseTimeStamp ( line.substr ( arrow + 5u ) );
}

const Fixer::ENTRIES& Fixer::items() const {
    return m_items;
}

// kate: indent-mode cstyle; indent-width 4; replace-tabs on; 
