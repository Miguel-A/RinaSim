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

#ifndef RMTBASE_H_
#define RMTBASE_H_

#include <omnetpp.h>

class RMTBase : public cSimpleModule
{
  public:
    RMTBase();
    virtual ~RMTBase();

    virtual bool isOnWire() = 0;
    virtual bool getRelayStatus() = 0;
    virtual void preQueueArrival(cObject* obj) = 0;
    virtual void postQueueArrival(cObject* obj) = 0;
    virtual void preQueueDeparture(cObject* obj) = 0;
    virtual void postQueueDeparture(cObject* obj) = 0;
    virtual void writeToPort(cObject* obj) = 0;
    virtual void readFromPort(cObject* obj) = 0;

  protected:
    virtual void initialize() = 0;
    virtual void handleMessage(cMessage *msg) = 0;

};

#endif /* RMTBASE_H_ */
