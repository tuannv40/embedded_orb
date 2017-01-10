#include <stdio.h>

#define ORBDB_NODE_MAXIMUM              100

/****************************** ORB DATA INTERFACE *****************************/
typedef enum {
    ORBDB_TYPE_PUBSUB = 0,
    ORBDB_TYPE_PARAM  = 1,
    ORBDB_TYPE_UNDEFINE  = 2
} ORBDB_TYPE;

/**
 * Interface of a topic existed in Message Server.
 */
typedef struct {
    const char* name;       // Name of the topic
    int         id;         // Id of the topic
    int         size;       // Size of the topic
    int         padding;    // In log debug version
} orb_metadata_t;

typedef const orb_metadata_t *orb_id_t;

enum ORB_PRIO {
	ORB_PRIO_MIN = 1, // leave 0 free for other purposes, eg. marking an uninitialized value
	ORB_PRIO_VERY_LOW = 25,
	ORB_PRIO_LOW = 50,
	ORB_PRIO_DEFAULT = 75,
	ORB_PRIO_HIGH = 100,
	ORB_PRIO_VERY_HIGH = 125,
	ORB_PRIO_MAX = 255
};

#define ORB_ID(_name)		&__orb_##_name
#define ORB_DECLARE(_name)	extern const orb_metadata_t     __orb_##_name 
#define ORB_DEFINE(_name, _id, _padding)		            \
                	const orb_metadata_t __orb_##_name = {	\
                		#_name,					            \
                        _id,                                \
                		sizeof(_struct),		            \
                		_padding };

/**
 * Node or proxy of data managed in ORBServer
 */
typedef struct {
    const orb_metadata_t *meta;  // Constant pointer to orb_metadata_t.
    uint8_t              *data;  // Pointer to alocalte of first queue store data.

    uint64_t              timeLastUpdated; // Time at last update data.
    volatile uint32_t     generation;  // Generation counter begin at first updated.
    const uint8_t         priority;    // Priority number of this topic.
    bool                  isPublished; // Flag when the topic is updated and published.
    uint8_t               sizeQueue;   // Maximum number of elements in the circle queue.

    uint8_t               publisherID; // In this version,one topic will updated by only a publisher.
    int8_t                subcriberNo; // Quantity of subcribers current registered to the topic.
    uint32_t              lostMessage; // Lost message number
} orb_dev_node_t;

orb_dev_node_t* ORBDev_CreateNode();
result_t ORBDev_Write();
int32_t  ORBDev_Read();
result_t ORBDev_Publish();
result_t ORBDev_AddSubscriber();
result_t ORBDev_RemoveSubscriber();
bool     ORBDev_IsPublish();
const orb_metadata_t* ORBDev_GetMeta ();

/**
 * Data-base of the topics
 * \note In other system as uORB, ROS, MOOS data-base of system using dynamic memory to manage data but in this
 * version using stack to manage is for avoid leak memory.
 *
 */
typedef struct {
    uint64_t               timestamp; // Time at statistics data
    orb_dev_node_t         node[ORBDB_NODE_MAXIMUM]; // Data-base concurrent
    ORBDB_TYPE             type; // Type of the data-base
} orb_data_base_t;

result_t ORBDB_Initialize (int32_t size);
result_t ORBDB_AddNewNode (int32_t size);
result_t ORBDB_RemoveNode (int32_t size);
orb_dev_node_t* ORBDB_GetDevNode(int32_t id);
