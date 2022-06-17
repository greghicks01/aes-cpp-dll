
/*
 -------------------------------------------------------------------------
 Copyright (c) 2001, Dr Brian Gladman <brg@gladman.uk.net>, Worcester, UK.
 All rights reserved.

 TERMS

 Redistribution and use in source and binary forms, with or without 
 modification, are permitted subject to the following conditions:

  1. Redistributions of source code must retain the above copyright 
     notice, this list of conditions and the following disclaimer. 

  2. Redistributions in binary form must reproduce the above copyright
     notice, this list of conditions and the following disclaimer in the 
     documentation and/or other materials provided with the distribution. 

  3. The copyright holder's name must not be used to endorse or promote 
     any products derived from this software without his specific prior 
     written permission. 

 This software is provided 'as is' with no express or implied warranties 
 of correctness or fitness for purpose.
 -------------------------------------------------------------------------
 Issue Date: 21/01/2002

 This file contains the definitions required to use AES (Rijndael) in C++.
*/

#ifndef _AESCPP_H
#define _AESCPP_H

#include <vcl.h>
#include "aes.h"

class AESclass : public TComponent
{
typedef TComponent inherited ;
private:
   aes_ctx cx[1];
public:
#if defined(BLOCK_SIZE)
    AESclass():inherited(NULL) { cx->n_blk = BLOCK_SIZE; cx->n_rnd = 0; }
#else
    AESclass(unsigned int blen = 16):inherited(NULL)
    { cx->n_blk = blen; cx->n_rnd = 0; }

    aes_rval blk_len(unsigned int blen) { return aes_blk_len(blen, cx); }
#endif

    aes_rval enc_key( AnsiString key )
            //const unsigned char in_key[], unsigned int klen)
            {
                unsigned char * in_key ;
                unsigned int klen  = A2C( key , in_key ) ;
                aes_32t x = aes_enc_key(in_key, klen, cx);
                return x ; 
            }

    aes_rval dec_key ( AnsiString key )
            //const unsigned char in_key[], unsigned int klen)
            { 
                unsigned char * in_key ;
                unsigned int klen  = A2C( key , in_key ) ;
                aes_32t x = aes_dec_key(in_key, klen, cx);
                delete [] in_key ;
                return x ;
            }

    aes_rval enc_blk( AnsiString & blk )
            //const unsigned char in_blk[], unsigned char out_blk[])
            { 
                unsigned char * Cblk ;
                unsigned int klen  = A2C( blk , Cblk ) ;
                blk_len( klen ) ;
                aes_32t x = aes_enc_blk( Cblk, Cblk, cx);
                blk = C2A ( Cblk , klen ) ;
                delete [] Cblk ;
                return x ;
            }

    aes_rval dec_blk( AnsiString & blk )
            //const unsigned char in_blk[], unsigned char out_blk[])
            { 
                unsigned char * Cblk = NULL;
                unsigned int klen  = A2C( blk , Cblk ) ;
                blk_len( klen ) ;
                aes_32t x = aes_dec_blk( Cblk, Cblk, cx);
                return x ;
            }

    unsigned int __fastcall A2C( AnsiString a , unsigned char * c )
    {
            //TODO: Add your source code here
            unsigned int sz = a.Length() ;
            if ( ! sz % 2 )
                a += '0' , sz = a.Length() ;
            sz /= 2 ; // halfsize when converted
            //reverse ( a ) ;
            UpperCase ( a ) ;

            AnsiString hex = "0123456789ABCDEF" ;

            if ( c != NULL )
                delete c ;
            c = new unsigned char [ sz ] ;

            for ( int idx = 0 ; idx < sz ; idx ++ )
            {
                char up  = a [ idx * 2 + 1 ] ;
                char low = a [ idx * 2 + 2 ] ;
                c [ idx ] = ( ( hex.Pos( up )-1 ) << 4 ) + hex.Pos( low ) ;
            }
            return sz ;
    }

    AnsiString __fastcall C2A( char * c , unsigned int len )
    {
            //TODO: Add your source code here; 

            AnsiString hex = "0123456789ABCDEF" ;
            AnsiString v = "" ;
            for ( int idx = 0 ; idx < len ; idx ++ )
            {                
                v += hex [ ( ( c [ idx ] >> 4 ) & 0x0F + 1 ) ] ;
                v += hex [ ( c [ idx ] & 0x0F + 1 ) ] ;
            }
            return v ;
    }

    void __fastcall reverse(AnsiString & v)
    {
        int start = 1 , stop = v.Length() ;
        while ( start < stop )
        {
                char t      = v [ start ] ;
                v [ start ] = v [ stop  ] ;
                v [ stop  ] = t           ;
        };
    }
};

#endif

