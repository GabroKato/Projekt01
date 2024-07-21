// Property of Bricsys NV. All rights reserved. 
// This file is part of the BRX SDK, and its use is subject to
// the terms of the BRX SDK license agreement.
/////////////////////////////////////////////////////////////////////////

#include "StdAfx.h"

class CBrxApp: public AcRxArxApp
{
public:
    CBrxApp(): AcRxArxApp() {}

    virtual void RegisterServerComponents()
    {
    }

    virtual AcRx::AppRetCode On_kInitAppMsg(void* pAppData)
    {
        AcRx::AppRetCode result = AcRxArxApp::On_kInitAppMsg(pAppData);

        acrxRegisterAppMDIAware(pAppData); // is able to work in MDI context
        acrxUnlockApplication(pAppData);   // allows to unload the module during session

        // Place your initialization code here
        acutPrintf(_T("\nWillkommen zur BricsCAD BRX plugin Entwicklung\n"));
        acutPrintf(_T("\nVerfügbare Befehle:\n"));
        acutPrintf(_T("\nMyLine\n"));

        return result;
    }

    virtual AcRx::AppRetCode On_kUnloadAppMsg(void* pAppData)
    {
        return AcRxArxApp::On_kUnloadAppMsg(pAppData);
    }

    virtual AcRx::AppRetCode On_kLoadDwgMsg(void* pAppData)
    {
        return AcRxArxApp::On_kLoadDwgMsg(pAppData);
    }

    virtual AcRx::AppRetCode On_kUnloadDwgMsg(void* pAppData)
    {
        return AcRxArxApp::On_kUnloadDwgMsg(pAppData);
    }

    virtual AcRx::AppRetCode On_kQuitMsg(void* pAppData)
    {
        return AcRxArxApp::On_kQuitMsg(pAppData);
    }

    static void BrxAppMyLine(void)
    {
        AcGePoint3d startPt(4.0, 2.0, 0.0);
        AcGePoint3d endPt(10.0, 7.0, 0.0);
        AcDbLine* pLine = new AcDbLine(startPt, endPt);
        AcDbBlockTable* pBlockTable;
        acdbHostApplicationServices()->workingDatabase()
            ->getSymbolTable(pBlockTable, AcDb::kForRead);
        AcDbBlockTableRecord* pBlockTableRecord;
        pBlockTable->getAt(ACDB_MODEL_SPACE, pBlockTableRecord,
            AcDb::kForWrite);
        pBlockTable->close();
        AcDbObjectId lineId;
        pBlockTableRecord->appendAcDbEntity(lineId, pLine);
        pBlockTableRecord->close();
        pLine->close();

    }


};

IMPLEMENT_ARX_ENTRYPOINT(CBrxApp)

ACED_ARXCOMMAND_ENTRY_AUTO(CBrxApp, BrxApp, MyLine, Zeichne, ACRX_CMD_TRANSPARENT, NULL)
