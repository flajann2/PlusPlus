#pragma once 
//
//  bufferlike.h
//  cwrap
//
//  Created by Lisa Lippincott on 9/5/14.
//  Released into the public domain by Lisa Lippincott, 2014.
//

#ifndef PLUSPLUS_STDISH_BUFFERLIKE_H
#define PLUSPLUS_STDISH_BUFFERLIKE_H

#include "arraylike.h"
#include "charlike.h"

#include <type_traits>

/*
    is_bufferlike       detects types that can be treated as an array of characters for bytewise I/O.
    bufferlike_data     provides a uniform interface to the start of the buffer.
    bufferlike_size     provides a uniform interface to the size of the buffer.
*/
    
namespace cwrap
   {
    namespace stdish
       {
        template < class T >
        using is_bufferlike
            = std::integral_constant< bool, cwrap::stdish::is_arraylike<T>::value 
                                            && cwrap::stdish::is_charlike< cwrap::stdish::arraylike_element<T> >::value >;
        
        
        
        template < class B >
        auto bufferlike_data( B& b )
        -> typename std::enable_if< is_bufferlike<B>::value, char * >::type
           {
            using cwrap::stdish::charlike_cast;
            using cwrap::stdish::arraylike_data;
            
            return charlike_cast< char * >( arraylike_data( b ) );
           }

        template < class B >
        auto bufferlike_data( const B& b )
        -> typename std::enable_if< is_bufferlike<B>::value, const char * >::type
           {
            using cwrap::stdish::charlike_cast;
            using cwrap::stdish::arraylike_data;
            
            return charlike_cast< const char * >( arraylike_data( b ) );
           }


        
        template < class B >
        auto bufferlike_size( const B& b )
        -> typename std::enable_if< is_bufferlike<B>::value, std::size_t >::type
           {
            using cwrap::stdish::charlike_cast;
            using cwrap::stdish::arraylike_data;
            
            return arraylike_size( b ) * sizeof( arraylike_element<B> );
           }
       }
   }

#endif
