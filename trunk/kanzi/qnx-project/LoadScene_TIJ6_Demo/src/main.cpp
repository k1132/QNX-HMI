/**
* \file
*
* This is a skeleton for new application.
*/
#include <application/kza_application_interface.h>
#include <application/kza_application.h>

#include <user/engine/kzu_engine.h>
#include <core/debug/kzc_log.h>

#include <user/ui/kzu_screen.h>
#include <user/scene_graph/kzu_object.h>
#include <user/layers/kzu_layer.h>
#include <user/properties/kzu_property_registry.h>
#include <user/properties/kzu_fixed_properties.h>

#include <user/ui/message/kzu_general_messages.h>
#include <user/ui/message/kzu_message.h>
#include <user/ui/message/kzu_message_dispatcher.h>
#include <user/ui/kzu_ui_domain.h>
#include <user/ui/state_manager/kzu_state_manager.h>
#include <user/resource/kzu_image_texture.h>
#include <user/resource/kzu_resource_manager.h>
#include <user/ui/kzu_ui_component.h>
#include <user/ui/components/kzu_ui_list_box.h>

#include<user/scene_graph/kzu_object_resources.h>
#include <user/ui/templates/kzu_prefab.h>
#include <user/resource/kzu_resource.h>
#include <user/resource/kzu_image_texture.h>

#include <user/resource/kzu_resource_manager.h>
#include <core/debug/kzc_log.h>
#include <core/memory/kzc_memory_manager.h>
#include <core/util/collection/kzc_dynamic_array.h>
#include <core/util/image/kzc_image.h>
#include <core/util/string/kzc_string.h>
#include <core/util/io/kzc_input_stream.h>


#include <system/kzs_system.h>
#include <system/thread/kzs_thread.h>

#include "kanzi.h"
#include "Demo.h"

using namespace KANZI;
static struct KzaApplication* g_application = KZ_NULL;
Kanzi_CB g_kanzicb;


typedef enum {
	SETUI,TOGGLELF,TOGGLELR,TOGGLERL,TOGGLERR,TOGGLEAMFM,
	TOGGLEWINDOWFL,TOGGLEWINDOWFR,TOGGLEWINDOWRL,TOGGLEWINDOWRR,TOGGLEBACKDOOR,SETCARLIGHT,SETSTYLE,SETCHAIRGOBACKV,SETCHAIRUPDOWNV,SETCHAIRROTATEV,SETAMFMV,SETYUSHUA,SETCC,MISCONOFF
}MSGTYPE;

typedef struct {
	MSGTYPE type;
	union {
		idxUI idx;
		LightState lightState;
		UIStyle style;
		float val;
		CCState ccstate;
	};
	
}IPCMSG;

/*
const kzString TextureIds[]={"Mat_Video_Picture1.png","Mat_Video_Picture2.png","Mat_Video_Picture3.png",
"Mat_Video_Picture4.png","Mat_Video_Picture5.png","Mat_Video_Picture6.png",
"Mat_Video_Picture7.png","Mat_Video_Picture8.png","Mat_Video_Picture9.png","111.jpg"};
*/
#define   musicIconProfabUrl "kzb://ChangAnShow/Prefabs/MusicItem"
#define   videoIconProfabUrl "kzb://ChangAnShow/Prefabs/IconPrefab_circle"
static  kzString WIDGET_ICON_RESOURCE_ID =   "videoResource";
//static vector<string> file_path_vector
void sendMsgToKanzi(IPCMSG *msg);

struct ApplicationData
{
	struct KzuObjectNode* rootNode;
	struct KzuPropertyType* moduleStateType;
	idxUI currentModule;
	struct KzuObjectNode* mediaVideoList;
	struct KzuObjectNode* mediaMusicList;
	struct KzuMessageDispatcher* messageDispatcher;
	struct KzsThread* ipcThread;
	struct KzcDynamicArray* msgArray;
	struct KzsThreadLock* ipcLock;
     
	//4 doors node and state 
	struct KzuObjectNode* flNode, *frNode, *rlNode, *rrNode;
	struct KzuObjectNode* miscNode;
	struct KzuObjectNode* flWindowNode, *frWindowNode,*rlWindowNode, *rrWindowNode;
	struct KzuPropertyType* togglePropertyType;
	struct KzuObjectNode* backDoorNode;
	struct KzuObjectNode* lightNode;
	struct KzuObjectNode* frontLightNode;
	//struct KzuObjectNode* backLightNode;
	struct KzuPropertyType* lightStatePropertyType,*stateType,*styleState;
	struct KzuObjectNode* caryushuaiqiNode;

	//am fm radio 
	struct KzuObjectNode* radioNodeControl;
	struct KzuObjectNode* radioTextNode;
	//chair control 
	struct KzuObjectNode* chairNode;
	struct KzuPropertyType* gobackType,*updownType,*rotateType;

	//setting cc node 
	struct KzuObjectNode* settingCCNode;

	struct KzuPrefabTemplate* musicIconProfab;
	struct KzuPrefabTemplate* videoIconProfab;
};

void parse_music_video(struct KzuPrefabTemplate* iconProfab,struct KzuObjectNode* itemListBox ,vector<string>& vectortmp)
{
	struct KzcMemoryManager* memoryManager  = kzaApplicationGetApplicationMemoryManager(g_application);
	struct KzuUIDomain* domain = kzaApplicationGetUIDomain(g_application);
	struct  KzuResourceManager* resourceManager = kzuUIDomainGetResourceManager(domain);
	kzInt i = 0;
	for(i = 0;i<vectortmp.size();++i)
	{
		struct KzuObjectNode *  instanceNode = KZ_NULL;
		struct KzcInputStream *inpustream;
		kzuPrefabTemplateInstantiate(iconProfab,"profabInstance",&instanceNode);
		kzuUiListBoxAddObject(kzuUiListBoxFromUiComponentNode(kzuUiComponentNodeFromObjectNode(itemListBox)),instanceNode);
		struct KzcImage* image = KZ_NULL;
		struct KzuImageTexture* imageTexture = KZ_NULL;
		kzcInputStreamCreateFromFile(memoryManager,vectortmp[i].c_str(),KZC_IO_STREAM_ENDIANNESS_PLATFORM,&inpustream);
		kzcImageLoadJPEG(memoryManager, inpustream,true, &image);
		kzcInputStreamDelete(inpustream);
		kzuImageTextureCreateFromImage(resourceManager,vectortmp[i].c_str(),image,KZU_TEXTURE_FILTER_BILINEAR,KZU_TEXTURE_WRAP_CLAMP,0,&imageTexture);
		kzuResourceManagerAddResource(resourceManager,vectortmp[i].c_str(),kzuImageTextureToResource(imageTexture));
		kzuObjectNodeAddResource(instanceNode,WIDGET_ICON_RESOURCE_ID,vectortmp[i].c_str());
		kzuResourceRelease(kzuImageTextureToResource(imageTexture));
	}
}

