#ifndef KANZI_H
#define KANZI_H

#include <stdio.h>

namespace KANZI
{
	typedef enum {
		SettingCar = 1, SettingChair, Radio,MediaVideo,MediaMusic,SettingCC
	} idxUI;

	typedef enum {
		LightNone = 1,LightDadeng,LightWudeng
	}LightState;

	typedef enum {
		None = 1,White,Green
	}CCState;

	typedef enum {
		NormalStyle = 1,ClassicStyle,SportStyle
	}UIStyle;

        typedef struct{
	        char musicPath[100];
	        char videoPath[100];
        }FILEPATH;

	typedef void (*PTRSETUI)(const idxUI idx);
	typedef idxUI (*PTRGETUI)(void);

	typedef  void(*PTRToggleFunc)(void);

	typedef void(*PTRSetLightFunc)(LightState state);

	typedef void(*PTRSetCCFunc)(CCState state);

	typedef void(*PTRSetStyleFunc)(UIStyle style);
	//设置座椅前后距离,范围：-9 - 16.5
	typedef void(*PTRSetChairGoBackValue)(float value);
	//设置座椅上下距离,范围：-2.3 - 4.4
	typedef void(*PTRSetChairUpDownValue)(float val);
	//设置座椅向后旋转角度,范围：-20 - 22
	typedef void(*PTRSetChairRotateValue)(float val);

	typedef void(*PTRSetAMFMVal)(float val);

	typedef void(*PTRReadFileList)(FILEPATH filepath);

	typedef struct
	{
		PTRSETUI pSetUI;
		PTRGETUI pGetUI;
		//toggle front left door
		PTRToggleFunc pSettingToggleFL;
		//toggle front right door
		PTRToggleFunc pSettingToggleFR;
		//toggle rear left door
		PTRToggleFunc pSettingToggleRL;
		//toggle rear right door
		PTRToggleFunc pSettingToggleRR;

		//Radio
		PTRToggleFunc pRadioToggleAMFM;

		//toggle yushua
		PTRToggleFunc pSettingToggleYushua;

		//setting module
		PTRToggleFunc pSettingToggleWindowFL;
		PTRToggleFunc pSettingToggleWindowFR;
		PTRToggleFunc pSettingToggleWindowRL;
		PTRToggleFunc pSettingToggleWindowRR;
		PTRToggleFunc pSettingToggleBackDoor;
		PTRSetLightFunc pSetCarLight;
		PTRSetStyleFunc pSetUIStyle;
		PTRSetChairGoBackValue pSetChairGoBackFunc;
		PTRSetChairUpDownValue pSetChairUpDownFunc;
		PTRSetChairRotateValue pSetChairRotateFunc;
		PTRSetAMFMVal pSetAMFMFunc;
		PTRSetCCFunc pSetCCFunc;
		PTRToggleFunc pMiscToggleONOFF;
                PTRReadFileList pReadFileList;
	}Kanzi_CB;
	/*运行通信消息循环*/
	void runIPCLoop(Kanzi_CB *callbacks);

	/*通知一个视频播放媒体封面的点击事件*/
	void on_media_video_clicked(const int idx);
	/*通知一个视频播放媒体封面的焦点事件*/
	void on_media_video_focus(const int idx);

	void on_media_music_clicked(const int idx);
	void on_media_music_focus(const int idx);

	typedef enum {CAR_DOOR_FRONT_LEFT = 1,CAR_DOOR_RONT_RIGHT,CAR_DOOR_BACK_LEFT,CAR_DOOR_BACK_RIGHT,CAR_LIGHT,CAR_FOG_LIGHT,CAR_BACK_DOOR}VehicleSection;

	void on_vehicle_clicked(VehicleSection section, bool opened);

}
#endif



