// ScanPerson.cpp : DLL ������ʵ�֡�
#include "stdafx.h"
#include "resource.h"
#include "ScanPerson_i.h"
#include "dllmain.h"
#include "KinectControler.h"
#include "blaxxunVRML.h"
#include "QueryNode.h"
#include "KinectData.h"
#include "VrmlData.h"
#include "SingleControler.h"


// ����ȷ�� DLL �Ƿ���� OLE ж��
STDAPI DllCanUnloadNow(void)
{
    return _AtlModule.DllCanUnloadNow();
}


// ����һ���๤���Դ������������͵Ķ���
STDAPI DllGetClassObject(REFCLSID rclsid, REFIID riid, LPVOID* ppv)
{
    return _AtlModule.DllGetClassObject(rclsid, riid, ppv);
}


// DllRegisterServer - ������ӵ�ϵͳע���
STDAPI DllRegisterServer(void)
{
    // ע��������Ϳ�����Ϳ��е����нӿ�
    HRESULT hr = _AtlModule.DllRegisterServer();
	return hr;
}


// DllUnregisterServer - �����ϵͳע������Ƴ�
STDAPI DllUnregisterServer(void)
{
	HRESULT hr = _AtlModule.DllUnregisterServer();
	return hr;
}

// DllInstall - ���û����߰��������ϵͳע��������/ɾ��
//              �	
STDAPI DllInstall(BOOL bInstall, LPCWSTR pszCmdLine)
{
    HRESULT hr = E_FAIL;
    static const wchar_t szUserSwitch[] = _T("user");

    if (pszCmdLine != NULL)
    {
    	if (_wcsnicmp(pszCmdLine, szUserSwitch, _countof(szUserSwitch)) == 0)
    	{
    		AtlSetPerUserRegistration(true);
    	}
    }

    if (bInstall)
    {	
    	hr = DllRegisterServer();
    	if (FAILED(hr))
    	{	
    		DllUnregisterServer();
    	}
    }
    else
    {
    	hr = DllUnregisterServer();
    }

    return hr;
}

// ScanPerson.cpp : CScanPerson ��ʵ��

#include "stdafx.h"
#include "ScanPerson.h"

CScanPerson::CScanPerson()
{

}
CScanPerson::~CScanPerson(){
//	KinectClose();
}


STDMETHODIMP CScanPerson::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_IbxxHID
	};
	for (int i=0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}


HRESULT STDMETHODCALLTYPE CScanPerson::Init( 
							   /* [in] */ BSTR Device,
							   /* [in] */ int DeviceNo,
							   /* [in] */ Browser *pBrowser,
							   /* [retval][out] */ int *pDeviceNoUsed)
{
	int i=1;
	DeviceNo=1;
	*pDeviceNoUsed= 1;
	return S_OK;
}



HRESULT STDMETHODCALLTYPE CScanPerson::RemoveDeviceSensor( 
	/* [in] */ int ID)
{
	return S_OK;
}

HRESULT STDMETHODCALLTYPE CScanPerson::Tick( 
							   /* [in] */ double SimTime,
							   /* [in] */ double FrameRate) 
{
//	UpdateImage();
	return S_OK;

}

HRESULT STDMETHODCALLTYPE CScanPerson::EnabledChanged( 
	int ID,
	BOOL Enabled,
	/* [retval][out] */ BOOL *pSetIsActive)
{
return S_OK;
}

HRESULT STDMETHODCALLTYPE CScanPerson::FocusChanged( 
									   /* [in] */ BOOL HasFocusNow,
									   /* [retval][out] */ BOOL *pNeedTickCalls)
{
*pNeedTickCalls=true;
return S_OK;
}


HRESULT STDMETHODCALLTYPE CScanPerson::AddDeviceSensor( 
	/* [in] */ BSTR eventType,
	/* [in] */ Node *pEventNode,
	/* [in] */ EventInSFBool *pIsActive,
	/* [in] */ BOOL Enabled,
	/* [in] */ int ID,
	/* [retval][out] */ int *pRetVal)
{	
	EventOutSFNode* clr_dev1,*clr_dev2,*clr_dev3;
	QuerySFNode(pEventNode,_T("colorTexture_dev1"),IID_EventOutSFNode,&clr_dev1);
	QuerySFNode(pEventNode,_T("colorTexture_dev2"),IID_EventOutSFNode,&clr_dev2);
	QuerySFNode(pEventNode,_T("colorTexture_dev3"),IID_EventOutSFNode,&clr_dev3);

	EventOutSFNode *crd_dev1,*crd_dev2,*crd_dev3;
	QuerySFNode(pEventNode,_T("coord_dev1"),IID_EventOutSFNode,&crd_dev1);
	QuerySFNode(pEventNode,_T("coord_dev2"),IID_EventOutSFNode,&crd_dev2);
	QuerySFNode(pEventNode,_T("coord_dev3"),IID_EventOutSFNode,&crd_dev3);

	EventOutSFNode *faceSet;
	QuerySFNode(pEventNode,_T("IndxFaceSet"),IID_EventOutSFNode,&faceSet);

	EventOutSFNode* extra;
	QuerySFNode(pEventNode,_T("extra"),IID_EventOutSFNode,&extra);

	EventOutSFInt32* key;
	QuerySFNode(pEventNode,_T("keyObserver"),IID_EventOutSFInt32,&key);

	VrmlData* vrmlData=new VrmlData();
	vrmlData->setTexture1(clr_dev1);
	vrmlData->setCoord1(crd_dev1);
	vrmlData->setTexture1(clr_dev2);
	vrmlData->setCoord1(crd_dev2);
	vrmlData->setTexture1(clr_dev3);
	vrmlData->setCoord1(crd_dev3);
	KinectData* devData=new KinectData();
	int num=devData->getDevNum();
	initStatus ini=devData->initData();
	if(ini!=initStatus::success)
	{
		delete devData;
		delete vrmlData;
		return S_FALSE;
	}
	SingleControler* single=new	SingleControler(*vrmlData,*devData);
	*pRetVal=1;
	return S_OK;
}

