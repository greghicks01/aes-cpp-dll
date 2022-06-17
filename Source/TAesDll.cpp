//---------------------------------------------------------------------------


#pragma hdrstop

#include "TAesDll.h"
#include <windows.h>

//---------------------------------------------------------------------------

#pragma package(smart_init)
const AnsiString TAESDll::FLen     = "_aes_blk_len@8"  ,
                 TAESDll::FEkey    = "_aes_enc_key@12" ,
                 TAESDll::FEncB    = "_aes_enc_blk@12" ,
                 TAESDll::FDkey    = "_aes_dec_key@12" ,
                 TAESDll::FDecB    = "_aes_dec_blk@12" ,
                 TAESDll::FDllName = "aes.dll"         ;

__fastcall TAESDll::TAESDll(TComponent * Owner): Inherited ( Owner )
{
        //TODO: Add your source code here
        LoadDelay = new TTimer ( NULL ) ;
        LoadDelay->Enabled = false ;
        LoadDelay->OnTimer = OnLoadDelay ;
        LoadDelay->Interval = 300 ;
        LoadDelay->Enabled = true ;
}

__fastcall TAESDll::~TAESDll()
{
        //TODO: Add your source code here
        LoadDelay->Enabled = false ;
        delete LoadDelay ;
        FreeLibrary ( FhDll ) ;
}

void __fastcall TAESDll::OnLoadDelay(TObject * Sender)
{
        //TODO: Add your source code here
        LoadDelay->Enabled = false ;

        FhDll = LoadLibrary ( FDllName . c_str ( ) ) ;

        if ( FhDll )
        {
                aes_blk_len = ( Taes_blk_len ) GetProcAddress ( FhDll , FLen  . c_str ( ) ) ;
                aes_enc_key = ( Taes_enc_key ) GetProcAddress ( FhDll , FEkey . c_str ( ) ) ;
                aes_enc_blk = ( Taes_enc_blk ) GetProcAddress ( FhDll , FEncB . c_str ( ) ) ;
                aes_dec_key = ( Taes_dec_key ) GetProcAddress ( FhDll , FDkey . c_str ( ) ) ;
                aes_dec_blk = ( Taes_dec_blk ) GetProcAddress ( FhDll , FDecB . c_str ( ) ) ;
        }
}

void __fastcall TAESDll::enckey( AnsiString key )
{
        //TODO: Add your source code here
        unsigned char * in_key = NULL ;
        int klen ;

        loadArray ( in_key , klen , key ) ;

        aes_enc_key(in_key, klen, &cx);

        delete [] in_key ;
}

void __fastcall TAESDll::deckey(AnsiString key )
{
        //TODO: Add your source code here 
        unsigned char * in_key = NULL ;
        int klen ;

        loadArray ( in_key , klen , key ) ;
        aes_dec_key(in_key, klen, &cx);
        
        delete [] in_key ;
}

AnsiString __fastcall TAESDll::encblk(AnsiString blk )
{
        //TODO: Add your source code here
        unsigned char * Cblk = NULL ;
        int klen ;

        loadArray ( Cblk , klen , blk ) ;
        cx.n_blk = klen ;
        aes_enc_blk( Cblk, Cblk, &cx);
        AnsiString t = unloadArray ( Cblk , klen ) ;

        delete [] Cblk ;
        return t ;
}

AnsiString __fastcall TAESDll::decblk(AnsiString blk)
{
        //TODO: Add your source code here
        unsigned char * Cblk = NULL; 
        int klen ;

        loadArray ( Cblk , klen , blk ) ;
        cx.n_blk = klen ;
        aes_dec_blk( Cblk, Cblk, &cx);
        AnsiString t = unloadArray ( Cblk , klen ) ;

        delete [] Cblk ;
        return t ;
}

                                             
void __fastcall TAESDll::loadArray ( unsigned char *& c , int & sz , AnsiString a )
{
        //TODO: Add your source code here
        
        if ( ! a.Length() % 2 )
                a += "0" ;

        sz = a.Length() / 2 ;

        UpperCase ( a ) ;

        if ( c )
                delete [] &c ;

        c = new unsigned char [ sz ] ;

        for ( int x = 0 ; x < sz ; x++  )
                c [ x ] = HexToInt ( a.SubString ( x * 2 + 1 , 2 ) ) ;
}

AnsiString __fastcall TAESDll::unloadArray(unsigned char * c , int len )
{
        //TODO: Add your source code here
        AnsiString v = "" ;
        for ( int idx = 0 ; idx < len ; idx ++ )
        {
            v += IntToHex ( c [ idx ] , 2 ) ; 
        }
        return v ;
}

void __fastcall TAESDll::blk_len(int len)
{
        //TODO: Add your source code here
        cx.n_blk = len ;
}


int __fastcall TAESDll::HexToInt ( AnsiString v )
{
        //TODO: Add your source code here 
        AnsiString hex = "0123456789ABCDEF" ;
        int start = 1 , stop = v.Length() , vInt = 0 ;

        while ( start < stop )
        {
                char t        = v [ start ] ;
                v [ start++ ] = v [ stop ] ;
                v [ stop--  ] = t ;
        }

        for ( int x = 0 ; x < v.Length() ; x++ )  
                vInt += ( hex.Pos( UpperCase ( v [ x + 1 ] ) ) - 1 ) << ( 4 * x ) ;

        return vInt ;
}