//Recursive search directory images, dynamic loading
void recursive_search_file(FILEPATH filePath)
{
    struct ApplicationData* data = (struct ApplicationData*)kzaApplicationGetUserData(g_application);
    if(strcmp(filePath.videoPath,"")!=0)
	{
	  printf("parse video path\n");
          WIDGET_ICON_RESOURCE_ID =   "videoResource";
	  readFileList(filePath.videoPath,file_video_path_vector);
      parse_music_video(data->videoIconProfab,data->mediaVideoList,file_video_path_vector);
	}
	if(strcmp(filePath.musicPath,"")!=0)
	{
		printf("parse music path\n");
                WIDGET_ICON_RESOURCE_ID =   "videoResource";
		readFileList(filePath.musicPath,file_music_path_vector);
		parse_music_video(data->musicIconProfab,data->mediaMusicList,file_music_path_vector);
	}
}

void readFileList( char *basePath,vector<string>& filePathVector)
{
    DIR *dir;
    struct dirent *ptr;
    char base[1000];

    if ((dir=opendir(basePath)) == NULL)
    {
        perror("Open dir error...");
        exit(1);
    }

    while ((ptr=readdir(dir)) != NULL)
    {
        if(strcmp(ptr->d_name,".")==0 || strcmp(ptr->d_name,"..")==0)    ///current dir OR parrent dir
            continue;
        struct stat info;
        memset(base,'\0',sizeof(base));
        strcpy(base,basePath);
        strcat(base,"/");
        strcat(base,ptr->d_name);
        stat(base,&info);
        if(S_ISDIR(info.st_mode))         ///dir
        {
            readFileList(base,filePathVector);
            printf("This is a directory %s\n",ptr->d_name);
        }else if(S_ISREG(info.st_mode))   ///file
        {
            if(!strcmp(ptr->d_name,"original"))
            {
                printf("This is a file %s\n",ptr->d_name);
                filePathVector.push_back(base);
            }
        }

       // if(ptr->d_ino == 8)    ///file
       // {
             /*
            if(!strcasecmp(strrchr(ptr->d_name,'.')+1,"jpg") || !strcasecmp(strrchr(ptr->d_name,'.')+1,"png")||\
                    !strcasecmp(strrchr(ptr->d_name,'.')+1,"jpeg"))
            {
                 char strtmp[100];
                 sprintf(strtmp,"%s/%s",basePath,ptr->d_name);
                 file_path_vector.push_back(strtmp);
            }*/
          /*
          if(!strcmp(ptr->d_name,"original"))
            {
                 char strtmp[100];
                 sprintf(strtmp,"%s/%s",basePath,ptr->d_name);
                 file_path_vector.push_back(strtmp);
            }

        }
        else if(ptr->d_ino == 4)    ///dir
        {
            memset(base,'\0',sizeof(base));
            strcpy(base,basePath);
            strcat(base,"/");
            strcat(base,ptr->d_name);
            readFileList(base);
        }*/
    }
    closedir(dir);

}
//setting current UI
void send_set_ui_msg(const idxUI idx)
{
	IPCMSG *msg = new IPCMSG;
	msg->idx = idx;
	msg->type = SETUI;
	sendMsgToKanzi(msg);
}

void set_gui(const idxUI idx)
{
	if(g_application != KZ_NULL)
	{
		struct ApplicationData* data = (struct ApplicationData*)kzaApplicationGetUserData(g_application); 
		kzuObjectNodeSetIntProperty(data->rootNode,data->moduleStateType,idx);
	}
}

idxUI get_ui(void)
{
	idxUI idx = SettingCar;
	if(g_application != KZ_NULL)
	{
		struct ApplicationData* data = (struct ApplicationData*)kzaApplicationGetUserData(g_application);
		idx = data->currentModule;
	}
	return idx;
}

void send_toggle_misc_onoff_msg()
{
	IPCMSG* msg = new IPCMSG;
	msg->type = MISCONOFF;
	sendMsgToKanzi(msg);
}

void send_toggle_fl_msg()
{
	IPCMSG* msg = new IPCMSG;
	msg->type = TOGGLELF;
	sendMsgToKanzi(msg);
}

void send_toggle_am_fm_msg()
{
	IPCMSG* msg = new IPCMSG();
	msg->type = TOGGLEAMFM;
	sendMsgToKanzi(msg);
}

void send_toggle_window_fl_msg()
{
	IPCMSG* msg = new IPCMSG();
	msg->type = TOGGLEWINDOWFL;
	sendMsgToKanzi(msg);
}


void send_toggle_window_fr_msg()
{
	IPCMSG* msg = new IPCMSG();
	msg->type = TOGGLEWINDOWFR;
	sendMsgToKanzi(msg);
}


void send_toggle_window_rl_msg()
{
	IPCMSG* msg = new IPCMSG();
	msg->type = TOGGLEWINDOWRL;
	sendMsgToKanzi(msg);
}

void send_toggle_window_rr_msg()
{
	IPCMSG* msg = new IPCMSG();
	msg->type = TOGGLEWINDOWRR;
	sendMsgToKanzi(msg);
}



void send_toggle_back_door_msg()
{
	IPCMSG* msg = new IPCMSG();
	msg->type = TOGGLEBACKDOOR;
	sendMsgToKanzi(msg);
}


void send_set_light_msg(LightState state)
{
	IPCMSG* msg = new IPCMSG();
	msg->type = SETCARLIGHT;
	msg->lightState = state;
	sendMsgToKanzi(msg);
}


void send_set_style_msg(UIStyle style)
{
	IPCMSG* msg = new IPCMSG();
	msg->type = SETSTYLE;
	msg->style = style;
	sendMsgToKanzi(msg);
}

void send_set_cc_msg(CCState state)
{
	IPCMSG* msg = new IPCMSG();
	msg->type = SETCC;
	msg->ccstate = state;
	sendMsgToKanzi(msg);
}

void send_set_chair_goback_value_msg(float val)
{
	IPCMSG* msg = new IPCMSG();
	msg->type = SETCHAIRGOBACKV;
	msg->val = val;
	sendMsgToKanzi(msg);
}

void send_set_chair_updown_value_msg(float val)
{
	IPCMSG* msg = new IPCMSG();
	msg->type = SETCHAIRUPDOWNV;
	msg->val = val;
	sendMsgToKanzi(msg);
}

