#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h> 
#include <unistd.h> 

#include "../include/cae/cae.h"
#include "../include/tinyalsa/asoundlib.h"

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

	char *resPath = "fo|./dingdong.jet|0|815696";
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
	return resPath;
}

	typedef int (*CAE_FUNC)(...);
	//CAE_FUNC CAENew, CAEAudioWrite, CAEResetEng, CAESetRealBeam, CAEDestroy, CAEExtract16K;
	CAE_HANDLE CAEHandler;

static int loadCAE()
{
	
}
/*
unsigned int capture_sample(FILE *file)
{
    struct pcm_config config;
    struct pcm *pcm;
    char *buffer;
    unsigned int size;
    unsigned int frames_read;
    unsigned int total_frames_read;
    unsigned int bytes_per_frame;
    int cae_ret;

    memset(&config, 0, sizeof(config));
    config.channels = 2;
    config.rate = 96000;
    config.period_size = 1536;
    config.period_count = 8;
    config.format = PCM_FORMAT_S16_LE;
    config.start_threshold = 0;
    config.stop_threshold = 0;
    config.silence_threshold = 0;

    pcm = pcm_open(1, 0, PCM_IN, &config);
    if (!pcm || !pcm_is_ready(pcm)) {
        printf("Unable to open PCM device (%s)\n",
                pcm_get_error(pcm));
        return 0;
    }

    size = pcm_frames_to_bytes(pcm, pcm_get_buffer_size(pcm));
    printf("PCM buffer size %d Bytes \n", size);
    buffer = (char *)malloc(size);
    if (!buffer) {
        printf("Unable to allocate %u bytes\n", size);
        pcm_close(pcm);
        return 0;
    }

    bytes_per_frame = pcm_frames_to_bytes(pcm, 1);
    total_frames_read = 0;
    frames_read = 0;
    while (1) {
        frames_read = pcm_readi(pcm, buffer, pcm_get_buffer_size(pcm));
        total_frames_read += frames_read;
        printf("pcm read %d bytes\n",bytes_per_frame * frames_read);
        
        if (fwrite(buffer, bytes_per_frame, frames_read, file) != frames_read) {
            printf("Error capturing sample\n");
            break;
        }
        //cae_ret=CAEAudioWrite(CAEHandler, buffer, size);
        //printf("CAEAudioWrite ret %d\n", cae_ret);
    }

    free(buffer);
    pcm_close(pcm);
    return total_frames_read;
}*/
#if 0
void caewrite_test()
{
	FILE *f1;
	int ret,i,size;
	size =49152;
	f1 = fopen("/sdcard/raw.pcm", "rb");

	char *buf = (char *)malloc(size);

	for (i=0;i<100;i++) {
		fread(buf,size,1,f1);
		usleep(10000);
        	ret=CAEAudioWrite(CAEHandler, buf, size);
        	printf("CAEAudioWrite ret %d\n", ret);
       }
}
#endif
int main()
{
	const char* resPathChar = "fo|./dingdong.jet|0|815696";
	
	FILE * file;

	printf("Hello CAE !\n");

	printf("CAENew | res path:%s", resPathChar);

	void * handle1;
	handle1 = dlopen ("libcae.so", RTLD_NOW); 
	//CAENew = dlsym(handle1, "CAENew");  
	//CAEAudioWrite = dlsym(handle1, "CAEAudioWrite");  


	int ret = CAENew(&CAEHandler, resPathChar, ivw_cbf, audio_cbf, NULL, NULL);
	//caewrite_test();
	printf("CAENew | cae handle:%p\n=============\n", CAEHandler);
	 FILE *f1;
	 int caeret,i,size;
	 size =10240;
	 f1 = fopen("/sdcard/raw.pcm", "rb");
	
	 char *buf = (char *)malloc(size);
	
	 for (i=0;i<10000;i++) {
		 fread(buf,size,1,f1);
		 usleep(10000);
		 caeret=CAEAudioWrite(CAEHandler, buf, size);
		 printf("# i %d,CAEAudioWrite ret %d\n",i, caeret);
	}

	//file = fopen("/sdcard/raw.pcm", "wb");
	//capture_sample(file);
	return ret;

}
