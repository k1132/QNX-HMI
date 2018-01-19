/**
* \file
*
* This is a skeleton for new application.
*/
#include <stdio.h>
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

struct ApplicationData
{
	struct KzuObjectNode* playNode;
	struct KzuObjectNode* stopNode;
	struct KzuObjectNode* preNode;
	struct KzuObjectNode* nextNode;
	struct KzuMessageDispatcher* messageDispatcher;
};
KZ_CALLBACK static kzsError keyInputEventHandler(struct KzaApplication* application, const struct KzsInputEventKey* inputData)
{
    enum KzsInputKey button = kzsInputEventKeyGetButton(inputData);

    /* Handle the escape or Q button to exit the application. */
    if (button == KZS_KEY_ESC || button == KZS_KEY_Q)
    {
        kzaApplicationQuit(application);
    }

    kzsSuccess();
}
kzsError onVehicleClickHandler(struct KzuMessage* message, void* userData)
{
	struct KzuObjectNode* sourceNode = kzuMessageGetSource(message);
	struct KzaApplication* application = (struct KzaApplication* )userData;
	struct ApplicationData* data = (struct ApplicationData*)kzaApplicationGetUserData(application);
	//kzBool toggleProperty = KZ_FALSE;
	//VehicleSection section;
	//kzuObjectNodeGetBoolProperty(sourceNode,data->togglePropertyType,&toggleProperty);
	//toggleProperty = !toggleProperty;
	//kzuObjectNodeSetBoolProperty(sourceNode,data->togglePropertyType,toggleProperty);
	if(sourceNode == data->playNode){
		system("/opt/media.sh play &");
		printf("play\n");
	}else if(sourceNode == data->stopNode){
		system("/opt/media.sh stop &");
		printf("stop\n");
	}else if(sourceNode == data->preNode){
		system("/opt/media.sh pre &");
		printf("pre\n");
	}else if(sourceNode == data->nextNode){
		system("/opt/media.sh next &");
		printf("next\n");
	}
	
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
	//data->rootNode = kzuLayerToObjectNode(kzaApplicationGetRootLayer(application));          
	//data->moduleStateType = kzuPropertyRegistryFindPropertyType("ModuleState");
	data->messageDispatcher = kzuUIDomainGetMessageDispatcher(domain);         
	data->playNode = kzuObjectNodeGetRelative(screenNode,"#play");
	kzuMessageDispatcherAddHandler(data->messageDispatcher,data->playNode,KZU_MESSAGE_CLICK,KZ_NULL,onVehicleClickHandler,application);
	data->stopNode = kzuObjectNodeGetRelative(screenNode,"#stop");
	kzuMessageDispatcherAddHandler(data->messageDispatcher,data->stopNode,KZU_MESSAGE_CLICK,KZ_NULL,onVehicleClickHandler,application);
	data->preNode = kzuObjectNodeGetRelative(screenNode,"#pre");
	kzuMessageDispatcherAddHandler(data->messageDispatcher,data->preNode,KZU_MESSAGE_CLICK,KZ_NULL,onVehicleClickHandler,application);
	data->nextNode = kzuObjectNodeGetRelative(screenNode,"#next");
	kzuMessageDispatcherAddHandler(data->messageDispatcher,data->nextNode,KZU_MESSAGE_CLICK,KZ_NULL,onVehicleClickHandler,application);
    kzsSuccess();
}
kzsError shutdown(struct KzaApplication* application)
{
	struct ApplicationData* data = (struct ApplicationData*)kzaApplicationGetUserData(application);
	kzuMessageDispatcherRemoveHandler(data->messageDispatcher,data->playNode,KZU_MESSAGE_CLICK,onVehicleClickHandler,application);
	kzuMessageDispatcherRemoveHandler(data->messageDispatcher,data->stopNode,KZU_MESSAGE_CLICK,onVehicleClickHandler,application);
	kzuMessageDispatcherRemoveHandler(data->messageDispatcher,data->preNode,KZU_MESSAGE_CLICK,onVehicleClickHandler,application);
	kzuMessageDispatcherRemoveHandler(data->messageDispatcher,data->nextNode,KZU_MESSAGE_CLICK,onVehicleClickHandler,application);
	//kzuMessageDispatcherRemoveHandler(data->messageDispatcher,data->backLightNode,KZU_MESSAGE_CLICK,onVehicleClickHandler,application);
   kzcMemoryFreeVariable(data);
	kzsSuccess();
}
KZ_CALLBACK void kzApplicationConfigure(const struct KzaSystemProperties* systemProperties, struct KzaApplicationProperties* configuration)
{
    configuration->memoryPoolSize = 200 * 1024 * 1024;
    configuration->binaryName = "clickDemo.kzb.cfg";
    configuration->onProjectLoaded = projectLoaded;
    configuration->onKeyInputEvent = keyInputEventHandler;
	configuration->onShutdown = shutdown;
}