void send_set_chair_rotate_value_msg(float val)
{
	IPCMSG* msg = new IPCMSG();
	msg->type = SETCHAIRROTATEV;
	msg->val = val;
	sendMsgToKanzi(msg);
}


void send_amfm_value_msg(float val)
{
	IPCMSG* msg = new IPCMSG();
	msg->type = SETAMFMV;
	msg->val = val;
	sendMsgToKanzi(msg);
}

void send_set_toggle_yushua_msg()
{
	IPCMSG* msg = new IPCMSG();
	msg->type = SETYUSHUA;
	sendMsgToKanzi(msg);
}


//true means open
//false means close

void toggleFrontLeftCarState()
{
	static kzBool state = KZ_FALSE;
	kzcLogDebug("call toggleFL");
	state = !state;
	if(g_application!= KZ_NULL){
		struct ApplicationData* data = (struct ApplicationData*)kzaApplicationGetUserData(g_application);
		if(state){
			//open the door
			kzuObjectNodeSetBoolProperty(data->flNode,data->togglePropertyType,KZ_TRUE);
		}else{
			kzuObjectNodeSetBoolProperty(data->flNode,data->togglePropertyType,KZ_FALSE);
		}
	}
}

void send_toggle_fr_msg()
{
	IPCMSG* msg = new IPCMSG;
	msg->type = TOGGLELR;
	sendMsgToKanzi(msg);
}

void toggleFrontRightCarState()
{
	static kzBool state = KZ_FALSE;
		state = !state;
	if(g_application!= KZ_NULL){
		struct ApplicationData* data = (struct ApplicationData*)kzaApplicationGetUserData(g_application);
		if(state){
			//open the door
			kzuObjectNodeSetBoolProperty(data->frNode,data->togglePropertyType,KZ_TRUE);
		}else{
			kzuObjectNodeSetBoolProperty(data->frNode,data->togglePropertyType,KZ_FALSE);
		}
	}
}


void toggleCarYushua()
{
	static kzBool state = KZ_FALSE;
	state = !state;
	if(g_application!= KZ_NULL){
		struct ApplicationData* data = (struct ApplicationData*)kzaApplicationGetUserData(g_application);
		if(state){
			//open the door
			kzuObjectNodeSetBoolProperty(data->caryushuaiqiNode,data->togglePropertyType,KZ_TRUE);
		}else{
			kzuObjectNodeSetBoolProperty(data->caryushuaiqiNode,data->togglePropertyType,KZ_FALSE);
		}
	}
}


void send_toggle_rl_msg()
{
	IPCMSG* msg = new IPCMSG;
	msg->type = TOGGLERL;
	sendMsgToKanzi(msg);
}


void toggleRearLeftCarState()
{
	static kzBool state = KZ_FALSE;
		state = !state;
	if(g_application!= KZ_NULL){
	struct ApplicationData* data = (struct ApplicationData*)kzaApplicationGetUserData(g_application);
	if(state){
		//open the door
		kzuObjectNodeSetBoolProperty(data->rlNode,data->togglePropertyType,KZ_TRUE);
	}else{
		kzuObjectNodeSetBoolProperty(data->rlNode,data->togglePropertyType,KZ_FALSE);
	}
}
}

void send_toggle_rr_msg()
{
	IPCMSG* msg = new IPCMSG;
	msg->type = TOGGLERR;
	sendMsgToKanzi(msg);
}

void toggleRearRightCarState()
{
	static kzBool state = KZ_FALSE;
		state = !state;
	if(g_application!= KZ_NULL){
		struct ApplicationData* data = (struct ApplicationData*)kzaApplicationGetUserData(g_application);
		if(state){
			//open the door
			kzuObjectNodeSetBoolProperty(data->rrNode,data->togglePropertyType,KZ_TRUE);
		}else{
			kzuObjectNodeSetBoolProperty(data->rrNode,data->togglePropertyType,KZ_FALSE);
		}
	}
}

void toggleMiscOnoffState()
{
	static kzBool state = KZ_FALSE;
	state = !state;
	if(g_application!= KZ_NULL){
		struct ApplicationData* data = (struct ApplicationData*)kzaApplicationGetUserData(g_application);
		if(state){
			//open the door
			kzuObjectNodeSetBoolProperty(data->miscNode,data->togglePropertyType,KZ_TRUE);
		}else{
			kzuObjectNodeSetBoolProperty(data->miscNode,data->togglePropertyType,KZ_FALSE);
		}
	}
}



void sendMsgToKanzi(IPCMSG *msg)
{
	if(g_application != KZ_NULL){
		struct ApplicationData* data = (struct ApplicationData*)kzaApplicationGetUserData(g_application);
		kzsThreadLockAcquire(data->ipcLock);
		kzcDynamicArrayPointerAdd(data->msgArray,msg);
		kzsThreadLockRelease(data->ipcLock);
	}
}



void setting_toggle_window_fl()
{
	static kzBool state = KZ_FALSE;
	state = !state;
	if(g_application!= KZ_NULL){
		struct ApplicationData* data = (struct ApplicationData*)kzaApplicationGetUserData(g_application);
		if(state){
			//open the door
			kzuObjectNodeSetBoolProperty(data->flWindowNode,data->togglePropertyType,KZ_TRUE);
		}else{
			kzuObjectNodeSetBoolProperty(data->flWindowNode,data->togglePropertyType,KZ_FALSE);
		}
	}
}

void setting_toggle_window_fr()
{
	static kzBool state = KZ_FALSE;
	state = !state;
	if(g_application!= KZ_NULL){
		struct ApplicationData* data = (struct ApplicationData*)kzaApplicationGetUserData(g_application);
		if(state){
			//open the door
			kzuObjectNodeSetBoolProperty(data->frWindowNode,data->togglePropertyType,KZ_TRUE);
		}else{
			kzuObjectNodeSetBoolProperty(data->frWindowNode,data->togglePropertyType,KZ_FALSE);
		}
	}
}


void setting_toggle_window_rl()
{
	static kzBool state = KZ_FALSE;
	state = !state;
	if(g_application!= KZ_NULL){
		struct ApplicationData* data = (struct ApplicationData*)kzaApplicationGetUserData(g_application);
		if(state){
			//open the door
			kzuObjectNodeSetBoolProperty(data->rlWindowNode,data->togglePropertyType,KZ_TRUE);
		}else{
			kzuObjectNodeSetBoolProperty(data->rlWindowNode,data->togglePropertyType,KZ_FALSE);
		}
	}
}

