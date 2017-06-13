#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h> 

#include "../include/cae/cae.h"


// 唤醒回调函数
void ivw_cbf(short angle, short channel, float power, short CMScore, short beam, void *userData)
{
	printf("ivw_cbf | angle:%d channel:%d power:%f CMScore:%d beam:%d", angle, channel, power, CMScore, beam);
}

// 音频回调函数
void audio_cbf(const void *audioData, unsigned int audioLen, int param1, const void *param2, void *userData)
{
	printf("audio_cbf | audioLen:%d", audioLen);
}

static char* getAbsolutePath(char* path) {
#if 0
    if(path == NULL) {
	return NULL;
    } else {
	File f = new File(path);
	if(f.exists() && f.isFile()) {
	    long length = f.length();
	    long offset = 0L;
	    return "fo|" + path + "|" + offset + "|" + length;
	} else {
	    return null;
	}
    }
#endif
	return "fo|../res/dingdong.jet|0|815696";
}

	//typedef int (*CAE_FUNC)(CAE_HANDLE *cae, const char* resPath, cae_ivw_fn ivwCb, cae_audio_fn audioCb, const char*param, void *userData);

	typedef int (*CAE_FUNC)(...);
int loadCAE()
{
	
}

int main()
{
	const char* resPathChar = "fo|./dingdong.jet|0|815696";
	CAE_HANDLE handle;

	CAE_FUNC CAENew, CAEAudioWrite, CAEResetEng, CAESetRealBeam, CAEDestroy, CAEExtract16K;
	printf("Hello CAE !\n");

	printf("CAENew | res path:%s", resPathChar);

	void * handle1;
	handle1 = dlopen ("libcae.so", RTLD_NOW); 
	*(void **)(&CAENew) = dlsym(handle1, "CAENew");  
	*(void **)(&CAEAudioWrite) = dlsym(handle1, "CAEAudioWrite");  
	*(void **)(&CAEResetEng) = dlsym(handle1, "CAEResetEng");  
	*(void **)(&CAESetRealBeam) = dlsym(handle1, "CAESetRealBeam");  
	*(void **)(&CAEDestroy) = dlsym(handle1, "CAEDestroy");  
	*(void **)(&CAEExtract16K) = dlsym(handle1, "CAEExtract16K");

	int ret = CAENew(&handle, resPathChar, ivw_cbf, audio_cbf, NULL, NULL);

	printf("CAENew | cae handle:%p", handle);

	return ret;

}
