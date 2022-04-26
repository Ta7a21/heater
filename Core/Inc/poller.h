#ifndef INC_POLLER_H_
#define INC_POLLER_H_

#include <utils.h>

void Poll(void);
void StartPolling(void);
void StopPolling(void);
void SetPollingTime(uint32_type polling_time);

#endif /* INC_POLLER_H_ */