void setting_toggle_window_rr()
{
	static kzBool state = KZ_FALSE;
	state = !state;
	if(g_application!= KZ_NULL){
		struct ApplicationData* data = (struct ApplicationData*)kzaApplicationGetUserData(g_application);
		if(state){
			//open the door
			kzuObjectNodeSetBoolProperty(data->rrWindowNode,data->togglePropertyType,KZ_TRUE);
		}else{
			kzuObjectNodeSetBoolProperty(data->rrWindowNode,data->togglePropertyType,KZ_FALSE);
		}
	}
}



void setting_toggle_back_door()
{
	static kzBool state = KZ_FALSE;
	state = !state;
	if(g_application!= KZ_NULL){
		struct ApplicationData* data = (struct ApplicationData*)kzaApplicationGetUserData(g_application);
		if(state){
			//open the door
			kzuObjectNodeSetBoolProperty(data->backDoorNode,data->togglePropertyType,KZ_TRUE);
		}else{
			kzuObjectNodeSetBoolProperty(data->backDoorNode,data->togglePropertyType,KZ_FALSE);
		}
	}
}


void  setting_change_light(LightState lightState)
{
	if(g_application != KZ_NULL){
		struct ApplicationData* data = (struct ApplicationData*)kzaApplicationGetUserData(g_application);
		kzuObjectNodeSetIntProperty(data->lightNode,data->lightStatePropertyType,lightState);
	}
}

void setting_change_style(UIStyle style)
{
	if(g_application != KZ_NULL){
		struct ApplicationData* data = (struct ApplicationData*)kzaApplicationGetUserData(g_application);
		kzuObjectNodeSetIntProperty(data->rootNode,data->styleState,(int)style);
	}
}

void setting_chair_goback_value(float val)
{
	if(g_application != KZ_NULL){
		struct ApplicationData* data = (struct ApplicationData*)kzaApplicationGetUserData(g_application);
		kzuObjectNodeSetFloatProperty(data->chairNode,data->gobackType,val);
	}
}

void setting_cc_state(CCState state)
{
	if(g_application != KZ_NULL){
		struct ApplicationData* data = (struct ApplicationData*)kzaApplicationGetUserData(g_application);
		kzuObjectNodeSetIntProperty(data->settingCCNode,data->stateType,(int)state);
	}
}

void setting_chair_updown_value(float val)
{
	if(g_application != KZ_NULL){
		struct ApplicationData* data = (struct ApplicationData*)kzaApplicationGetUserData(g_application);
		kzuObjectNodeSetFloatProperty(data->chairNode,data->updownType,val);
	}
}

void setting_chair_rotate_value(float val)
{
	if(g_application != KZ_NULL){
		struct ApplicationData* data = (struct ApplicationData*)kzaApplicationGetUserData(g_application);
		kzuObjectNodeSetFloatProperty(data->chairNode,data->rotateType,val);
	}
}


void radio_set_amfm_value(float val)
{
	if(g_application != KZ_NULL)
	{
		struct ApplicationData* data = (struct ApplicationData*)kzaApplicationGetUserData(g_application);
		kzMutableString outVal;
		struct KzcMemoryManager* memoryManager = kzaApplicationGetApplicationMemoryManager(g_application);
		kzcStringFormat(memoryManager,"%3.1f",&outVal,val);
		kzuObjectNodeSetStringProperty(data->radioTextNode,KZU_PROPERTY_TYPE_TEXT_BLOCK__TEXT,outVal);
		kzcStringDelete(outVal);
	}
}

void radio_am_fm_switch()
{
	static kzBool amMode = KZ_TRUE;
	if(amMode){
		//switch to FM  by sending click message to AM node
		if(g_application != KZ_NULL){
			struct ApplicationData* data = (struct ApplicationData*)kzaApplicationGetUserData(g_application);
			kzuObjectNodeSetIntProperty(data->radioNodeControl,data->stateType,1);
			amMode = KZ_FALSE;
		}
	}else{
		//switch to AM  by sending click message to FM node
		if(g_application != KZ_NULL){
			struct ApplicationData* data = (struct ApplicationData*)kzaApplicationGetUserData(g_application);
			kzuObjectNodeSetIntProperty(data->radioNodeControl,data->stateType,2);
			amMode = KZ_TRUE;
		}
	}
}

//void set_main_menu_app_icon(const char* iconFileName)
//{
//
//	if(g_application != KZ_NULL){
//		struct ApplicationData* data = (struct ApplicationData*)kzaApplicationGetUserData(g_application);
//		struct KzcMemoryManager* memoryManager = kzaApplicationGetApplicationMemoryManager(g_application);
//		struct KzuUIDomain* domain = kzaApplicationGetUIDomain(g_application);
//		struct KzuResourceManager*  resourceManager = kzuUIDomainGetResourceManager(domain);
//		struct KzuObjectNode* iconNode =data->mainMenuAppNode;
//		struct KzcImage* image = KZ_NULL;
//		struct KzuImageTexture* imageTexture = KZ_NULL;
//		kzcImageLoadResourceFlipped(memoryManager,iconFileName,&image);
//		kzuImageTextureCreateFromImage(resourceManager,iconFileName,image,KZU_TEXTURE_FILTER_BILINEAR,KZU_TEXTURE_WRAP_CLAMP,0,&imageTexture);
//		kzuResourceManagerAddResource(resourceManager,iconFileName,kzuImageTextureToResource(imageTexture));
//		kzuObjectNodeAddResource(iconNode,"MainMenuAppIcon",iconFileName);
//		kzuObjectNodeSetResourceIDProperty(iconNode,KZU_PROPERTY_TYPE_TEXTURE,"MainMenuAppIcon");
//		kzuResourceRelease(kzuImageTextureToResource(imageTexture));
//	}
//}




void handleIPCMsg(IPCMSG* msg){
	if(g_application != KZ_NULL){
		struct ApplicationData* data = (struct ApplicationData*)kzaApplicationGetUserData(g_application);
		if(msg->type == SETUI){
			set_gui(msg->idx);
		}else if(msg->type == TOGGLELF){
			toggleFrontLeftCarState();
		}else if(msg->type == TOGGLELR){
			toggleFrontRightCarState();
		}else if(msg->type == TOGGLERL){
			toggleRearLeftCarState();
		}else if(msg->type == TOGGLERR){
			toggleRearRightCarState();
		}else if(msg->type == TOGGLEWINDOWFL){
			setting_toggle_window_fl();
		}else if(msg->type == TOGGLEWINDOWFR){
			setting_toggle_window_fr();
		}else if(msg->type == TOGGLEWINDOWRL){
			setting_toggle_window_rl();
		}else if(msg->type == TOGGLEWINDOWRR){
			setting_toggle_window_rr();
		}else if(msg->type == TOGGLEBACKDOOR){
			setting_toggle_back_door();
		}else if(msg->type == TOGGLEAMFM){
			radio_am_fm_switch();
		}else if(msg->type == SETCARLIGHT){
			setting_change_light(msg->lightState);
		}else if(msg->type == SETSTYLE){
			setting_change_style(msg->style);
		}else if(msg->type == SETCHAIRGOBACKV){
			setting_chair_goback_value(msg->val);
		}else if(msg->type == SETCHAIRUPDOWNV){
			setting_chair_updown_value(msg->val);
		}else if(msg->type == SETCHAIRROTATEV){
			setting_chair_rotate_value(msg->val);
		}else if(msg->type == SETAMFMV){
			radio_set_amfm_value(msg->val);
		}else if(msg->type == SETYUSHUA){
			toggleCarYushua();
		}else if(msg->type == SETCC){
			setting_cc_state(msg->ccstate);
		}else if(msg->type == MISCONOFF){
			toggleMiscOnoffState();
		}
	}
}


