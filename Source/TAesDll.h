/*
 -------------------------------------------------------------------------
 Copyright (c) 2001, Dr Brian Gladman <                 >, Worcester, UK.
 All rights reserved.

 LICENSE TERMS

 The free distribution and use of this software in both source and binary
 form is allowed (with or without changes) provided that:

   1. distributions of this source code include the above copyright
      notice, this list of conditions and the following disclaimer;

   2. distributions in binary form include the above copyright
      notice, this list of conditions and the following disclaimer
      in the documentation and/or other associated materials;

   3. the copyright holder's name is not used to endorse products
      built using this software without specific written permission. 

 DISCLAIMER                        9

 This software is provided 'as is' with no explicit or implied warranties
 in respect of its properties, including, but not limited to, correctness
 and fitness for purpose.
 -------------------------------------------------------------------------
 Issue Date: 29/07/2002

 This file contains the definitions required to use AES (Rijndael) in C.
*/
//---------------------------------------------------------------------------

#ifndef TAesDllH
#define TAesDllH

/*  This include is used only to find 8 and 32 bit unsigned integer types   */

#include <vcl.h>
#include <limits.h>

#define BLOCK_SIZE 16

union u
{
        unsigned   int   ui [ 2 ] ;
        struct 
        {
/*   Range  |Off |Max |Bits */
/* ======================== */
/*    1-31  |    | 1F |  5  */ unsigned int d  :  5 ;
/*    1-12  |    |  F |  4  */ unsigned int m  :  4 ;
/* 2000-2254|2000| FF |  8  */ unsigned int y  :  8 ;
/*    0-23  |    | 1F |  5  */ unsigned int h  :  5 ;
/*    0-59  |    | 3F |  6  */ unsigned int mn :  6 ;
/*    0-59  |    | 3F |  6  */ unsigned int s  :  6 ;
/*    0-999 |    | 3FF| 10  */ unsigned int ms : 10 ;
/*          |    |FFFF| 16  */ unsigned int ls : 16 ;
/* ======================== */
        } ;
} pdu ;


#if !defined(BLOCK_SIZE)
#define KS_LENGTH   128
#else
#define KS_LENGTH   4 * BLOCK_SIZE
#endif

typedef unsigned int aes_32t ;

typedef struct aes                 /* the AES context for encryption   */
{   aes_32t    k_sch[KS_LENGTH];   /* the encryption key schedule      */
    aes_32t    n_rnd;              /* the number of cipher rounds      */
    aes_32t    n_blk;              /* the number of bytes in the state */
} aes_ctx;

class TAESDll : public TComponent
{

typedef TComponent Inherited ;
typedef unsigned int aes_fret;       /* type for function return value  */
#define aes_rval     aes_fret
private:
        HANDLE FhDll ;
        aes_ctx cx ;
        TTimer * LoadDelay ;
        void __fastcall OnLoadDelay(TObject * Sender);
        static const AnsiString FEncB , FDecB , FDkey , FEkey , FLen , FDllName ;

        typedef aes_rval ( _stdcall * Taes_blk_len)
                         ( unsigned int blen , aes_ctx cx[1] ) ;
        typedef aes_rval ( _stdcall * Taes_enc_key)
                         ( const unsigned char in_key[], unsigned int klen, aes_ctx cx[1]);
        typedef aes_rval ( _stdcall * Taes_enc_blk )
                         ( const unsigned char in_blk[], unsigned char out_blk[], const aes_ctx cx[1]);
        typedef aes_rval ( _stdcall * Taes_dec_key )
                         ( const unsigned char in_key[], unsigned int klen, aes_ctx cx[1]);
        typedef aes_rval ( _stdcall * Taes_dec_blk )
                         ( const unsigned char in_blk[], unsigned char out_blk[], const aes_ctx cx[1]);

        Taes_blk_len aes_blk_len ;
        Taes_enc_key aes_enc_key ;
        Taes_enc_blk aes_enc_blk ;
        Taes_dec_key aes_dec_key ;
        Taes_dec_blk aes_dec_blk ;
        
        // convert string to BYTE array
        void __fastcall loadArray ( unsigned char *& , int & , AnsiString );
        AnsiString __fastcall unloadArray ( unsigned char * , int ) ;

        void __fastcall blk_len(int);
        int __fastcall HexToInt(AnsiString);

public:
        __fastcall TAESDll(TComponent * Owner);
        virtual __fastcall ~TAESDll();
        
        void __fastcall deckey ( AnsiString ) ;
        void __fastcall enckey ( AnsiString ) ;
        AnsiString __fastcall decblk ( AnsiString ) ;
        AnsiString __fastcall encblk ( AnsiString ) ;

};
//---------------------------------------------------------------------------
#endif
/*


#ifndef _AES_H
#define _AES_H



/*  BLOCK_SIZE is in BYTES: 16, 24, 32 or undefined for aes.c and 16, 20,
    24, 28, 32 or undefined for aespp.c.  When left undefined a slower
    version that provides variable block length is compiled.
*/

//#define BLOCK_SIZE  16
// #define AES_DLL

/* key schedule length (in 32-bit words)    */

