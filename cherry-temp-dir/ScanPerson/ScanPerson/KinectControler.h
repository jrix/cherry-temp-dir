#pragma once
#include <XnStatus.h>
#include <XnCppWrapper.h>
#include "blaxxunVRML.h"
#include "KinectData.h"
#include "VrmlData.h"
using namespace xn;

class KinectControler{
public:
	KinectControler::KinectControler(const VrmlData& v_data,const KinectData& k_data,int x_step,int y_step);
	~KinectControler();
	const KinectData& getDevData()const;
	const VrmlData& getVrmlData()const;
	XnUInt32 getXStep()const;
	XnUInt32 getYStep()const;
	virtual void  start();
	virtual int update();
	virtual initStatus init();
	virtual void  close();
protected:
	/*XnUInt32 blockSize;
	XnPoint3D* depthPts;
	XnPoint3D* clorPts;*/
	initStatus ini_stus;	
	const KinectData& _devData;
	const VrmlData& _vrmlData;
private:	

	XnUInt32 _yStep;
	XnUInt32 _xStep;
};