void handleIPCMsgQueue(){
	if(g_application != KZ_NULL){
		struct ApplicationData* data = (struct ApplicationData*)kzaApplicationGetUserData(g_application);
		kzsThreadLockAcquire(data->ipcLock);
		struct KzcDynamicArrayIterator it = kzcDynamicArrayGetIterator(data->msgArray);
		while(kzcDynamicArrayIterate(it)){
			IPCMSG* msg = (IPCMSG*)kzcDynamicArrayIteratorPointerGetValue(it);
			handleIPCMsg(msg);
			delete msg;
		}
		kzcDynamicArrayClear(data->msgArray);
		kzsThreadLockRelease(data->ipcLock);
	}
}


kzsError listboxcallback(struct KzuMessage* message, void* userData)
{
	struct KzuMessageType* type = (struct KzuMessageType*)kzuMessageGetType(message);
	if(type == KZU_MESSAGE_LIST_BOX_ITEM_SELECTED){
		
		int selection;
		selection = kzuMessageGetIntArgumentDefault(message,KZU_MESSAGE_ARGUMENT__LIST_BOX__SELECTION);
		on_media_video_clicked(selection);
	}else if(type == KZU_MESSAGE_LIST_BOX_TARGET_CHANGED){
		
		int focusIndex;
		focusIndex = kzuMessageGetIntArgumentDefault(message,KZU_MESSAGE_ARGUMENT__LIST_BOX__ITEM_INDEX);
		on_media_video_focus(focusIndex);
	}
	kzsSuccess();
}

kzsError musiclistboxcallback(struct KzuMessage* message, void* userData)
{
	struct KzuMessageType* type = (struct KzuMessageType*)kzuMessageGetType(message);
	if(type == KZU_MESSAGE_LIST_BOX_ITEM_SELECTED){

		int selection;
		selection = kzuMessageGetIntArgumentDefault(message,KZU_MESSAGE_ARGUMENT__LIST_BOX__SELECTION);
		on_media_music_clicked(selection);
	}else if(type == KZU_MESSAGE_LIST_BOX_TARGET_CHANGED){

		int focusIndex;
		focusIndex = kzuMessageGetIntArgumentDefault(message,KZU_MESSAGE_ARGUMENT__LIST_BOX__ITEM_INDEX);
		on_media_music_focus(focusIndex);
	}
	kzsSuccess();
}



KZ_CALLBACK static kzsError keyInputEventHandler(struct KzaApplication* application, const struct KzsInputEventKey* inputData)
{
    enum KzsInputKey button = kzsInputEventKeyGetButton(inputData);
	enum KzsInputKeyDeviceState state = kzsInputEventKeyGetState(inputData);
	struct ApplicationData* data = (struct ApplicationData*)kzaApplicationGetUserData(g_application);
    /* Handle the escape or Q button to exit the application. */
    if (button == KZS_KEY_ESC || button == KZS_KEY_Q)
    {
        kzaApplicationQuit(application);
    }
	if(button == KZS_KEY_1 && state == KZS_KEY_DEVICE_STATE_UP){
		g_kanzicb.pSetUI(SettingCar);
	}else if(button == KZS_KEY_2 && state == KZS_KEY_DEVICE_STATE_UP){
		g_kanzicb.pSetUI(SettingChair);
	}else if(button == KZS_KEY_3 && state == KZS_KEY_DEVICE_STATE_UP){
		g_kanzicb.pSetUI(Radio);
	}else if(button == KZS_KEY_4 && state == KZS_KEY_DEVICE_STATE_UP){
		g_kanzicb.pSetUI(MediaVideo);
	}else if(button == KZS_KEY_5 && state == KZS_KEY_DEVICE_STATE_UP){
		g_kanzicb.pSetUI(MediaMusic);
	}else if(button == KZS_KEY_6 && state == KZS_KEY_DEVICE_STATE_UP){
		static kzInt times = 0;
		g_kanzicb.pSetUIStyle(UIStyle(times+1));
		times = (times + 1)%3;
	}else if(button == KZS_KEY_7 && state == KZS_KEY_DEVICE_STATE_UP){
		static kzInt times = 0;
		g_kanzicb.pSetCarLight(LightState(times+1));
		times = (times + 1)%3;
	}else if(button == KZS_KEY_8 && state == KZS_KEY_DEVICE_STATE_UP){
		g_kanzicb.pSetUI(SettingCC);
	}else if(button == KZS_KEY_A && state == KZS_KEY_DEVICE_STATE_UP){
		static kzInt times = 0;
		
		if(times == 0)
			g_kanzicb.pSettingToggleFL();
		if(times == 1)
			g_kanzicb.pSettingToggleFR();
		if(times == 2)
			g_kanzicb.pSettingToggleRL();
		if(times == 3)
			g_kanzicb.pSettingToggleRR();
		times = (times + 1) %4;
	}else if(button == KZS_KEY_B && state == KZS_KEY_DEVICE_STATE_UP){
		g_kanzicb.pSetChairGoBackFunc(10);
	}else if(button == KZS_KEY_C && state == KZS_KEY_DEVICE_STATE_UP){
		g_kanzicb.pSetChairUpDownFunc(2);
	}else if(button == KZS_KEY_D && state == KZS_KEY_DEVICE_STATE_UP){
		g_kanzicb.pSetChairRotateFunc(10);
	}else if(button == KZS_KEY_E && state == KZS_KEY_DEVICE_STATE_UP){
		g_kanzicb.pRadioToggleAMFM();
	}else if(button == KZS_KEY_F && state == KZS_KEY_DEVICE_STATE_UP){
		float v = 96.59999f;
		g_kanzicb.pSetAMFMFunc(v);
	}else if(button == KZS_KEY_G && state == KZS_KEY_DEVICE_STATE_UP){
		static kzInt  times = 0;
		g_kanzicb.pSetCCFunc(CCState(times + 1));
		times = (times + 1)%3;
	}else if(button == KZS_KEY_H && state == KZS_KEY_DEVICE_STATE_UP){
		g_kanzicb.pSettingToggleWindowFL();
		g_kanzicb.pSettingToggleWindowFR();	
		g_kanzicb.pSettingToggleWindowRL();
		g_kanzicb.pSettingToggleWindowRR();
		
	}else if(button == KZS_KEY_J && state == KZS_KEY_DEVICE_STATE_UP){
		g_kanzicb.pSettingToggleYushua();
	}else if(button == KZS_KEY_K && state == KZS_KEY_DEVICE_STATE_UP){
		g_kanzicb.pSettingToggleBackDoor();
	}else if(button == KZS_KEY_L && state == KZS_KEY_DEVICE_STATE_UP){
		g_kanzicb.pMiscToggleONOFF();
	}

    kzsSuccess();
}

