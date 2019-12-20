#pragma once
#ifndef _Mesh_SizeMapMacros_Header
#define _Mesh_SizeMapMacros_Header

#define VIRTUAL_SIZEMAP 

#ifdef VIRTUAL_SIZEMAP
#define SIZEMAP_OVERRIDE override
#else
#define SIZEMAP_OVERRIDE
#endif

#ifdef VIRTUAL_SIZEMAP
#define SIZEMAP_INHERITANCE(BASE_CLASS, CLASS) BASE_CLASS 
#else
#define SIZEMAP_INHERITANCE(BASE_CLASS, CLASS) std::enable_shared_from_this<CLASS>, public Global_Done
#endif

#endif // !_Mesh_SizeMapMacros_Header
