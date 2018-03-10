#pragma once
//
//  Thrown.h
//  cwrap
//
//  Created by Lisa Lippincott on 8/16/14.
//  Released into the public domain by Lisa Lippincott, 2014.
//


#include <tuple>

/*
    The items in this file are used to modify the basic parameter and result groups 
    to be thrown when failure is detected.  (Failure detection is handled by Checked.) For example:
    
        NotPassed( p ) + Thrown()   in addition to any other bases, the exception will be derived from p
*/

namespace cwrap
   {
    template < bool thrown > struct ThrowSelector;
    
    template <>
    struct ThrowSelector< true >
       {
        template < class... P >
        std::tuple<P...> operator()( std::tuple<P...> toThrow ) const       { return toThrow; }
       };
    
    template <>
    struct ThrowSelector< false >
       {
        template < class... P >
        std::tuple<> operator()( std::tuple<P...> ) const                   { return std::tuple<>(); }
       };
    
    inline ThrowSelector<true>  Thrown()        { return ThrowSelector<true>(); }
    inline ThrowSelector<false> NotThrown()     { return ThrowSelector<false>(); }
   }

