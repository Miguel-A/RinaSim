//
// The MIT License (MIT)
//
// Copyright (c) 2014-2016 Brno University of Technology, PRISTINE project
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.

#ifndef DLMonitor_H_
#define DLMonitor_H_

#include "SmartMonitor.h"

#include <string>
#include <map>
#include <vector>
#include <list>

namespace BEMonitor {

using namespace std;

typedef list<RMTQueue*> QueuesList;
typedef map<RMTPort*, RMTQueue* > port2Queue;
typedef map<RMTPort*, QueuesList > port2Queues;
typedef map<RMTPort*, unsigned int > port2Count;


class BEMonitor : public SmartMonitor
{
public:
    void onPolicyInit();
    void onMessageArrival(RMTQueue* queue);
    void onMessageDeparture(RMTQueue* queue);
    void onMessageDrop(RMTQueue* queue, const cPacket* pdu);
    void postQueueCreation(RMTQueue* queue);

    int getInCount(RMTPort* port);
    int getInThreshold(RMTQueue * queue);
    RMTQueue* getNextInput(RMTPort* port);

    int getOutCount(RMTPort* port);
    int getOutThreshold(RMTQueue * queue);
    RMTQueue* getNextOutput(RMTPort* port);

    queueStat getInStat(RMTQueue * queue);
    queueStat getOutStat(RMTQueue * queue);

  protected:
    port2Queues inQ, outQ;
    port2Count inC, outC;
};

}

#endif /* SIMPLEMONITOR_H_ */
