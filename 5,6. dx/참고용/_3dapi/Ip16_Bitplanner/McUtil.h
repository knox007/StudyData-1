// Interface for the Utilities.
//
////////////////////////////////////////////////////////////////////////////////

#ifndef _MCUTIL_H_
#define _MCUTIL_H_

#define SAFE_DELETE(p)			{ if(p) { delete (p);     (p)=NULL; } }
#define SAFE_DELETE_ARRAY(p)	{ if(p) { delete[] (p);   (p)=NULL; } }
#define SAFE_RELEASE(p)			{ if(p) { (p)->Release(); (p)=NULL; } }

#define SAFE_FRMMOV(p)			{ if(p)	{if(FAILED((p)->FrameMove()))return -1;	}}
#define SAFE_RENDER(p)			{ if(p)	{ (p)->Render();			} }


#define SAFE_DESTROY_WINDOW(p)	{	if(p){	DestroyWindow(p);	p=NULL;	}	}

#define SAFE_NEWINIT(p, CLASSNAME)								\
{																\
	if(NULL == p)												\
	{															\
		p = new CLASSNAME;										\
																\
		if(FAILED( (p)->Init()))								\
		{														\
			delete (p);											\
			(p)	= NULL;											\
																\
			return -1;											\
		}														\
	}															\
}

#endif