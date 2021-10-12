#define CINTERFACE

#include <stdio.h>
#include <math.h>
#include <windows.h>
#include <windowsx.h>
#include <mmsystem.h>
#include <dsound.h>

#define DSBCAPS_CTRLDEFAULT DSBCAPS_CTRLPAN | DSBCAPS_CTRLVOLUME | DSBCAPS_CTRLFREQUENCY

#define DBFACTOR 1000.0
#define lin2log(v) ((-log(v)*DBFACTOR/log(0.5)) > -10000 ?(LONG) (-log(v)*DBFACTOR/log(0.5)) : -10000)

#define debug 0
#define DEBUG_CODE(code) if (debug) { code };

IDirectSoundBuffer *DSLoadSoundBufferMem(BYTE *lpSound);
BOOL DSParseWaveResource(void* pvRes, WAVEFORMATEX **ppWaveHeader, BYTE** ppbWaveData, DWORD *pcbWaveSize);
BOOL DSFillSoundBuffer(IDirectSoundBuffer* s,BYTE *pbWaveData, DWORD cbWaveSize);


LPDIRECTSOUND DSound = NULL;
IDirectSoundBuffer *Primary=NULL;

/******** init and exit ***********/

int SND_Init(HWND hwnd) {
  int attemps=10,n;
  DSBUFFERDESC dsBD;
  
  DEBUG_CODE(fprintf(stdout,"sndinit on hwnd:%d\n",hwnd);)
  ZeroMemory(&dsBD,sizeof(DSBUFFERDESC));
  dsBD.dwSize=sizeof(dsBD);
  dsBD.dwFlags=DSBCAPS_PRIMARYBUFFER;
  while (DirectSoundCreate(NULL,&DSound,NULL)!=DS_OK) {
    attemps--;
    if (!attemps) {
      DSound=NULL;
      return 0;
    }
    Sleep(100);
  }
  DSound->lpVtbl->SetCooperativeLevel(DSound,hwnd,DSSCL_NORMAL);
  if (IDirectSound_CreateSoundBuffer(DSound,&dsBD,&Primary,NULL)!=DS_OK) Primary=NULL;
  else IDirectSoundBuffer_Play(Primary,0,0,0);
  return 1;
}

void SND_Exit() {
  if (Primary) IDirectSound_Release(Primary); Primary=NULL;
  if (DSound) DSound->lpVtbl->Release(DSound); DSound=NULL;
}

/* BETA utility functions, ie. COM wrappers */

int SoundBufPlay (LPDIRECTSOUNDBUFFER buf,INT loop) {
  DEBUG_CODE(fprintf(stdout,"play on %d\n",(int)buf);)
  if (loop) 
    return buf->lpVtbl->Play(buf,0,0,DSBPLAY_LOOPING);
  else
    return buf->lpVtbl->Play(buf,0,0,0);
}


void SoundBufStop (LPDIRECTSOUNDBUFFER buf)
{
  DEBUG_CODE(fprintf(stdout,"stop on %d\n",(int)buf);)
  buf->lpVtbl->Stop(buf);
}

void SoundBufVol (LPDIRECTSOUNDBUFFER buf,INT vol) {
  DEBUG_CODE(fprintf(stdout,"Vol on %d\n",(int)buf);)
  buf->lpVtbl->SetVolume(buf,lin2log((float)vol/100.0));
}

int SoundBufGetVol (LPDIRECTSOUNDBUFFER buf) {
  long vol=0;
  DEBUG_CODE(fprintf(stdout,"GetVol on %d\n",(int)buf););
  fprintf(stdout,"GetVol not supportet!");
  return vol;
}

char SoundBufIsPlaying (LPDIRECTSOUNDBUFFER buf)
{ 
  unsigned long status;

  DEBUG_CODE(fprintf(stdout,"isplaying on %d\n",(int)buf);)
  buf->lpVtbl->GetStatus(buf,&status);
  if (status&DSBSTATUS_PLAYING) 
  {
    return 1;
  } else {
    return 0;
  };
}

char SoundBufIsLooping (LPDIRECTSOUNDBUFFER buf)
{ 
  unsigned long status;

  DEBUG_CODE(fprintf(stdout,"islooping on %d\n",(int)buf);)
  buf->lpVtbl->GetStatus(buf,&status);
  if (status&DSBSTATUS_LOOPING) 
  {
    return 1;
  } else {
    return 0;
  };
}


void SoundBufSetPos(LPDIRECTSOUNDBUFFER buf,int pos)
{
  buf->lpVtbl->SetCurrentPosition(buf,pos);
}

void SoundBufGetPos(LPDIRECTSOUNDBUFFER buf,long *playpos,long* writepos)
{
  buf->lpVtbl->GetCurrentPosition(buf,playpos,writepos);
}

void SoundBufSetFrq(LPDIRECTSOUNDBUFFER buf,int frq)
{
  buf->lpVtbl->SetFrequency(buf,frq);
}

int SoundBufGetFrq(LPDIRECTSOUNDBUFFER buf)
{ long frq;
  buf->lpVtbl->GetFrequency(buf,&frq);
  return frq;
}

#define DSBPAN_RIGHT 10000

