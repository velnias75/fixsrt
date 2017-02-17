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

#include <cstdlib>
#include <iostream>

using namespace FixSRT;

int main ( int, char ** ) {

    Fixer p ( std::cin );
    uint64_t nr = 1u;

    for ( Fixer::ENTRIES::const_iterator i ( p.items().begin() ); i != p.items().end(); ++i ) {

        std::cout << nr++ << std::endl;
        std::cout << p.tcode ( *i ) << std::endl;

        for ( Fixer::LINES::const_iterator j ( ( *i ).txt.begin() ); j != ( *i ).txt.end(); ++j ) {
            std::cout << *j << std::endl;
        }

        std::cout << std::endl;
    }

    return EXIT_SUCCESS;
}

// kate: indent-mode cstyle; indent-width 4; replace-tabs on; ;