static kzsError runIPCThread(void *userData)
{
	Kanzi_CB * kanziCB = (Kanzi_CB*)userData;
	kzcLogDebug("run ipc thread in kanzi ");
	runIPCLoop(kanziCB);


// 	{
// 		kanziCB->pSetUI(SettingCar);
// 		int count =0;
// 		while(1){
// 			
// 			count++;
// 			if(10000000 == count){
// 
// 				//set the light 
// 				//kanziCB->pSetUIStyle(NormalStyle);
// 				kanziCB->pSetCarLight(LightNone);
// 				printf("set light");
// 			}else if(20000000 == count){
// 				//kanziCB->pSetUIStyle(ClassicStyle);
// 				kanziCB->pSetCarLight(LightDadeng);
// 				printf("set light");
// 			}else if(30000000 == count){
// 				//kanziCB->pSetUIStyle(SportStyle);
// 				kanziCB->pSetCarLight(LightWudeng);
// 				printf("set light");
// 			}
// 			if(count == 40000000){
// 				count = 0;
// 			}
// 
// 		}
// 	}


// 	static int i = 0; 
// 	while(true){
// 		if(i ==0 ){
// 			g_kanzicb.pSetUI(SettingCar);
// 			static kzInt times = 0;
// 		//	g_kanzicb.pSettingToggleBackDoor();
// 			//g_kanzicb.pSetCarLight(LightNone);
// 
// 			g_kanzicb.pSetUIStyle(NormalStyle);
// // 			if(times == 0)
// // 				g_kanzicb.pSettingToggleFL();
// // 			if(times == 1)
// // 				g_kanzicb.pSettingToggleFR();
// // 			if(times == 2)
// // 				g_kanzicb.pSettingToggleRL();
// // 			if(times == 3)
// // 				g_kanzicb.pSettingToggleRR();
// // 			times = (times + 1) %4;
// // 
// // 			g_kanzicb.pSettingToggleWindowFL();
// // 			g_kanzicb.pSettingToggleWindowFR();	
// // 			g_kanzicb.pSettingToggleWindowRL();
// // 			g_kanzicb.pSettingToggleWindowRR();
// // 			g_kanzicb.pSettingToggleBackDoor();
// // 			g_kanzicb.pSettingToggleYushua();
// 		}else if(i  == 20000){
// 			g_kanzicb.pSetUIStyle(ClassicStyle);
// 		//	g_kanzicb.pSettingToggleBackDoor();
// 			//g_kanzicb.pSetCarLight(LightDadeng);
// // 			g_kanzicb.pSetUI(SettingChair);
// // 			g_kanzicb.pSetChairGoBackFunc(1 + i);
// // 			g_kanzicb.pSetChairUpDownFunc(i - 8);
// // 			g_kanzicb.pSetChairRotateFunc(i+1);
// 		}else if(i == 30000){
// 			g_kanzicb.pSetUIStyle(SportStyle);
// 		//	g_kanzicb.pSettingToggleBackDoor();
// 		//	g_kanzicb.pSetCarLight(LightWudeng);
// // 			g_kanzicb.pSetUI(Radio);
// // 			float v = 96.59999 + i;
// // 			g_kanzicb.pSetAMFMFunc(v); 
// // 			g_kanzicb.pRadioToggleAMFM();
// 		}
// 		++i;
// 		if(i == 40000)
// 			i =0;
// 		printf("%d\n",i);
// 	}
	kzsSuccess();
}


kzsError onVehicleClickHandler(struct KzuMessage* message, void* userData)
{
	struct KzuObjectNode* sourceNode = kzuMessageGetSource(message);
	struct KzaApplication* application = (struct KzaApplication* )userData;
	struct ApplicationData* data = (struct ApplicationData*)kzaApplicationGetUserData(application);
	kzBool toggleProperty = KZ_FALSE;
	VehicleSection section;
	kzuObjectNodeGetBoolProperty(sourceNode,data->togglePropertyType,&toggleProperty);
	toggleProperty = !toggleProperty;
	kzuObjectNodeSetBoolProperty(sourceNode,data->togglePropertyType,toggleProperty);
	if(sourceNode == data->flNode){
		section = CAR_DOOR_FRONT_LEFT;
		on_vehicle_clicked(section,toggleProperty);
	}else if(sourceNode == data->frNode){
		section = CAR_DOOR_RONT_RIGHT;
		on_vehicle_clicked(section,toggleProperty);
	}else if(sourceNode == data->rlNode){
		section =CAR_DOOR_BACK_LEFT;
		on_vehicle_clicked(section,toggleProperty);
	}else if(sourceNode == data->rrNode){
		section =CAR_DOOR_BACK_RIGHT;
		on_vehicle_clicked(section,toggleProperty);
	}else if(sourceNode == data->frontLightNode){
		kzInt lightState;
		kzuObjectNodeGetIntProperty(data->lightNode,data->lightStatePropertyType,&lightState);
		section =CAR_LIGHT;
		bool dadengOpened = false;
		if(lightState != 2){
			lightState = 2;
			kzuObjectNodeSetIntProperty(data->lightNode,data->lightStatePropertyType,lightState);
			dadengOpened  = true;
		}else if(lightState == 2){
			lightState = 1;
			kzuObjectNodeSetIntProperty(data->lightNode,data->lightStatePropertyType,lightState);
			dadengOpened = false;
		}
		on_vehicle_clicked(section,dadengOpened);

	}else if(sourceNode == data->backDoorNode){
		section =CAR_BACK_DOOR;
		on_vehicle_clicked(section,toggleProperty);
	}/*else if(sourceNode == data->backLightNode){
		kzInt lightState;
		kzuObjectNodeGetIntProperty(data->lightNode,data->lightStatePropertyType,&lightState);
		section =CAR_FOG_LIGHT;
		bool fogDengOpened = false;
		if(lightState != 3){
			lightState = 3;
			kzuObjectNodeSetIntProperty(data->lightNode,data->lightStatePropertyType,lightState);
			fogDengOpened  = true;
		}else if(lightState == 3){
			lightState = 1;
			kzuObjectNodeSetIntProperty(data->lightNode,data->lightStatePropertyType,lightState);
			fogDengOpened = false;
		}
		on_vehicle_clicked(section,fogDengOpened);
		kzuMessageSetHandled(message,KZ_TRUE);
	}*/
//	printf("state %d\n",toggleProperty);
	kzsSuccess();
}

