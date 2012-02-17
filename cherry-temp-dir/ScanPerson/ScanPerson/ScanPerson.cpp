// ScanPerson.cpp : DLL ������ʵ�֡�


#include "stdafx.h"
#include "resource.h"
#include "ScanPerson_i.h"
#include "dllmain.h"
#include "KinectControl.h"
#include "blaxxunVRML.h"
#include "globalVar.h"
#include "QueryNode.h"

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
	KinectClose();
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

HRESULT STDMETHODCALLTYPE CScanPerson::AddDeviceSensor( 
	/* [in] */ BSTR eventType,
	/* [in] */ Node *pEventNode,
	/* [in] */ EventInSFBool *pIsActive,
	/* [in] */ BOOL Enabled,
	/* [in] */ int ID,
	/* [retval][out] */ int *pRetVal)
{
	


	
	EventOutSFNode* clr_dev1,*clr_dev2;
	Node* img1,*img2;
	QuerySFNode(pEventNode,_T("colorTexture_dev1"),IID_EventOutSFNode,&clr_dev1,&img1);
	QuerySFNode(pEventNode,_T("colorTexture_dev2"),IID_EventOutSFNode,&clr_dev2,&img2);
	clr_dev1->Release();
	clr_dev2->Release();

	EventOutSFNode *crd_dev1,*crd_dev2;
	Node *crd1,*crd2;
	QuerySFNode(pEventNode,_T("coord_dev1"),IID_EventOutSFNode,&crd_dev1,&crd1);
	QuerySFNode(pEventNode,_T("coord_dev2"),IID_EventOutSFNode,&crd_dev2,&crd2);
	crd_dev1->Release();
	crd_dev2->Release();

	EventOutSFNode *faceSet;
	Node* face;
	QuerySFNode(pEventNode,_T("IndxFaceSet"),IID_EventOutSFNode,&faceSet,&face);
	faceSet->Release();


	EventOutSFNode* extra;
	Node* ext;
	QuerySFNode(pEventNode,_T("extra"),IID_EventOutSFNode,&extra,&ext);

	KinectInit(img1,img2,crd1,crd2,face,ext);

	*pRetVal=1;
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
	UpdateImage();
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

