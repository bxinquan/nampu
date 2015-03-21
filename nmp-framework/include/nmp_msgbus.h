/*
 * nmp_msgbus.h
 *
 * Copyright(c) by Nampu, 2010~2014
 * Author:
*/

#ifndef __NMP_MSG_BUS_H__
#define __NMP_MSG_BUS_H__

#include "nmp_object.h"
#include "nmp_sysmsg.h"
#include "nmp_modio.h"

G_BEGIN_DECLS

typedef enum        /* ret-value type of bus hooks */
{
    BHR_ACCEPT = 0,
    BHR_DROP,
    BHR_QUEUE
}JpfBusHookRet;

#define NMP_TYPE_MSGBUS (jpf_msg_bus_get_type())
#define NMP_IS_MSGBUS(o) (G_TYPE_CHECK_INSTANCE_TYPE((o), NMP_TYPE_MSGBUS))
#define NMP_IS_MSGBUS_CLASS(c) \
    (G_TYPE_CHECK_CALSS_TYPE((c), NMP_TYPE_MSGBUS))
#define NMP_MSGBUS(o) (G_TYPE_CHECK_INSTANCE_CAST((o), NMP_TYPE_MSGBUS, JpfMsgBus))
#define NMP_MSGBUS_CLASS(c) \
    (G_TYPE_CHECK_CLASS_CAST((c), NMP_TYPE_MSGBUS, JpfMsgBusClass))
#define NMP_MSGBUS_GET_CLASS(o) \
    (G_TYPE_INSTANCE_GET_CLASS((o), NMP_TYPE_MSGBUS, JpfMsgBusClass))

typedef struct _JpfMsgBus JpfMsgBus;
typedef struct _JpfMsgBusClass JpfMsgBusClass;
typedef gint (*JpfMsgHookFn)(NmpSysMsg *msg);
typedef JpfBusHookRet (*JpfBusMsgHook)(JpfMsgBus *bus, NmpSysMsg *msg);

struct _JpfMsgBus
{
    JpfObject parent_object;

    GAsyncQueue *msg_queue;
    JpfBusMsgHook msg_hook;
	gboolean bus_bypass;
    JpfBusSlots bus_slots;
    GThread *bus_thread;    /* msg dispatcher */
};


struct _JpfMsgBusClass
{
    JpfObjectClass parent_class;
};


gint jpf_msg_bus_request_slot(JpfMsgBus *self, 
    gpointer slot, JpfBusSlotPos i_slot);

gint jpf_msg_bus_slot_link(JpfMsgBus *self,
    JpfBusSlotPos i_slot, NmpModIO *modio);

void jpf_msg_bus_set_bypass(JpfMsgBus *self);

gint jpf_msg_bus_add_msg_hook(JpfBusSlotPos who, JpfMsgHookFn fun);
gint jpf_msg_bus_rcv_msg(JpfMsgBus *self, JpfBusSlotPos i_slot, NmpSysMsg *msg);

GType jpf_msg_bus_get_type( void );

G_END_DECLS

#endif  //__NMP_MSG_BUS_H__