kzsError projectLoaded(struct KzaApplication* application)
{
	struct KzuScreen* screen = kzaApplicationGetScreen(application);
	struct KzuObjectNode* screenNode = kzuScreenToObjectNode(screen);
	struct KzcMemoryManager* memoryManager  = kzaApplicationGetApplicationMemoryManager(application);
	struct ApplicationData* data = KZ_NULL;
	struct KzuUIDomain* domain = kzaApplicationGetUIDomain(application);
  
	kzcMemoryAllocVariable(memoryManager,data,"data");
	kzaApplicationSetUserData(application,data);
	data->rootNode = kzuLayerToObjectNode(kzaApplicationGetRootLayer(application));          
	data->moduleStateType = kzuPropertyRegistryFindPropertyType("ModuleState");
	data->messageDispatcher = kzuUIDomainGetMessageDispatcher(domain);         
	data->flNode = kzuObjectNodeGetRelative(screenNode,"#door_front_left_group");
	kzuMessageDispatcherAddHandler(data->messageDispatcher,data->flNode,KZU_MESSAGE_CLICK,KZ_NULL,onVehicleClickHandler,application);
	data->frNode = kzuObjectNodeGetRelative(screenNode,"#door_front_right_group");
	kzuMessageDispatcherAddHandler(data->messageDispatcher,data->frNode,KZU_MESSAGE_CLICK,KZ_NULL,onVehicleClickHandler,application);
	data->rlNode = kzuObjectNodeGetRelative(screenNode,"#door_rear_left_group");
	kzuMessageDispatcherAddHandler(data->messageDispatcher,data->rlNode,KZU_MESSAGE_CLICK,KZ_NULL,onVehicleClickHandler,application);
	data->rrNode = kzuObjectNodeGetRelative(screenNode,"#door_rear_right_group");
	kzuMessageDispatcherAddHandler(data->messageDispatcher,data->rrNode,KZU_MESSAGE_CLICK,KZ_NULL,onVehicleClickHandler,application);

	/*
	data->flWindowNode = kzuObjectNodeGetRelative(screenNode,"#door_front_left_window");
	data->frWindowNode = kzuObjectNodeGetRelative(screenNode,"#door_front_right_window");
	data->rlWindowNode = kzuObjectNodeGetRelative(screenNode,"#door_rear_left_window");
	data->rrWindowNode = kzuObjectNodeGetRelative(screenNode,"#door_rear_right_window");
        */

	data->backDoorNode = kzuObjectNodeGetRelative(screenNode,"#back_door");
	kzuMessageDispatcherAddHandler(data->messageDispatcher,data->backDoorNode,KZU_MESSAGE_CLICK,KZ_NULL,onVehicleClickHandler,application);

	data->togglePropertyType = kzuPropertyRegistryFindPropertyType("ToogleProperty");
	data->lightStatePropertyType = kzuPropertyRegistryFindPropertyType("LightState");
	data->styleState = kzuPropertyRegistryFindPropertyType("BackGroundState");
	
	data->radioNodeControl = kzuObjectNodeGetRelative(screenNode,"#Radio_Node_Model");
	data->radioTextNode = kzuObjectNodeGetRelative(screenNode,"#AMFMVal");
	data->lightNode = kzuObjectNodeGetRelative(screenNode,"#light_node");
	data->frontLightNode = kzuObjectNodeGetRelative(screenNode,"#front_light");
	data->settingCCNode = kzuObjectNodeGetRelative(screenNode,"#CCLabel");
	data->miscNode = kzuObjectNodeGetRelative(screenNode,"#Misc");
	//data->backLightNode = kzuObjectNodeGetRelative(screenNode,"#ext_front_left_light");
	kzuMessageDispatcherAddHandler(data->messageDispatcher,data->frontLightNode,KZU_MESSAGE_CLICK,KZ_NULL,onVehicleClickHandler,application);
	//kzuMessageDispatcherAddHandler(data->messageDispatcher,data->backLightNode,KZU_MESSAGE_CLICK,KZ_NULL,onVehicleClickHandler,application);
	
	data->stateType = kzuPropertyRegistryFindPropertyType("State");

	data->chairNode = kzuObjectNodeGetRelative(screenNode,"#Chair");
	data->caryushuaiqiNode = kzuObjectNodeGetRelative(screenNode,"#car_yushuaqi");
	data->gobackType = kzuPropertyRegistryFindPropertyType("GoBackValue_Chair");
	data->updownType = kzuPropertyRegistryFindPropertyType("UpDownValue_Chair");
	data->rotateType = kzuPropertyRegistryFindPropertyType("RotateValue_Chair");
	

	data->mediaVideoList = kzuObjectNodeGetRelative(screenNode,"#media_video_list");
	data->mediaMusicList = kzuObjectNodeGetRelative(screenNode,"#media_music_list");
	kzuMessageDispatcherAddHandler(data->messageDispatcher,data->mediaVideoList,KZU_MESSAGE_LIST_BOX_TARGET_CHANGED,KZ_NULL,listboxcallback,application);
	kzuMessageDispatcherAddHandler(data->messageDispatcher,data->mediaVideoList,KZU_MESSAGE_LIST_BOX_ITEM_SELECTED,KZ_NULL,listboxcallback,application);

	kzuMessageDispatcherAddHandler(data->messageDispatcher,data->mediaMusicList,KZU_MESSAGE_LIST_BOX_TARGET_CHANGED,KZ_NULL,musiclistboxcallback,application);
	kzuMessageDispatcherAddHandler(data->messageDispatcher,data->mediaMusicList,KZU_MESSAGE_LIST_BOX_ITEM_SELECTED,KZ_NULL,musiclistboxcallback,application);

        struct  KzuResourceManager* resourceManager = kzuUIDomainGetResourceManager(domain);
        struct KzuResource* musicResource = KZ_NULL;    
        struct KzuResource* videoResource = KZ_NULL;
	kzuResourceManagerAcquireResource(resourceManager,musicIconProfabUrl,&musicResource);	
        data->musicIconProfab = kzuPrefabTemplateFromResource(musicResource);    
        kzuResourceManagerAcquireResource(resourceManager,videoIconProfabUrl,&videoResource);	
        data->videoIconProfab = kzuPrefabTemplateFromResource(videoResource);
	g_application = application;
	FILEPATH DEMPPATH={"","/apps/mediasources/imagecache/mme"};
	recursive_search_file(DEMPPATH);
	
//create a new thread to receive the msg from ipc
	kzcDynamicArrayCreate(kzaApplicationGetSystemMemoryManager(application),&data->msgArray);



	kzsThreadLockCreate(&data->ipcLock);
	g_kanzicb.pSetUI = send_set_ui_msg;
	g_kanzicb.pGetUI = get_ui;
	g_kanzicb.pSettingToggleFL = send_toggle_fl_msg;
	g_kanzicb.pSettingToggleFR = send_toggle_fr_msg;
	g_kanzicb.pSettingToggleRL = send_toggle_rl_msg;
	g_kanzicb.pSettingToggleRR = send_toggle_rr_msg;
	
	g_kanzicb.pRadioToggleAMFM = send_toggle_am_fm_msg;
	g_kanzicb.pSettingToggleWindowFL = send_toggle_window_fl_msg;
	g_kanzicb.pSettingToggleWindowFR = send_toggle_window_fr_msg;
	g_kanzicb.pSettingToggleWindowRL = send_toggle_window_rl_msg;
	g_kanzicb.pSettingToggleWindowRR = send_toggle_window_rr_msg;
	g_kanzicb.pSettingToggleBackDoor = send_toggle_back_door_msg;
	g_kanzicb.pSetCarLight = send_set_light_msg;
	g_kanzicb.pSetUIStyle = send_set_style_msg;	
	g_kanzicb.pSetChairGoBackFunc = send_set_chair_goback_value_msg;
	g_kanzicb.pSetChairUpDownFunc = send_set_chair_updown_value_msg;
	g_kanzicb.pSetChairRotateFunc = send_set_chair_rotate_value_msg;
	g_kanzicb.pSetAMFMFunc = send_amfm_value_msg;
	g_kanzicb.pSettingToggleYushua = send_set_toggle_yushua_msg;
	g_kanzicb.pSetCCFunc = send_set_cc_msg;
	g_kanzicb.pMiscToggleONOFF = send_toggle_misc_onoff_msg;
        g_kanzicb.pReadFileList = recursive_search_file;


	kzsThreadCreate(runIPCThread,&g_kanzicb,KZ_FALSE,&data->ipcThread);
	kzsSuccess();
}

