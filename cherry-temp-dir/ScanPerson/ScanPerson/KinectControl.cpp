#include "stdafx.h"
#include "KinectControl.h"
#include "XnCppWrapper.h"
#include "D3D9TYPES.h"
#include "blaxxunVRML.h"
#include "globalVar.h"
#include <vector>
using namespace xn;

const int showStyle=1;
XnUInt32 pixSize;
int xres;
int yres;
int sensor_count;
GenGrp *sensors;
CComQIPtr<IBufferTexture> g_bufTex;
EventInMFVec3f* g_pts;
EventInMFVec3f* g_mesh;
Context g_Context;
XnStatus  checkSensors();
void drawPoint(XnUInt32 devId,XnUserID nId);
XnUInt16 tdel=0;
XnUInt32 rows=0;
XnBool findValidCell=0;

void KinectInit(CComPtr<Node> img,CComPtr<EventInMFVec3f> pts,CComPtr<EventInMFVec3f> mesh){
	g_bufTex=img;
	g_pts=pts;
	g_mesh=mesh;
	XnStatus rc=XN_STATUS_OK;
	rc=g_Context.Init();
	const XnChar* rslt=xnGetStatusString(rc);
	rc=checkSensors();
	xres=sensors[0].xres;
	yres=sensors[0].yres;
	g_bufTex->setFormat(xres,yres,0,D3DFMT_R8G8B8,0);
	pixSize = 3;
	g_bufTex->setTexture(0,xres*yres*pixSize,(BYTE*)sensors[0].pImageData,xres*pixSize);
}

void UpdateImage(){	
	g_Context.WaitAndUpdateAll();
//	g_bufTex->setTexture(0,2*xres*yres,(BYTE*)sensors[0].pDepthData,2*xres);
	g_bufTex->setTexture(0,xres*yres*pixSize,(BYTE*)sensors[0].pImageData,xres*pixSize);
	drawPoint(0,1);
}
GenGrp  getGrp(){
	GenGrp p;
	DepthGenerator dd=p.depGen;
	return p;
}
XnStatus checkSensors(){
	NodeInfoList devicesList;
	XnStatus rc;
	rc=g_Context.EnumerateProductionTrees(XN_NODE_TYPE_DEVICE,NULL,devicesList);
	int i=0;
	NodeInfoList::Iterator it=devicesList.Begin();
	for(it;it!=devicesList.End();it++,i++){}
	sensor_count=i;
	sensors=new GenGrp[sensor_count];
	i=0;
	it=devicesList.Begin();
	const XnChar* statusStr;
	for(;it!=devicesList.End();it++,i++){
		NodeInfo devInf=*it;
		rc=g_Context.CreateProductionTree(devInf);
		CHECK_RC(rc,"Create Device");
		const XnChar * devName=devInf.GetInstanceName();
		XnInt32 len =xnOSStrLen(devName); 
		Query query;
		query.AddNeededNode(devName);
		xnOSMemCopy(sensors[i].name,devName,len);
		rc=g_Context.CreateAnyProductionTree(XN_NODE_TYPE_DEPTH,&query,sensors[i].depGen);
		statusStr=xnGetStatusString(rc);
		CHECK_RC(rc,"CreateDepGen");
		rc=g_Context.CreateAnyProductionTree(XN_NODE_TYPE_IMAGE,&query,sensors[i].imgGen);
		statusStr=xnGetStatusString(rc);
		CHECK_RC(rc,"CreateImgGen");
		rc=g_Context.CreateAnyProductionTree(XN_NODE_TYPE_USER,&query,sensors[i].userGen);
		statusStr=xnGetStatusString(rc);
		CHECK_RC(rc,"CreateUsrGen");
		rc=g_Context.CreateAnyProductionTree(XN_NODE_TYPE_SCENE,&query,sensors[i].scenGen);
		statusStr=xnGetStatusString(rc);
		CHECK_RC(rc,"CreateScenAnly");
		DepthMetaData depMD;
		ImageMetaData imgMD;
		sensors[i].depGen.GetMetaData(depMD);
		sensors[i].imgGen.GetMetaData(imgMD);
		sensors[i].xres=depMD.XRes();
		sensors[i].yres=depMD.YRes();
		sensors[i].pDepthData=depMD.Data();
		sensors[i].pImageData=imgMD.Data();
	}
	g_Context.StartGeneratingAll();
	return rc;
}


