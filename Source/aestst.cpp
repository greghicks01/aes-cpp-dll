//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "aestst.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TAEStestBed *AEStestBed;
//---------------------------------------------------------------------------
__fastcall TAEStestBed::TAEStestBed(TComponent* Owner)
        : TForm(Owner)
{
        AES = new TAESDll ( NULL ) ;        
} 

__fastcall TAEStestBed::~TAEStestBed()
{
        //TODO: Add your source code here
        delete AES ;
}
//---------------------------------------------------------------------------

void __fastcall TAEStestBed::LibFail(TObject * Sender)
{
        //TODO: Add your source code here
        LibProb->Brush->Color = clRed ;
}
void __fastcall TAEStestBed::EdtChange(TObject *Sender)
{
        TEdit  * Edit  = static_cast < TEdit * > ( Sender ) ;
        AnsiString editName = Edit->Name ;

        TLabel * Label = static_cast < TLabel * >
                                        ( FindComponent (
                                                editName.SubString( 1 , 3 ) + "Len"
                                        ) ) ;

        if ( IntToStr ( Edit->Text.Length ( ) ) % 2)
                Label->Font->Color = clRed ;
        else
                Label->Font->Color = clBlack ;

        Label->Caption = IntToStr ( Edit->Text.Length ( ) / 2 ) ;

}
//---------------------------------------------------------------------------

void __fastcall TAEStestBed::RunAESClick(TObject *Sender)
{
        // set key from KeyEdt
        AES->enckey(KeyEdt->Text) ;
        // enc block  from DatEdt
        EncEdt->Text = AES->encblk(DatEdt->Text) ;
        // get enc block to EncEdt 
        AES->deckey(KeyEdt->Text) ;
        // dec enc block to DecEdt
        DecEdt->Text = AES->decblk(EncEdt->Text) ;
}
//---------------------------------------------------------------------------

void __fastcall TAEStestBed::Timer1Timer(TObject *Sender)
{
        Timer1->Enabled = false ;
        EdtChange( KeyEdt ) ;
        EdtChange( DatEdt ) ;
}
//---------------------------------------------------------------------------

void __fastcall TAEStestBed::Button1Click(TObject *Sender)
{
        reg = new TRegistry ;
        reg->RootKey = HKEY_LOCAL_MACHINE ;

        TStringList * Knames = new TStringList ;

        AnsiString x =  "\\SOFTWARE\\SDA\\serialdriver\\Version\\1.00" ;

        reg->OpenKey( x , false);
        reg->GetKeyNames( Knames ) ;

        TStringList * Vnames = new TStringList [ Knames->Count ];
        // for each Knames - get Vnames
        for ( int i = 0 ; i < Knames->Count ; i ++ )
        {
                reg->OpenKey( Knames->Strings [i] , false ) ;
                reg->GetValueNames( &( Vnames[i] ) ) ;
                reg->OpenKey(x , false);
        }

        delete reg , Knames ;
        delete [] Vnames  ;
}
//---------------------------------------------------------------------------

