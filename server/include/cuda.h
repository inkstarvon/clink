/* 
 * Clink
 * Copyright (C) 2023 cair <rui.cai@tenclass.com>
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#ifndef _CLINK_CUDA_H
#define _CLINK_CUDA_H

#include <map>
#include <uuid/uuid.h>
#include "render.h"
#include "linuz/cuda/cuda.h"
#include "linuz/cuda/driver_api.h"

struct CudaRequest {
  uint32_t version;
  uint32_t api_index;
  uint32_t param_count;
  uint64_t params[0];
} __attribute__((packed));

#define CUDA_REQUEST_EXTEND(request) (((char*)(request)) + sizeof(CudaRequest) + ((request)->param_count) * sizeof(uint64_t))
#define FIELD_OFFSET(data) (((char*)(data)) + sizeof(*data))

class Cuda : public Render {
private:
  uint32_t version_;
  std::string log_buffer_;
  std::string error_buffer_;
  std::map<void*, void*> guest_host_memory_;

  void TranslateJitOptions(uint32_t num_option, CUjit_option* options, void** values);

  void Dispatch(WorkerItem* item);
  void DispatchCuInit(CudaRequest* request, RenderResponse* response);
  void DispatchCuDriverGetVersion(CudaRequest* request, RenderResponse* response);
  void DispatchCuDeviceGetCount(CudaRequest* request, RenderResponse* response);
  void DispatchCuDeviceGet(CudaRequest* request, RenderResponse* response);
  void DispatchCuDeviceGetName(CudaRequest* request, RenderResponse* response);
  void DispatchCuDeviceComputeCapability(CudaRequest* request, RenderResponse* response);
  void DispatchCuGetErrorString(CudaRequest* request, RenderResponse* response);
  void DispatchCuDeviceGetAttribute(CudaRequest* request, RenderResponse* response);
  void DispatchCuDeviceTotalMem(CudaRequest* request, RenderResponse* response);
  void DispatchCuDeviceGetUuid(CudaRequest* request, RenderResponse* response);
  void DispatchCuCtxCreate(CudaRequest* request, RenderResponse* response);
  void DispatchCuMemGetInfo(CudaRequest* request, RenderResponse* response);
  void DispatchCuCtxDestroy(CudaRequest* request, RenderResponse* response);
  void DispatchCuLinkCreate(CudaRequest* request, RenderResponse* response);
  void DispatchCuLinkAddData(CudaRequest* request, RenderResponse* response);
  void DispatchCuLinkComplete(CudaRequest* request, RenderResponse* response);
  void DispatchCuModuleLoadData(CudaRequest* request, RenderResponse* response);
  void DispatchCuLinkDestroy(CudaRequest* request, RenderResponse* response);
  void DispatchCuModuleGetGlobal(CudaRequest* request, RenderResponse* response);
  void DispatchCuModuleUnload(CudaRequest* request, RenderResponse* response);
  void DispatchCuModuleGetTexRef(CudaRequest* request, RenderResponse* response);
  void DispatchCuModuleGetFunction(CudaRequest* request, RenderResponse* response);
  void DispatchCuFuncSetCacheConfig(CudaRequest* request, RenderResponse* response);
  void DispatchCuFuncGetAttribute(CudaRequest* request, RenderResponse* response);
  void DispatchCuMemHostAlloc(CudaRequest* request, RenderResponse* response);
  void DispatchCuMemHostGetDevicePointer(CudaRequest* request, RenderResponse* response);
  void DispatchCuMemcpyHtoD(CudaRequest* request, RenderResponse* response);
  void DispatchCuMemAlloc(CudaRequest* request, RenderResponse* response);
  void DispatchCuEventCreate(CudaRequest* request, RenderResponse* response);
  void DispatchCuLaunchKernel(CudaRequest* request, RenderResponse* response);
  void DispatchCuStreamSynchronize(CudaRequest* request, RenderResponse* response);
  void DispatchCuMemcpyDtoD(CudaRequest* request, RenderResponse* response);
  void DispatchCuMemFree(CudaRequest* request, RenderResponse* response);
  void DispatchCuTexRefSetFormat(CudaRequest* request, RenderResponse* response);
  void DispatchcuTexRefSetAddressMode(CudaRequest* request, RenderResponse* response);
  void DispatchCuTexRefSetFlags(CudaRequest* request, RenderResponse* response);
  void DispatchCuTexRefSetAddress(CudaRequest* request, RenderResponse* response);
  void DispatchCuArrayCreate(CudaRequest* request, RenderResponse* response);
  void DispatchCuArrayDestroy(CudaRequest* request, RenderResponse* response);
  void DispatchCuArray3DCreate(CudaRequest* request, RenderResponse* response);
  void DispatchCuMemcpy3D(CudaRequest* request, RenderResponse* response);
  void DispatchCuTexRefSetFilterMode(CudaRequest* request, RenderResponse* response);
  void DispatchCuTexRefSetArray(CudaRequest* request, RenderResponse* response);
  void DispatchCuMemcpyDtoH(CudaRequest* request, RenderResponse* response);
  void DispatchCuMemsetD8Async(CudaRequest* request, RenderResponse* response);
  void DispatchCuEventRecord(CudaRequest* request, RenderResponse* response);
  void DispatchCuEventSynchronize(CudaRequest* request, RenderResponse* response);
  void DispatchCuMemFreeHost(CudaRequest* request, RenderResponse* response);
  void DispatchCuMemcpy2D(CudaRequest* request, RenderResponse* response);
  void DispatchCuEventDestroy(CudaRequest* request, RenderResponse* response);
  void DispatchCuCtxSetCurrent(CudaRequest* request, RenderResponse* response);
  void DispatchCuTexObjectCreate(CudaRequest* request, RenderResponse* response);
  void DispatchCuTexObjectDestroy(CudaRequest* request, RenderResponse* response);
  void DispatchCuMemAllocPitch(CudaRequest* request, RenderResponse* response);
  void DispatchCuMemHostRegister(CudaRequest* request, RenderResponse* response);
  void DispatchCuMemHostUnregister(CudaRequest* request, RenderResponse* response);
  void DispatchCuCtxPopCurrent(CudaRequest* request, RenderResponse* response);
  void DispatchCuCtxPushCurrent(CudaRequest* request, RenderResponse* response);
  void DispatchCuStreamCreate(CudaRequest* request, RenderResponse* response);

  inline const char* GetCudaFunctionName(uint32_t index) {
    switch (index){
      case CUGETERRORSTRING: return "cuGetErrorString";
      case CUGETERRORNAME: return "cuGetErrorName";
      case CUINIT: return "cuInit";
      case CUDRIVERGETVERSION: return "cuDriverGetVersion";
      case CUDEVICEGET: return "cuDeviceGet";
      case CUDEVICEGETCOUNT: return "cuDeviceGetCount";
      case CUDEVICEGETNAME: return "cuDeviceGetName";
      case CUDEVICEGETUUID: return "cuDeviceGetUuid";
      case CUDEVICEGETUUID_V2: return "cuDeviceGetUuid_v2";
      case CUDEVICEGETLUID: return "cuDeviceGetLuid";
      case CUDEVICETOTALMEM: return "cuDeviceTotalMem";
      case CUDEVICEGETTEXTURE1DLINEARMAXWIDTH: return "cuDeviceGetTexture1DLinearMaxWidth";
      case CUDEVICEGETATTRIBUTE: return "cuDeviceGetAttribute";
      case CUDEVICEGETNVSCISYNCATTRIBUTES: return "cuDeviceGetNvSciSyncAttributes";
      case CUDEVICESETMEMPOOL: return "cuDeviceSetMemPool";
      case CUDEVICEGETMEMPOOL: return "cuDeviceGetMemPool";
      case CUDEVICEGETDEFAULTMEMPOOL: return "cuDeviceGetDefaultMemPool";
      case CUDEVICEGETEXECAFFINITYSUPPORT: return "cuDeviceGetExecAffinitySupport";
      case CUFLUSHGPUDIRECTRDMAWRITES: return "cuFlushGPUDirectRDMAWrites";
      case CUDEVICEGETPROPERTIES: return "cuDeviceGetProperties";
      case CUDEVICECOMPUTECAPABILITY: return "cuDeviceComputeCapability";
      case CUDEVICEPRIMARYCTXRETAIN: return "cuDevicePrimaryCtxRetain";
      case CUDEVICEPRIMARYCTXRELEASE: return "cuDevicePrimaryCtxRelease";
      case CUDEVICEPRIMARYCTXSETFLAGS: return "cuDevicePrimaryCtxSetFlags";
      case CUDEVICEPRIMARYCTXGETSTATE: return "cuDevicePrimaryCtxGetState";
      case CUDEVICEPRIMARYCTXRESET: return "cuDevicePrimaryCtxReset";
      case CUCTXCREATE: return "cuCtxCreate";
      case CUCTXCREATE_V3: return "cuCtxCreate_v3";
      case CUCTXDESTROY: return "cuCtxDestroy";
      case CUCTXPUSHCURRENT: return "cuCtxPushCurrent";
      case CUCTXPOPCURRENT: return "cuCtxPopCurrent";
      case CUCTXSETCURRENT: return "cuCtxSetCurrent";
      case CUCTXGETCURRENT: return "cuCtxGetCurrent";
      case CUCTXGETDEVICE: return "cuCtxGetDevice";
      case CUCTXGETFLAGS: return "cuCtxGetFlags";
      case CUCTXSETFLAGS: return "cuCtxSetFlags";
      case CUCTXGETID: return "cuCtxGetId";
      case CUCTXSYNCHRONIZE: return "cuCtxSynchronize";
      case CUCTXSETLIMIT: return "cuCtxSetLimit";
      case CUCTXGETLIMIT: return "cuCtxGetLimit";
      case CUCTXGETCACHECONFIG: return "cuCtxGetCacheConfig";
      case CUCTXSETCACHECONFIG: return "cuCtxSetCacheConfig";
      case CUCTXGETSHAREDMEMCONFIG: return "cuCtxGetSharedMemConfig";
      case CUCTXSETSHAREDMEMCONFIG: return "cuCtxSetSharedMemConfig";
      case CUCTXGETAPIVERSION: return "cuCtxGetApiVersion";
      case CUCTXGETSTREAMPRIORITYRANGE: return "cuCtxGetStreamPriorityRange";
      case CUCTXRESETPERSISTINGL2CACHE: return "cuCtxResetPersistingL2Cache";
      case CUCTXGETEXECAFFINITY: return "cuCtxGetExecAffinity";
      case CUCTXATTACH: return "cuCtxAttach";
      case CUCTXDETACH: return "cuCtxDetach";
      case CUMODULELOAD: return "cuModuleLoad";
      case CUMODULELOADDATA: return "cuModuleLoadData";
      case CUMODULELOADDATAEX: return "cuModuleLoadDataEx";
      case CUMODULELOADFATBINARY: return "cuModuleLoadFatBinary";
      case CUMODULEUNLOAD: return "cuModuleUnload";
      case CUMODULEGETLOADINGMODE: return "cuModuleGetLoadingMode";
      case CUMODULEGETFUNCTION: return "cuModuleGetFunction";
      case CUMODULEGETGLOBAL: return "cuModuleGetGlobal";
      case CULINKCREATE: return "cuLinkCreate";
      case CULINKADDDATA: return "cuLinkAddData";
      case CULINKADDFILE: return "cuLinkAddFile";
      case CULINKCOMPLETE: return "cuLinkComplete";
      case CULINKDESTROY: return "cuLinkDestroy";
      case CUMODULEGETTEXREF: return "cuModuleGetTexRef";
      case CUMODULEGETSURFREF: return "cuModuleGetSurfRef";
      case CULIBRARYLOADDATA: return "cuLibraryLoadData";
      case CULIBRARYLOADFROMFILE: return "cuLibraryLoadFromFile";
      case CULIBRARYUNLOAD: return "cuLibraryUnload";
      case CULIBRARYGETKERNEL: return "cuLibraryGetKernel";
      case CULIBRARYGETMODULE: return "cuLibraryGetModule";
      case CUKERNELGETFUNCTION: return "cuKernelGetFunction";
      case CULIBRARYGETGLOBAL: return "cuLibraryGetGlobal";
      case CULIBRARYGETMANAGED: return "cuLibraryGetManaged";
      case CULIBRARYGETUNIFIEDFUNCTION: return "cuLibraryGetUnifiedFunction";
      case CUKERNELGETATTRIBUTE: return "cuKernelGetAttribute";
      case CUKERNELSETATTRIBUTE: return "cuKernelSetAttribute";
      case CUKERNELSETCACHECONFIG: return "cuKernelSetCacheConfig";
      case CUMEMGETINFO: return "cuMemGetInfo";
      case CUMEMALLOC: return "cuMemAlloc";
      case CUMEMALLOCPITCH: return "cuMemAllocPitch";
      case CUMEMFREE: return "cuMemFree";
      case CUMEMGETADDRESSRANGE: return "cuMemGetAddressRange";
      case CUMEMALLOCHOST: return "cuMemAllocHost";
      case CUMEMFREEHOST: return "cuMemFreeHost";
      case CUMEMHOSTALLOC: return "cuMemHostAlloc";
      case CUMEMHOSTGETDEVICEPOINTER: return "cuMemHostGetDevicePointer";
      case CUMEMHOSTGETFLAGS: return "cuMemHostGetFlags";
      case CUMEMALLOCMANAGED: return "cuMemAllocManaged";
      case CUDEVICEGETBYPCIBUSID: return "cuDeviceGetByPCIBusId";
      case CUDEVICEGETPCIBUSID: return "cuDeviceGetPCIBusId";
      case CUIPCGETEVENTHANDLE: return "cuIpcGetEventHandle";
      case CUIPCOPENEVENTHANDLE: return "cuIpcOpenEventHandle";
      case CUIPCGETMEMHANDLE: return "cuIpcGetMemHandle";
      case CUIPCOPENMEMHANDLE: return "cuIpcOpenMemHandle";
      case CUIPCCLOSEMEMHANDLE: return "cuIpcCloseMemHandle";
      case CUMEMHOSTREGISTER: return "cuMemHostRegister";
      case CUMEMHOSTUNREGISTER: return "cuMemHostUnregister";
      case CUMEMCPY: return "cuMemcpy";
      case CUMEMCPYPEER: return "cuMemcpyPeer";
      case CUMEMCPYHTOD: return "cuMemcpyHtoD";
      case CUMEMCPYDTOH: return "cuMemcpyDtoH";
      case CUMEMCPYDTOD: return "cuMemcpyDtoD";
      case CUMEMCPYDTOA: return "cuMemcpyDtoA";
      case CUMEMCPYATOD: return "cuMemcpyAtoD";
      case CUMEMCPYHTOA: return "cuMemcpyHtoA";
      case CUMEMCPYATOH: return "cuMemcpyAtoH";
      case CUMEMCPYATOA: return "cuMemcpyAtoA";
      case CUMEMCPY2D: return "cuMemcpy2D";
      case CUMEMCPY2DUNALIGNED: return "cuMemcpy2DUnaligned";
      case CUMEMCPY3D: return "cuMemcpy3D";
      case CUMEMCPY3DPEER: return "cuMemcpy3DPeer";
      case CUMEMCPYASYNC: return "cuMemcpyAsync";
      case CUMEMCPYPEERASYNC: return "cuMemcpyPeerAsync";
      case CUMEMCPYHTODASYNC: return "cuMemcpyHtoDAsync";
      case CUMEMCPYDTOHASYNC: return "cuMemcpyDtoHAsync";
      case CUMEMCPYDTODASYNC: return "cuMemcpyDtoDAsync";
      case CUMEMCPYHTOAASYNC: return "cuMemcpyHtoAAsync";
      case CUMEMCPYATOHASYNC: return "cuMemcpyAtoHAsync";
      case CUMEMCPY2DASYNC: return "cuMemcpy2DAsync";
      case CUMEMCPY3DASYNC: return "cuMemcpy3DAsync";
      case CUMEMCPY3DPEERASYNC: return "cuMemcpy3DPeerAsync";
      case CUMEMSETD8: return "cuMemsetD8";
      case CUMEMSETD16: return "cuMemsetD16";
      case CUMEMSETD32: return "cuMemsetD32";
      case CUMEMSETD2D8: return "cuMemsetD2D8";
      case CUMEMSETD2D16: return "cuMemsetD2D16";
      case CUMEMSETD2D32: return "cuMemsetD2D32";
      case CUMEMSETD8ASYNC: return "cuMemsetD8Async";
      case CUMEMSETD16ASYNC: return "cuMemsetD16Async";
      case CUMEMSETD32ASYNC: return "cuMemsetD32Async";
      case CUMEMSETD2D8ASYNC: return "cuMemsetD2D8Async";
      case CUMEMSETD2D16ASYNC: return "cuMemsetD2D16Async";
      case CUMEMSETD2D32ASYNC: return "cuMemsetD2D32Async";
      case CUARRAYCREATE: return "cuArrayCreate";
      case CUARRAYGETDESCRIPTOR: return "cuArrayGetDescriptor";
      case CUARRAYGETSPARSEPROPERTIES: return "cuArrayGetSparseProperties";
      case CUMIPMAPPEDARRAYGETSPARSEPROPERTIES: return "cuMipmappedArrayGetSparseProperties";
      case CUARRAYGETMEMORYREQUIREMENTS: return "cuArrayGetMemoryRequirements";
      case CUMIPMAPPEDARRAYGETMEMORYREQUIREMENTS: return "cuMipmappedArrayGetMemoryRequirements";
      case CUARRAYGETPLANE: return "cuArrayGetPlane";
      case CUARRAYDESTROY: return "cuArrayDestroy";
      case CUARRAY3DCREATE: return "cuArray3DCreate";
      case CUARRAY3DGETDESCRIPTOR: return "cuArray3DGetDescriptor";
      case CUMIPMAPPEDARRAYCREATE: return "cuMipmappedArrayCreate";
      case CUMIPMAPPEDARRAYGETLEVEL: return "cuMipmappedArrayGetLevel";
      case CUMIPMAPPEDARRAYDESTROY: return "cuMipmappedArrayDestroy";
      case CUMEMGETHANDLEFORADDRESSRANGE: return "cuMemGetHandleForAddressRange";
      case CUMEMADDRESSRESERVE: return "cuMemAddressReserve";
      case CUMEMADDRESSFREE: return "cuMemAddressFree";
      case CUMEMCREATE: return "cuMemCreate";
      case CUMEMRELEASE: return "cuMemRelease";
      case CUMEMMAP: return "cuMemMap";
      case CUMEMMAPARRAYASYNC: return "cuMemMapArrayAsync";
      case CUMEMUNMAP: return "cuMemUnmap";
      case CUMEMSETACCESS: return "cuMemSetAccess";
      case CUMEMGETACCESS: return "cuMemGetAccess";
      case CUMEMEXPORTTOSHAREABLEHANDLE: return "cuMemExportToShareableHandle";
      case CUMEMIMPORTFROMSHAREABLEHANDLE: return "cuMemImportFromShareableHandle";
      case CUMEMGETALLOCATIONGRANULARITY: return "cuMemGetAllocationGranularity";
      case CUMEMGETALLOCATIONPROPERTIESFROMHANDLE: return "cuMemGetAllocationPropertiesFromHandle";
      case CUMEMRETAINALLOCATIONHANDLE: return "cuMemRetainAllocationHandle";
      case CUMEMFREEASYNC: return "cuMemFreeAsync";
      case CUMEMALLOCASYNC: return "cuMemAllocAsync";
      case CUMEMPOOLTRIMTO: return "cuMemPoolTrimTo";
      case CUMEMPOOLSETATTRIBUTE: return "cuMemPoolSetAttribute";
      case CUMEMPOOLGETATTRIBUTE: return "cuMemPoolGetAttribute";
      case CUMEMPOOLSETACCESS: return "cuMemPoolSetAccess";
      case CUMEMPOOLGETACCESS: return "cuMemPoolGetAccess";
      case CUMEMPOOLCREATE: return "cuMemPoolCreate";
      case CUMEMPOOLDESTROY: return "cuMemPoolDestroy";
      case CUMEMALLOCFROMPOOLASYNC: return "cuMemAllocFromPoolAsync";
      case CUMEMPOOLEXPORTTOSHAREABLEHANDLE: return "cuMemPoolExportToShareableHandle";
      case CUMEMPOOLIMPORTFROMSHAREABLEHANDLE: return "cuMemPoolImportFromShareableHandle";
      case CUMEMPOOLEXPORTPOINTER: return "cuMemPoolExportPointer";
      case CUMEMPOOLIMPORTPOINTER: return "cuMemPoolImportPointer";
      case CUMULTICASTCREATE: return "cuMulticastCreate";
      case CUMULTICASTADDDEVICE: return "cuMulticastAddDevice";
      case CUMULTICASTBINDMEM: return "cuMulticastBindMem";
      case CUMULTICASTBINDADDR: return "cuMulticastBindAddr";
      case CUMULTICASTUNBIND: return "cuMulticastUnbind";
      case CUMULTICASTGETGRANULARITY: return "cuMulticastGetGranularity";
      case CUPOINTERGETATTRIBUTE: return "cuPointerGetAttribute";
      case CUMEMPREFETCHASYNC: return "cuMemPrefetchAsync";
      case CUMEMADVISE: return "cuMemAdvise";
      case CUMEMRANGEGETATTRIBUTE: return "cuMemRangeGetAttribute";
      case CUMEMRANGEGETATTRIBUTES: return "cuMemRangeGetAttributes";
      case CUPOINTERSETATTRIBUTE: return "cuPointerSetAttribute";
      case CUPOINTERGETATTRIBUTES: return "cuPointerGetAttributes";
      case CUSTREAMCREATE: return "cuStreamCreate";
      case CUSTREAMCREATEWITHPRIORITY: return "cuStreamCreateWithPriority";
      case CUSTREAMGETPRIORITY: return "cuStreamGetPriority";
      case CUSTREAMGETFLAGS: return "cuStreamGetFlags";
      case CUSTREAMGETID: return "cuStreamGetId";
      case CUSTREAMGETCTX: return "cuStreamGetCtx";
      case CUSTREAMWAITEVENT: return "cuStreamWaitEvent";
      case CUSTREAMADDCALLBACK: return "cuStreamAddCallback";
      case CUSTREAMBEGINCAPTURE: return "cuStreamBeginCapture";
      case CUTHREADEXCHANGESTREAMCAPTUREMODE: return "cuThreadExchangeStreamCaptureMode";
      case CUSTREAMENDCAPTURE: return "cuStreamEndCapture";
      case CUSTREAMISCAPTURING: return "cuStreamIsCapturing";
      case CUSTREAMGETCAPTUREINFO: return "cuStreamGetCaptureInfo";
      case CUSTREAMUPDATECAPTUREDEPENDENCIES: return "cuStreamUpdateCaptureDependencies";
      case CUSTREAMATTACHMEMASYNC: return "cuStreamAttachMemAsync";
      case CUSTREAMQUERY: return "cuStreamQuery";
      case CUSTREAMSYNCHRONIZE: return "cuStreamSynchronize";
      case CUSTREAMDESTROY: return "cuStreamDestroy";
      case CUSTREAMCOPYATTRIBUTES: return "cuStreamCopyAttributes";
      case CUSTREAMGETATTRIBUTE: return "cuStreamGetAttribute";
      case CUSTREAMSETATTRIBUTE: return "cuStreamSetAttribute";
      case CUEVENTCREATE: return "cuEventCreate";
      case CUEVENTRECORD: return "cuEventRecord";
      case CUEVENTRECORDWITHFLAGS: return "cuEventRecordWithFlags";
      case CUEVENTQUERY: return "cuEventQuery";
      case CUEVENTSYNCHRONIZE: return "cuEventSynchronize";
      case CUEVENTDESTROY: return "cuEventDestroy";
      case CUEVENTELAPSEDTIME: return "cuEventElapsedTime";
      case CUIMPORTEXTERNALMEMORY: return "cuImportExternalMemory";
      case CUEXTERNALMEMORYGETMAPPEDBUFFER: return "cuExternalMemoryGetMappedBuffer";
      case CUEXTERNALMEMORYGETMAPPEDMIPMAPPEDARRAY: return "cuExternalMemoryGetMappedMipmappedArray";
      case CUDESTROYEXTERNALMEMORY: return "cuDestroyExternalMemory";
      case CUIMPORTEXTERNALSEMAPHORE: return "cuImportExternalSemaphore";
      case CUSIGNALEXTERNALSEMAPHORESASYNC: return "cuSignalExternalSemaphoresAsync";
      case CUWAITEXTERNALSEMAPHORESASYNC: return "cuWaitExternalSemaphoresAsync";
      case CUDESTROYEXTERNALSEMAPHORE: return "cuDestroyExternalSemaphore";
      case CUSTREAMWAITVALUE32: return "cuStreamWaitValue32";
      case CUSTREAMWAITVALUE64: return "cuStreamWaitValue64";
      case CUSTREAMWRITEVALUE32: return "cuStreamWriteValue32";
      case CUSTREAMWRITEVALUE64: return "cuStreamWriteValue64";
      case CUSTREAMBATCHMEMOP: return "cuStreamBatchMemOp";
      case CUFUNCGETATTRIBUTE: return "cuFuncGetAttribute";
      case CUFUNCSETATTRIBUTE: return "cuFuncSetAttribute";
      case CUFUNCSETCACHECONFIG: return "cuFuncSetCacheConfig";
      case CUFUNCSETSHAREDMEMCONFIG: return "cuFuncSetSharedMemConfig";
      case CUFUNCGETMODULE: return "cuFuncGetModule";
      case CULAUNCHKERNEL: return "cuLaunchKernel";
      case CULAUNCHKERNELEX: return "cuLaunchKernelEx";
      case CULAUNCHCOOPERATIVEKERNEL: return "cuLaunchCooperativeKernel";
      case CULAUNCHCOOPERATIVEKERNELMULTIDEVICE: return "cuLaunchCooperativeKernelMultiDevice";
      case CULAUNCHHOSTFUNC: return "cuLaunchHostFunc";
      case CUFUNCSETBLOCKSHAPE: return "cuFuncSetBlockShape";
      case CUFUNCSETSHAREDSIZE: return "cuFuncSetSharedSize";
      case CUPARAMSETSIZE: return "cuParamSetSize";
      case CUPARAMSETI: return "cuParamSeti";
      case CUPARAMSETF: return "cuParamSetf";
      case CUPARAMSETV: return "cuParamSetv";
      case CULAUNCH: return "cuLaunch";
      case CULAUNCHGRID: return "cuLaunchGrid";
      case CULAUNCHGRIDASYNC: return "cuLaunchGridAsync";
      case CUPARAMSETTEXREF: return "cuParamSetTexRef";
      case CUGRAPHCREATE: return "cuGraphCreate";
      case CUGRAPHADDKERNELNODE: return "cuGraphAddKernelNode";
      case CUGRAPHKERNELNODEGETPARAMS: return "cuGraphKernelNodeGetParams";
      case CUGRAPHKERNELNODESETPARAMS: return "cuGraphKernelNodeSetParams";
      case CUGRAPHADDMEMCPYNODE: return "cuGraphAddMemcpyNode";
      case CUGRAPHMEMCPYNODEGETPARAMS: return "cuGraphMemcpyNodeGetParams";
      case CUGRAPHMEMCPYNODESETPARAMS: return "cuGraphMemcpyNodeSetParams";
      case CUGRAPHADDMEMSETNODE: return "cuGraphAddMemsetNode";
      case CUGRAPHMEMSETNODEGETPARAMS: return "cuGraphMemsetNodeGetParams";
      case CUGRAPHMEMSETNODESETPARAMS: return "cuGraphMemsetNodeSetParams";
      case CUGRAPHADDHOSTNODE: return "cuGraphAddHostNode";
      case CUGRAPHHOSTNODEGETPARAMS: return "cuGraphHostNodeGetParams";
      case CUGRAPHHOSTNODESETPARAMS: return "cuGraphHostNodeSetParams";
      case CUGRAPHADDCHILDGRAPHNODE: return "cuGraphAddChildGraphNode";
      case CUGRAPHCHILDGRAPHNODEGETGRAPH: return "cuGraphChildGraphNodeGetGraph";
      case CUGRAPHADDEMPTYNODE: return "cuGraphAddEmptyNode";
      case CUGRAPHADDEVENTRECORDNODE: return "cuGraphAddEventRecordNode";
      case CUGRAPHEVENTRECORDNODEGETEVENT: return "cuGraphEventRecordNodeGetEvent";
      case CUGRAPHEVENTRECORDNODESETEVENT: return "cuGraphEventRecordNodeSetEvent";
      case CUGRAPHADDEVENTWAITNODE: return "cuGraphAddEventWaitNode";
      case CUGRAPHEVENTWAITNODEGETEVENT: return "cuGraphEventWaitNodeGetEvent";
      case CUGRAPHEVENTWAITNODESETEVENT: return "cuGraphEventWaitNodeSetEvent";
      case CUGRAPHADDEXTERNALSEMAPHORESSIGNALNODE: return "cuGraphAddExternalSemaphoresSignalNode";
      case CUGRAPHEXTERNALSEMAPHORESSIGNALNODEGETPARAMS: return "cuGraphExternalSemaphoresSignalNodeGetParams";
      case CUGRAPHEXTERNALSEMAPHORESSIGNALNODESETPARAMS: return "cuGraphExternalSemaphoresSignalNodeSetParams";
      case CUGRAPHADDEXTERNALSEMAPHORESWAITNODE: return "cuGraphAddExternalSemaphoresWaitNode";
      case CUGRAPHEXTERNALSEMAPHORESWAITNODEGETPARAMS: return "cuGraphExternalSemaphoresWaitNodeGetParams";
      case CUGRAPHEXTERNALSEMAPHORESWAITNODESETPARAMS: return "cuGraphExternalSemaphoresWaitNodeSetParams";
      case CUGRAPHADDBATCHMEMOPNODE: return "cuGraphAddBatchMemOpNode";
      case CUGRAPHBATCHMEMOPNODEGETPARAMS: return "cuGraphBatchMemOpNodeGetParams";
      case CUGRAPHBATCHMEMOPNODESETPARAMS: return "cuGraphBatchMemOpNodeSetParams";
      case CUGRAPHEXECBATCHMEMOPNODESETPARAMS: return "cuGraphExecBatchMemOpNodeSetParams";
      case CUGRAPHADDMEMALLOCNODE: return "cuGraphAddMemAllocNode";
      case CUGRAPHMEMALLOCNODEGETPARAMS: return "cuGraphMemAllocNodeGetParams";
      case CUGRAPHADDMEMFREENODE: return "cuGraphAddMemFreeNode";
      case CUGRAPHMEMFREENODEGETPARAMS: return "cuGraphMemFreeNodeGetParams";
      case CUDEVICEGRAPHMEMTRIM: return "cuDeviceGraphMemTrim";
      case CUDEVICEGETGRAPHMEMATTRIBUTE: return "cuDeviceGetGraphMemAttribute";
      case CUDEVICESETGRAPHMEMATTRIBUTE: return "cuDeviceSetGraphMemAttribute";
      case CUGRAPHCLONE: return "cuGraphClone";
      case CUGRAPHNODEFINDINCLONE: return "cuGraphNodeFindInClone";
      case CUGRAPHNODEGETTYPE: return "cuGraphNodeGetType";
      case CUGRAPHGETNODES: return "cuGraphGetNodes";
      case CUGRAPHGETROOTNODES: return "cuGraphGetRootNodes";
      case CUGRAPHGETEDGES: return "cuGraphGetEdges";
      case CUGRAPHNODEGETDEPENDENCIES: return "cuGraphNodeGetDependencies";
      case CUGRAPHNODEGETDEPENDENTNODES: return "cuGraphNodeGetDependentNodes";
      case CUGRAPHADDDEPENDENCIES: return "cuGraphAddDependencies";
      case CUGRAPHREMOVEDEPENDENCIES: return "cuGraphRemoveDependencies";
      case CUGRAPHDESTROYNODE: return "cuGraphDestroyNode";
      case CUGRAPHINSTANTIATE: return "cuGraphInstantiate";
      case CUGRAPHINSTANTIATEWITHPARAMS: return "cuGraphInstantiateWithParams";
      case CUGRAPHEXECGETFLAGS: return "cuGraphExecGetFlags";
      case CUGRAPHEXECKERNELNODESETPARAMS: return "cuGraphExecKernelNodeSetParams";
      case CUGRAPHEXECMEMCPYNODESETPARAMS: return "cuGraphExecMemcpyNodeSetParams";
      case CUGRAPHEXECMEMSETNODESETPARAMS: return "cuGraphExecMemsetNodeSetParams";
      case CUGRAPHEXECHOSTNODESETPARAMS: return "cuGraphExecHostNodeSetParams";
      case CUGRAPHEXECCHILDGRAPHNODESETPARAMS: return "cuGraphExecChildGraphNodeSetParams";
      case CUGRAPHEXECEVENTRECORDNODESETEVENT: return "cuGraphExecEventRecordNodeSetEvent";
      case CUGRAPHEXECEVENTWAITNODESETEVENT: return "cuGraphExecEventWaitNodeSetEvent";
      case CUGRAPHEXECEXTERNALSEMAPHORESSIGNALNODESETPARAMS: return "cuGraphExecExternalSemaphoresSignalNodeSetParams";
      case CUGRAPHEXECEXTERNALSEMAPHORESWAITNODESETPARAMS: return "cuGraphExecExternalSemaphoresWaitNodeSetParams";
      case CUGRAPHNODESETENABLED: return "cuGraphNodeSetEnabled";
      case CUGRAPHNODEGETENABLED: return "cuGraphNodeGetEnabled";
      case CUGRAPHUPLOAD: return "cuGraphUpload";
      case CUGRAPHLAUNCH: return "cuGraphLaunch";
      case CUGRAPHEXECDESTROY: return "cuGraphExecDestroy";
      case CUGRAPHDESTROY: return "cuGraphDestroy";
      case CUGRAPHEXECUPDATE: return "cuGraphExecUpdate";
      case CUGRAPHKERNELNODECOPYATTRIBUTES: return "cuGraphKernelNodeCopyAttributes";
      case CUGRAPHKERNELNODEGETATTRIBUTE: return "cuGraphKernelNodeGetAttribute";
      case CUGRAPHKERNELNODESETATTRIBUTE: return "cuGraphKernelNodeSetAttribute";
      case CUGRAPHDEBUGDOTPRINT: return "cuGraphDebugDotPrint";
      case CUUSEROBJECTCREATE: return "cuUserObjectCreate";
      case CUUSEROBJECTRETAIN: return "cuUserObjectRetain";
      case CUUSEROBJECTRELEASE: return "cuUserObjectRelease";
      case CUGRAPHRETAINUSEROBJECT: return "cuGraphRetainUserObject";
      case CUGRAPHRELEASEUSEROBJECT: return "cuGraphReleaseUserObject";
      case CUOCCUPANCYMAXACTIVEBLOCKSPERMULTIPROCESSOR: return "cuOccupancyMaxActiveBlocksPerMultiprocessor";
      case CUOCCUPANCYMAXACTIVEBLOCKSPERMULTIPROCESSORWITHFLAGS: return "cuOccupancyMaxActiveBlocksPerMultiprocessorWithFlags";
      case CUOCCUPANCYMAXPOTENTIALBLOCKSIZE: return "cuOccupancyMaxPotentialBlockSize";
      case CUOCCUPANCYMAXPOTENTIALBLOCKSIZEWITHFLAGS: return "cuOccupancyMaxPotentialBlockSizeWithFlags";
      case CUOCCUPANCYAVAILABLEDYNAMICSMEMPERBLOCK: return "cuOccupancyAvailableDynamicSMemPerBlock";
      case CUOCCUPANCYMAXPOTENTIALCLUSTERSIZE: return "cuOccupancyMaxPotentialClusterSize";
      case CUOCCUPANCYMAXACTIVECLUSTERS: return "cuOccupancyMaxActiveClusters";
      case CUTEXREFSETARRAY: return "cuTexRefSetArray";
      case CUTEXREFSETMIPMAPPEDARRAY: return "cuTexRefSetMipmappedArray";
      case CUTEXREFSETADDRESS: return "cuTexRefSetAddress";
      case CUTEXREFSETADDRESS2D: return "cuTexRefSetAddress2D";
      case CUTEXREFSETFORMAT: return "cuTexRefSetFormat";
      case CUTEXREFSETADDRESSMODE: return "cuTexRefSetAddressMode";
      case CUTEXREFSETFILTERMODE: return "cuTexRefSetFilterMode";
      case CUTEXREFSETMIPMAPFILTERMODE: return "cuTexRefSetMipmapFilterMode";
      case CUTEXREFSETMIPMAPLEVELBIAS: return "cuTexRefSetMipmapLevelBias";
      case CUTEXREFSETMIPMAPLEVELCLAMP: return "cuTexRefSetMipmapLevelClamp";
      case CUTEXREFSETMAXANISOTROPY: return "cuTexRefSetMaxAnisotropy";
      case CUTEXREFSETBORDERCOLOR: return "cuTexRefSetBorderColor";
      case CUTEXREFSETFLAGS: return "cuTexRefSetFlags";
      case CUTEXREFGETADDRESS: return "cuTexRefGetAddress";
      case CUTEXREFGETARRAY: return "cuTexRefGetArray";
      case CUTEXREFGETMIPMAPPEDARRAY: return "cuTexRefGetMipmappedArray";
      case CUTEXREFGETADDRESSMODE: return "cuTexRefGetAddressMode";
      case CUTEXREFGETFILTERMODE: return "cuTexRefGetFilterMode";
      case CUTEXREFGETFORMAT: return "cuTexRefGetFormat";
      case CUTEXREFGETMIPMAPFILTERMODE: return "cuTexRefGetMipmapFilterMode";
      case CUTEXREFGETMIPMAPLEVELBIAS: return "cuTexRefGetMipmapLevelBias";
      case CUTEXREFGETMIPMAPLEVELCLAMP: return "cuTexRefGetMipmapLevelClamp";
      case CUTEXREFGETMAXANISOTROPY: return "cuTexRefGetMaxAnisotropy";
      case CUTEXREFGETBORDERCOLOR: return "cuTexRefGetBorderColor";
      case CUTEXREFGETFLAGS: return "cuTexRefGetFlags";
      case CUTEXREFCREATE: return "cuTexRefCreate";
      case CUTEXREFDESTROY: return "cuTexRefDestroy";
      case CUSURFREFSETARRAY: return "cuSurfRefSetArray";
      case CUSURFREFGETARRAY: return "cuSurfRefGetArray";
      case CUTEXOBJECTCREATE: return "cuTexObjectCreate";
      case CUTEXOBJECTDESTROY: return "cuTexObjectDestroy";
      case CUTEXOBJECTGETRESOURCEDESC: return "cuTexObjectGetResourceDesc";
      case CUTEXOBJECTGETTEXTUREDESC: return "cuTexObjectGetTextureDesc";
      case CUTEXOBJECTGETRESOURCEVIEWDESC: return "cuTexObjectGetResourceViewDesc";
      case CUSURFOBJECTCREATE: return "cuSurfObjectCreate";
      case CUSURFOBJECTDESTROY: return "cuSurfObjectDestroy";
      case CUSURFOBJECTGETRESOURCEDESC: return "cuSurfObjectGetResourceDesc";
      case CUTENSORMAPENCODETILED: return "cuTensorMapEncodeTiled";
      case CUTENSORMAPENCODEIM2COL: return "cuTensorMapEncodeIm2col";
      case CUTENSORMAPREPLACEADDRESS: return "cuTensorMapReplaceAddress";
      case CUDEVICECANACCESSPEER: return "cuDeviceCanAccessPeer";
      case CUCTXENABLEPEERACCESS: return "cuCtxEnablePeerAccess";
      case CUCTXDISABLEPEERACCESS: return "cuCtxDisablePeerAccess";
      case CUDEVICEGETP2PATTRIBUTE: return "cuDeviceGetP2PAttribute";
      case CUGRAPHICSUNREGISTERRESOURCE: return "cuGraphicsUnregisterResource";
      case CUGRAPHICSSUBRESOURCEGETMAPPEDARRAY: return "cuGraphicsSubResourceGetMappedArray";
      case CUGRAPHICSRESOURCEGETMAPPEDMIPMAPPEDARRAY: return "cuGraphicsResourceGetMappedMipmappedArray";
      case CUGRAPHICSRESOURCEGETMAPPEDPOINTER: return "cuGraphicsResourceGetMappedPointer";
      case CUGRAPHICSRESOURCESETMAPFLAGS: return "cuGraphicsResourceSetMapFlags";
      case CUGRAPHICSMAPRESOURCES: return "cuGraphicsMapResources";
      case CUGRAPHICSUNMAPRESOURCES: return "cuGraphicsUnmapResources";
      case CUGETPROCADDRESS: return "cuGetProcAddress";
      case CUCOREDUMPGETATTRIBUTE: return "cuCoredumpGetAttribute";
      case CUCOREDUMPGETATTRIBUTEGLOBAL: return "cuCoredumpGetAttributeGlobal";
      case CUCOREDUMPSETATTRIBUTE: return "cuCoredumpSetAttribute";
      case CUCOREDUMPSETATTRIBUTEGLOBAL: return "cuCoredumpSetAttributeGlobal";
      case CUGETEXPORTTABLE: return "cuGetExportTable";
      default: return nullptr;
    }
  }

public:
  Cuda(uint32_t version, uint64_t pid, uint64_t tid);
  ~Cuda();
};

#endif