void getValidUserNum(XnUInt32 devId,XnUserID aUsers[],XnUInt16 aUsersNum){
	sensors[devId].userGen.GetUsers(aUsers,aUsersNum);
}
//a long  long test code
void drawPoint(XnUInt32 devId,XnUserID nId){
	if(tdel==0)
	{
		XnBool hasUsrPix=false;
		SceneMetaData usrPix;
		XnStatus rc=XN_STATUS_OK;
		sensors[devId].scenGen.GetMetaData(usrPix);
		rc=sensors[devId].userGen.GetUserPixels(0,usrPix);
		const XnChar* rslt=xnGetStatusString(rc);
		XnUInt32 xres=sensors[devId].xres;
		XnUInt32 yres=sensors[devId].yres;
		XnUInt32 ptSize=xres*yres;
		if(rc==XN_STATUS_OK){
			XnPoint3D* pts=new XnPoint3D[ptSize];
			XnUInt32 len=0;
			XnUInt32 size=usrPix.DataSize();
			//	const XnLabel* pLab=usrPix.Data();
			XnUInt32 psize=usrPix.BytesPerPixel();
			hasUsrPix=TRUE;
			const XnLabel *p=usrPix.Data(); 
			std::vector<XnPoint3D> vecList;
			std::vector<XnPoint3D>::iterator vec_ptr=vecList.begin();
			for(XnUInt32 i=0;i<yres;i++){
				for(XnUInt32 j=0;j<xres;j++){
					if(*p==0){
						p++;
						continue;
					}
					XnUInt32 dep=sensors[devId].pDepthData[j+i*xres];
					pts[len].X=j;
					pts[len].Y=i;
					pts[len].Z=dep;
					p++;
					len++;
//******************************************
					if(xres-1==j||yres-1==i){
						continue;
					}
					XnPoint3D pts_squ[4];
					XnLabel dep_squ[4];
					dep_squ[0]=dep;
					dep_squ[1]=sensors[devId].pDepthData[j+1+i*xres];
					dep_squ[2]=sensors[devId].pDepthData[j+1+(i+1)*xres];
					dep_squ[3]=sensors[devId].pDepthData[j+(i+1)*xres];
					pts_squ[0].X=j;
					pts_squ[0].Y=i;
					pts_squ[0].Z=dep;
					pts_squ[1].X=j+1;
					pts_squ[1].Y=i;
					pts_squ[1].Z=dep_squ[1];
					pts_squ[2].X=j+1;
					pts_squ[2].Y=i+1;
					pts_squ[2].Z=dep_squ[2];
					pts_squ[3].X=j;
					pts_squ[3].Y=i+1;
					pts_squ[3].Z=dep_squ[3];

//*************************************************						
					int* id=new int[4];
					id[0]=0;
					int tri_num=1;
					for(int i=1;i<4;i++){
						if(p[i]==0)
						{
							continue;
						}else{
							id[tri_num]=i;
							tri_num++;
						}
					}
					if(tri_num<3){
						printf("trinum is less then 3:it is %d",tri_num);
					}else if(tri_num==3){
						XnPoint3D mesh[3];
						mesh[0]=pts_squ[id[0]];
						mesh[1]=pts_squ[id[1]];
						mesh[2]=pts_squ[id[2]];
						XnPoint3D* aRealWorld=new XnPoint3D[3];
						sensors[devId].depGen.ConvertProjectiveToRealWorld(3,mesh,aRealWorld);
						vecList.push_back(aRealWorld[0]);
						vecList.push_back(aRealWorld[1]);
						vecList.push_back(aRealWorld[2]);
						delete[] aRealWorld;
						printf("trinum == 3:it is %d",tri_num);
					}else{
						XnPoint3D mesh1[6];
						mesh1[0]=pts_squ[0];
						mesh1[1]=pts_squ[1];
						mesh1[2]=pts_squ[2];	
						mesh1[3]=pts_squ[0];
						mesh1[4]=pts_squ[2];
						mesh1[5]=pts_squ[3];
						XnPoint3D* aRealWorld=new XnPoint3D[6];
						sensors[devId].depGen.ConvertProjectiveToRealWorld(6,mesh1,aRealWorld);
						vecList.push_back(aRealWorld[0]);
						vecList.push_back(aRealWorld[1]);
						vecList.push_back(aRealWorld[2]);
						vecList.push_back(aRealWorld[3]);
						vecList.push_back(aRealWorld[4]);
						vecList.push_back(aRealWorld[5]);
						delete[] aRealWorld;
						printf("trinum == 4:it is %d",tri_num);
					}
					
//************************************************
				}
			}
			int v_size=vecList.size();
			int v_3time=v_size*3;
			if(v_size>0){
				float* putIn=new float[v_3time];
				vec_ptr=vecList.begin();
				for(int k=0;k<v_3time;k=k+3,vec_ptr++){
					putIn[k]=-vec_ptr->X;
					putIn[k+1]=vec_ptr->Y;
					putIn[k+2]=-vec_ptr->Z;
				}
				g_mesh->setValue(1,NULL);
				g_mesh->setValue(v_3time,putIn);
				tdel=1;
				delete[] putIn;
			}
			if(len>0){
				XnPoint3D* aRealWorld=new XnPoint3D[len];
				sensors[devId].depGen.ConvertProjectiveToRealWorld(len,pts,aRealWorld);
				for(int k=0;k<len;k++){
					aRealWorld[k].X*=-1;
					aRealWorld[k].Z*=-1;
				}
				g_pts->setValue(1,NULL);
				g_pts->setValue(len*3,(float*)aRealWorld);
				delete[] aRealWorld;
			}
			delete[] pts;	
		}
	}
}

void ReadCell()
{
		
}
void ReadRow()
{

}

void ReadGrid()
{

}


void KinectClose(){
	g_Context.Shutdown();
}