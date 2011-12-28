// ScanPerson.h : CScanPerson 的声明

#pragma once
#include "resource.h"       // 主符号

#include "ScanPerson_i.h"


#if defined(_WIN32_WCE) && !defined(_CE_DCOM) && !defined(_CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA)
#error "Windows CE 平台(如不提供完全 DCOM 支持的 Windows Mobile 平台)上无法正确支持单线程 COM 对象。定义 _CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA 可强制 ATL 支持创建单线程 COM 对象实现并允许使用其单线程 COM 对象实现。rgs 文件中的线程模型已被设置为“Free”，原因是该模型是非 DCOM Windows CE 平台支持的唯一线程模型。"
#endif

// ScanPerson.h : CScanPerson 的声明

#pragma once
#include "resource.h"       // 主符号

#include "ScanPerson_i.h"


#if defined(_WIN32_WCE) && !defined(_CE_DCOM) && !defined(_CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA)
#error "Windows CE 平台(如不提供完全 DCOM 支持的 Windows Mobile 平台)上无法正确支持单线程 COM 对象。定义 _CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA 可强制 ATL 支持创建单线程 COM 对象实现并允许使用其单线程 COM 对象实现。rgs 文件中的线程模型已被设置为“Free”，原因是该模型是非 DCOM Windows CE 平台支持的唯一线程模型。"
#endif

// ScanPerson.h : CScanPerson 的声明

#pragma once
#include "resource.h"       // 主符号

#include "ScanPerson_i.h"
#include "blaxxunhid.h"


#if defined(_WIN32_WCE) && !defined(_CE_DCOM) && !defined(_CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA)
#error "Windows CE 平台(如不提供完全 DCOM 支持的 Windows Mobile 平台)上无法正确支持单线程 COM 对象。定义 _CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA 可强制 ATL 支持创建单线程 COM 对象实现并允许使用其单线程 COM 对象实现。rgs 文件中的线程模型已被设置为“Free”，原因是该模型是非 DCOM Windows CE 平台支持的唯一线程模型。"
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

DECLARE_REGISTRY_RESOURCEID(IDR_SCANPERSON)


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
	EventInSFNode *m_ColorImg;
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


