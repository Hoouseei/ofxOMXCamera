/*
 *  BaseEngine.h
 *
 *  Created by jason van cleave on 2/10/14.
 *  Copyright 2014 jasonvancleave.com. All rights reserved.
 *
 */

#pragma once

#include "ofMain.h"
#include "OMX_Maps.h"
#include "OMXCameraSettings.h"

class RecordingListener
{
public:
    virtual void onRecordingComplete(string filePath)=0;
};

class BaseEngine
{
public:
	BaseEngine();
    virtual ~BaseEngine(){};

	virtual void setup(OMXCameraSettings&, RecordingListener*) = 0;
    virtual int getFrameCounter() = 0;
	OMXCameraSettings& getSettings();
    void stopRecording();
	OMX_HANDLETYPE camera;
	bool isOpen;
    bool isRecording;
    RecordingListener* recordingListener;
protected:
	
    OMXCameraSettings settings;
	void configureCameraResolution();
	void configureEncoder();
	
	OMX_HANDLETYPE splitter;
	OMX_HANDLETYPE encoder;
	OMX_HANDLETYPE render;
	
	
	bool didWriteFile;
	
	int recordingBitRate;
	float numMBps;
	
	bool stopRequested;
	bool isStopping;
	
	void writeFile();
	
	ofBuffer recordingFileBuffer;
	OMX_BUFFERHEADERTYPE* encoderOutputBuffer;
	
	int recordedFrameCounter;
	
	static OMX_ERRORTYPE 
    splitterEventHandlerCallback(OMX_HANDLETYPE, 
                                 OMX_PTR, 
                                 OMX_EVENTTYPE, 
                                 OMX_U32, 
                                 OMX_U32, OMX_PTR){return OMX_ErrorNone;};

	static OMX_ERRORTYPE 
    encoderEventHandlerCallback(OMX_HANDLETYPE, 
                                OMX_PTR, 
                                OMX_EVENTTYPE, 
                                OMX_U32, OMX_U32, 
                                OMX_PTR){return OMX_ErrorNone;};
	static OMX_ERRORTYPE 
    encoderEmptyBufferDone(OMX_IN OMX_HANDLETYPE, 
                           OMX_IN OMX_PTR, 
                           OMX_IN OMX_BUFFERHEADERTYPE*){return OMX_ErrorNone;};
    
    
    static OMX_ERRORTYPE 
    encoderFillBufferDone(OMX_IN OMX_HANDLETYPE encoder,
                          OMX_IN OMX_PTR engine,
                          OMX_IN OMX_BUFFERHEADERTYPE* encoderOutputBuffer);
    
	
	static OMX_ERRORTYPE 
    renderEventHandlerCallback(OMX_HANDLETYPE, 
                               OMX_PTR, 
                               OMX_EVENTTYPE, 
                               OMX_U32, 
                               OMX_U32, 
                               OMX_PTR){return OMX_ErrorNone;};
	static OMX_ERRORTYPE 
    renderEmptyBufferDone(OMX_IN OMX_HANDLETYPE, 
                          OMX_IN OMX_PTR, 
                          OMX_IN OMX_BUFFERHEADERTYPE*){return OMX_ErrorNone;};
    
	static OMX_ERRORTYPE 
    renderFillBufferDone(OMX_IN OMX_HANDLETYPE, 
                         OMX_IN OMX_PTR, 
                         OMX_IN OMX_BUFFERHEADERTYPE*){return OMX_ErrorNone;};
	
};
