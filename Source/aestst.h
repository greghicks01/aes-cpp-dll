//---------------------------------------------------------------------------

#ifndef aeststH
#define aeststH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <registry.hpp>
#include "TAesDll.h"
//---------------------------------------------------------------------------
class TAEStestBed : public TForm
{
__published:	// IDE-managed Components
        TEdit *DatEdt;
        TEdit *KeyEdt;
        TEdit *EncEdt;
        TLabel *KeyLbl;
        TLabel *KeyLen;
        TLabel *DatLbl;
        TLabel *EncLbl;
        TLabel *DatLen;
        TLabel *EncLen;
        TButton *RunAES;
        TEdit *DecEdt;
        TLabel *DecLbl;
        TLabel *DecLen;
        TShape *LibProb;
        TTimer *Timer1;
        TButton *Button1;
        void __fastcall EdtChange(TObject *Sender);
        void __fastcall RunAESClick(TObject *Sender);
        void __fastcall Timer1Timer(TObject *Sender);
        void __fastcall Button1Click(TObject *Sender);
private:	// User declarations
        TRegistry * reg ;
        TAESDll * AES ;
        char     * blk ,
                 * key ;
        virtual __fastcall ~TAEStestBed();
public:		// User declarations
        __fastcall TAEStestBed(TComponent* Owner);
        void __fastcall LibFail(TObject * Sender);
};
//---------------------------------------------------------------------------
extern PACKAGE TAEStestBed *AEStestBed;
//---------------------------------------------------------------------------
#endif
