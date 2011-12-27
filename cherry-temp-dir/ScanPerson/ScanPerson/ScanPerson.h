// ScanPerson.h : CScanPerson ������

#pragma once
#include "resource.h"       // ������

#include "ScanPerson_i.h"


#if defined(_WIN32_WCE) && !defined(_CE_DCOM) && !defined(_CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA)
#error "Windows CE ƽ̨(�粻�ṩ��ȫ DCOM ֧�ֵ� Windows Mobile ƽ̨)���޷���ȷ֧�ֵ��߳� COM ���󡣶��� _CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA ��ǿ�� ATL ֧�ִ������߳� COM ����ʵ�ֲ�����ʹ���䵥�߳� COM ����ʵ�֡�rgs �ļ��е��߳�ģ���ѱ�����Ϊ��Free����ԭ���Ǹ�ģ���Ƿ� DCOM Windows CE ƽ̨֧�ֵ�Ψһ�߳�ģ�͡�"
#endif

// ScanPerson.h : CScanPerson ������

#pragma once
#include "resource.h"       // ������

#include "ScanPerson_i.h"


#if defined(_WIN32_WCE) && !defined(_CE_DCOM) && !defined(_CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA)
#error "Windows CE ƽ̨(�粻�ṩ��ȫ DCOM ֧�ֵ� Windows Mobile ƽ̨)���޷���ȷ֧�ֵ��߳� COM ���󡣶��� _CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA ��ǿ�� ATL ֧�ִ������߳� COM ����ʵ�ֲ�����ʹ���䵥�߳� COM ����ʵ�֡�rgs �ļ��е��߳�ģ���ѱ�����Ϊ��Free����ԭ���Ǹ�ģ���Ƿ� DCOM Windows CE ƽ̨֧�ֵ�Ψһ�߳�ģ�͡�"
#endif

// ScanPerson.h : CScanPerson ������

#pragma once
#include "resource.h"       // ������

#include "ScanPerson_i.h"
#include "blaxxunhid.h"


#if defined(_WIN32_WCE) && !defined(_CE_DCOM) && !defined(_CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA)
#error "Windows CE ƽ̨(�粻�ṩ��ȫ DCOM ֧�ֵ� Windows Mobile ƽ̨)���޷���ȷ֧�ֵ��߳� COM ���󡣶��� _CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA ��ǿ�� ATL ֧�ִ������߳� COM ����ʵ�ֲ�����ʹ���䵥�߳� COM ����ʵ�֡�rgs �ļ��е��߳�ģ���ѱ�����Ϊ��Free����ԭ���Ǹ�ģ���Ƿ� DCOM Windows CE ƽ̨֧�ֵ�Ψһ�߳�ģ�͡�"
#endif



// CScanPerson

class ATL_NO_VTABLE CScanPerson :
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CScanPerson, &CLSID_ScanPerson>,
	public ISupportErrorInfo,
	public IDispatchImpl<IbxxHID, &IID_IbxxHID, &LIBID_ScanPersonLib, /*wMajor =*/ 1, /*wMinor =*/ 0>
{
public:
	CScanPerson();
	~CScanPerson();

DECLARE_REGISTRY_RESOURCEID(IDR_SCANPERSON3)


BEGIN_COM_MAP(CScanPerson)
	COM_INTERFACE_ENTRY(IbxxHID)
	COM_INTERFACE_ENTRY(IDispatch)
END_COM_MAP()

STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);


	DECLARE_PROTECT_FINAL_CONSTRUCT()

	HRESULT FinalConstruct()
	{
		return S_OK;
	}

	void FinalRelease()
	{
	}

public:
	HRESULT STDMETHODCALLTYPE Init( 
		/* [in] */ BSTR Device,
		/* [in] */ int DeviceNo,
		/* [in] */ Browser *pBrowser,
		/* [retval][out] */ int *pDeviceNoUsed);

	HRESULT STDMETHODCALLTYPE AddDeviceSensor( 
		/* [in] */ BSTR eventType,
		/* [in] */ Node *pEventNode,
		/* [in] */ EventInSFBool *pIsActive,
		/* [in] */ BOOL Enabled,
		/* [in] */ int ID,
		/* [retval][out] */ int *pRetVal);

	HRESULT STDMETHODCALLTYPE RemoveDeviceSensor( 
		/* [in] */ int ID);

	HRESULT STDMETHODCALLTYPE Tick( 
		/* [in] */ double SimTime,
		/* [in] */ double FrameRate);

	HRESULT STDMETHODCALLTYPE EnabledChanged( 
		int ID,
		BOOL Enabled,
		/* [retval][out] */ BOOL *pSetIsActive);

	HRESULT STDMETHODCALLTYPE FocusChanged( 
		/* [in] */ BOOL HasFocusNow,
		/* [retval][out] */ BOOL *pNeedTickCalls);


};

OBJECT_ENTRY_AUTO(__uuidof(ScanPerson), CScanPerson)


