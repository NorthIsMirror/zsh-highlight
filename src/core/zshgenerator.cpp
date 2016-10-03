/***************************************************************************
                      zshgenerator.cpp  -  description
                             -------------------
    begin                : Jul 5 2004
    copyright            : (C) 2004-2007 by Andre Simon
                           (C) 2016 Sebastian Gniazdowski (modifications)
    email                : andre.simon1@gmx.de
 ***************************************************************************/


/*
This file is part of Highlight.

Highlight is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Highlight is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with Highlight.  If not, see <http://www.gnu.org/licenses/>.
*/


#include <sstream>

#include "ZshGenerator.h"

namespace highlight
{

string  ZshGenerator::getOpenTag ( const string&font,
                                    const string&fgCol, const string&bgCol )
{
    ostringstream s;
    s  << "\033["<<font;
    if ( !fgCol.empty() )
        s<<";"<<fgCol;
    if ( !bgCol.empty() )
        s<<";"<<bgCol;
    s << "m";
    return  s.str();
}


ZshGenerator::ZshGenerator() : CodeGenerator ( ZSH )
{

    newLineTag = "\n";
    spacer = " ";
}

ZshGenerator::~ZshGenerator() {}

void ZshGenerator::initOutputTags()
{
    openTags.push_back ( "" );
    openTags.push_back ( getOpenTag ( "00", "31" ) ); //str
    openTags.push_back ( getOpenTag ( "00", "34" ) );//number
    openTags.push_back ( getOpenTag ( "00", "34" ) );//sl comment
    openTags.push_back ( getOpenTag ( "00", "34" ) );//ml comment
    openTags.push_back ( getOpenTag ( "00", "35" ) );//escapeChar
    openTags.push_back ( getOpenTag ( "00", "35" ) );//directive
    openTags.push_back ( getOpenTag ( "00", "31" ) );//directive string
    openTags.push_back ( getOpenTag ( "00", "30" ) );//linenum
    openTags.push_back ( getOpenTag ( "00", "00" ) );//symbol
    openTags.push_back ( getOpenTag ( "00", "35" ) );//interpolation

    closeTags.push_back ( "" );
    for (unsigned int i=1; i<NUMBER_BUILTIN_STATES; i++ ) {
        closeTags.push_back ( "\033[m" );
    }
}

string ZshGenerator::getHeader()
{
    return string();
}

void ZshGenerator::printBody()
{
    processRootState();
}

string ZshGenerator::getFooter()
{
    return string();
}

string ZshGenerator::maskCharacter ( unsigned char c )
{
    return string ( 1, c );
}

void ZshGenerator::maskString ( ostream& ss, const string & s )
{
    for ( unsigned int i=0; i< s.length(); i++ ) {
        ss << maskCharacter ( s[i] );
    }
}

string ZshGenerator::getKeywordOpenTag ( unsigned int styleID )
{
    return ( styleID ) ?getOpenTag ( "00", "32", "" ) :getOpenTag ( "00", "33" );
}

string ZshGenerator::getKeywordCloseTag ( unsigned int styleID )
{
    return "\033[m";
}

}