kzsError update(struct KzaApplication* application, kzUint delta)
{
	handleIPCMsgQueue();
	kzsSuccess();
}

kzsError shutdown(struct KzaApplication* application)
{
	struct ApplicationData* data = (struct ApplicationData*)kzaApplicationGetUserData(application);
	kzInt i=0;
	kzsThreadJoin(data->ipcThread);
	kzsThreadDelete(data->ipcThread);
	kzcDynamicArrayDelete(data->msgArray);
	kzsThreadLockDelete(data->ipcLock);
	kzuMessageDispatcherRemoveHandler(data->messageDispatcher,data->mediaVideoList,KZU_MESSAGE_LIST_BOX_TARGET_CHANGED,listboxcallback,application);
	kzuMessageDispatcherRemoveHandler(data->messageDispatcher,data->mediaVideoList,KZU_MESSAGE_LIST_BOX_ITEM_SELECTED,listboxcallback,application);
	kzuMessageDispatcherRemoveHandler(data->messageDispatcher,data->mediaMusicList,KZU_MESSAGE_LIST_BOX_TARGET_CHANGED,musiclistboxcallback,application);
	kzuMessageDispatcherRemoveHandler(data->messageDispatcher,data->mediaMusicList,KZU_MESSAGE_LIST_BOX_ITEM_SELECTED,musiclistboxcallback,application);
	kzuMessageDispatcherRemoveHandler(data->messageDispatcher,data->flNode,KZU_MESSAGE_CLICK,onVehicleClickHandler,application);
	kzuMessageDispatcherRemoveHandler(data->messageDispatcher,data->frNode,KZU_MESSAGE_CLICK,onVehicleClickHandler,application);
	kzuMessageDispatcherRemoveHandler(data->messageDispatcher,data->rlNode,KZU_MESSAGE_CLICK,onVehicleClickHandler,application);
	kzuMessageDispatcherRemoveHandler(data->messageDispatcher,data->rrNode,KZU_MESSAGE_CLICK,onVehicleClickHandler,application);
	kzuMessageDispatcherRemoveHandler(data->messageDispatcher,data->backDoorNode,KZU_MESSAGE_CLICK,onVehicleClickHandler,application);
	kzuMessageDispatcherRemoveHandler(data->messageDispatcher,data->frontLightNode,KZU_MESSAGE_CLICK,onVehicleClickHandler,application);
	//kzuMessageDispatcherRemoveHandler(data->messageDispatcher,data->backLightNode,KZU_MESSAGE_CLICK,onVehicleClickHandler,application);

        kzuResourceRelease(kzuPrefabTemplateToResource(data->musicIconProfab));
	kzuResourceRelease(kzuPrefabTemplateToResource(data->videoIconProfab));
	kzcMemoryFreeVariable(data);

	g_application = KZ_NULL;
	kzsSuccess();
}
//kzsError startup(struct KzaApplication* application)
//{
	//kzsError result;
	//struct KzuResourceManager* resourceManager = kzuUIDomainGetResourceManager(kzaApplicationGetUIDomain(application));
	/* Register a protocol handler that the resource manager will use for loading images from the file system. */
	//result = kzuResourceManagerRegisterProtocolHandler(resourceManager, IMAGE_PROTOCOL, imageFileLoader, KZ_NULL);
	//kzsErrorForward(result);

	//kzsSuccess();
//}
KZ_CALLBACK void kzApplicationConfigure(const struct KzaSystemProperties* systemProperties, struct KzaApplicationProperties* configuration)
{
    configuration->memoryPoolSize = 100 * 1024 * 1024;
    configuration->binaryName = "ChangAnShow.kzb.cfg";
    configuration->onKeyInputEvent = keyInputEventHandler;
    configuration->onProjectLoaded = projectLoaded;
	//configuration->onStartup = startup;
    configuration->onUpdate = update;
    configuration->onShutdown = shutdown;
}