void SoundBufPan (LPDIRECTSOUNDBUFFER buf,INT pan) {
  DEBUG_CODE(fprintf(stdout,"pan on %d\n",(int)buf);)
  buf->lpVtbl->SetPan(buf,pan*DSBPAN_RIGHT/100);
  DEBUG_CODE(fprintf(stdout,"pan:%d",pan*DSBPAN_RIGHT/100);)
}

int SoundBufGetPan (LPDIRECTSOUNDBUFFER buf) {
  long pan;

  buf->lpVtbl->GetPan(buf,&pan);
  return (pan*100)/DSBPAN_RIGHT;
}


/*********** SND_LOAD ********/

LPDIRECTSOUNDBUFFER SND_Load(char * filename) {
  LPDIRECTSOUNDBUFFER buf;
  unsigned char * membuf=NULL;
  int num,size,n;
  unsigned long f;
  FILE *v;

  if (!DSound) {
    DEBUG_CODE(fprintf(stdout,"load returning null\n"););
    return NULL;
  };
  if (v=fopen(filename,"rb")) {
    fseek(v,0,SEEK_END); size=ftell(v); fseek(v,0,SEEK_SET);
    if (membuf=(unsigned char*)malloc(size)) fread(membuf,size,1,v);
    fclose(v);
  } else {
    DEBUG_CODE(fprintf(stdout,"load.2 returning null\n");)
    return NULL;
  };
  if (!membuf) {
    DEBUG_CODE(fprintf(stdout,"load.2 returning null\n");)
    return NULL;
  };

  buf=DSLoadSoundBufferMem(membuf); free(membuf);
  if(!buf) {
    DEBUG_CODE(fprintf(stdout,"load.4 returning null\n"););
    return NULL;
  };

  return buf;
}

int lastsizecopied=0;

BOOL DSFillSoundBuffer(IDirectSoundBuffer* s,BYTE *pbWaveData, DWORD cbWaveSize)
{
  if (s && pbWaveData && cbWaveSize) {
    LPVOID pMem1,pMem2;
    DWORD dwSize1,dwSize2;
    if (IDirectSoundBuffer_Lock(s,0,cbWaveSize,&pMem1,&dwSize1,&pMem2,&dwSize2,0)==DS_OK) {
      lastsizecopied=dwSize1;
      CopyMemory(pMem1,pbWaveData,dwSize1);
      if (dwSize2) CopyMemory(pMem2,pbWaveData+dwSize1,dwSize2);
      IDirectSoundBuffer_Unlock(s,pMem1,dwSize1,pMem2,dwSize2);
      return TRUE;
    }
  }
  return FALSE;
}

BOOL DSParseWaveResource(void* pvRes, WAVEFORMATEX **ppWaveHeader, BYTE** ppbWaveData, DWORD *pcbWaveSize) {
  DWORD *pdw,*pdwEnd,dwRiff,dwType,dwLength;

  if (ppWaveHeader) *ppWaveHeader=NULL;
  if (ppbWaveData) *ppbWaveData=NULL;
  if (pcbWaveSize) *pcbWaveSize=0;
  pdw=(DWORD*)pvRes; dwRiff=*pdw++;dwLength= *pdw++;dwType=*pdw++;
  if(dwRiff!=mmioFOURCC('R','I','F','F')) return FALSE;
  if(dwType!=mmioFOURCC('W','A','V','E')) return FALSE;
  pdwEnd = (DWORD*)((BYTE*)pdw + dwLength-4);
  while(pdw<pdwEnd) {
    dwType = *pdw++;
    dwLength = *pdw++;
    switch (dwType) {
    case mmioFOURCC('f','m','t',' '):
      if(ppWaveHeader && !*ppWaveHeader) {
	if(dwLength<sizeof(WAVEFORMAT)) return FALSE;
	*ppWaveHeader = (WAVEFORMATEX*)pdw;
	if ((!ppbWaveData || *ppbWaveData) && (!pcbWaveSize && *pcbWaveSize)) 
	  return TRUE;
      }
      break;
    case mmioFOURCC('d','a','t','a'):
      if ((ppbWaveData && !*ppbWaveData) || (pcbWaveSize && !*pcbWaveSize)) {
	if (ppbWaveData) *ppbWaveData = (LPBYTE) pdw;
	if (pcbWaveSize) *pcbWaveSize = dwLength;
	if (!ppWaveHeader || *ppWaveHeader) return TRUE;
      }
      break;
    }
    pdw = (DWORD *)((BYTE *)pdw + ((dwLength+1)&~1));
  }
  return FALSE;
}

IDirectSoundBuffer *DSLoadSoundBufferMem(BYTE *lpSound) {
  IDirectSoundBuffer* s = NULL;
  DSBUFFERDESC dsBD={0};
  BYTE *pbWaveData;
  DSParseWaveResource(lpSound, &dsBD.lpwfxFormat, &pbWaveData, &dsBD.dwBufferBytes);
  dsBD.dwSize = sizeof(dsBD);
  dsBD.dwFlags = DSBCAPS_CTRLDEFAULT;
  if (IDirectSound_CreateSoundBuffer(DSound,&dsBD,&s,NULL)!=DS_OK) return NULL;
  if (DSFillSoundBuffer(s,pbWaveData,dsBD.dwBufferBytes)) return s;
  IDirectSoundBuffer_Release(s);
  return NULL;
}
							    
