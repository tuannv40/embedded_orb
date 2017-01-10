#include "orb_data.h"

typedef void 	*orb_advert_t;

// Funtionals for publishser
extern orb_advert_t ORB_Advertise();  // get pointer to device node and publisher first
extern orb_advert_t ORB_AdvertiseQueue();
extern orb_advert_t ORB_AdvertiseMultiQueue();
extern orb_advert_t ORB_AdvertiseMulti();
extern orb_advert_t ORB_Unadvertise();
extern int          ORB_Publish();
extern int          ORB_PublishAuto();

// Funtional interface for subscriber
extern int ORB_Subscribe();
extern int ORB_SubscribeMulti();
extern int ORB_Unsubscribe();
extern int ORB_Copy();

// Additional functions
extern int ORB_Copy();
extern int ORB_Check();
extern int ORB_Exists();
extern int ORB_SetInterval();
extern int ORB_GetInterval();
