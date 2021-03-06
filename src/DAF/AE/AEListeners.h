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

#ifndef AELISTENERS_H_
#define AELISTENERS_H_

//Standard libraries
#include <omnetpp.h>
//RINASim libraries
#include "AE.h"

class AE;
class AEListeners : public cListener {
  public:
    AEListeners(AE* nae);
    virtual ~AEListeners();

    virtual void receiveSignal(cComponent *src, simsignal_t id, bool b) {
        EV << "Signal to AE initiated by " << src->getFullPath() << endl;
    }
  protected:
    AE* ae;
};

class LisAEReceiveData : public AEListeners {
  public:
    LisAEReceiveData(AE* nae) : AEListeners(nae){};
    void virtual receiveSignal(cComponent *src, simsignal_t id, cObject *obj);
};

class LisAEAllReqFromFai : public AEListeners {
  public:
    LisAEAllReqFromFai(AE* nae) : AEListeners(nae){};
    void virtual receiveSignal(cComponent *src, simsignal_t id, cObject *obj);
};

class LisAEDeallReqFromFai : public AEListeners {
  public:
    LisAEDeallReqFromFai(AE* nae) : AEListeners(nae){};
    void virtual receiveSignal(cComponent *src, simsignal_t id, cObject *obj);
};

class LisAEAllResPosi : public AEListeners {
  public:
    LisAEAllResPosi(AE* nae) : AEListeners(nae){};
    void virtual receiveSignal(cComponent *src, simsignal_t id, cObject *obj);
};

class LisAEAllResNega : public AEListeners {
  public:
    LisAEAllResNega(AE* nae) : AEListeners(nae){};
    void virtual receiveSignal(cComponent *src, simsignal_t id, cObject *obj);
};

class LisAEConResPosi : public AEListeners {
  public:
    LisAEConResPosi(AE* nae) :  AEListeners(nae){};
    void virtual receiveSignal(cComponent *src, simsignal_t id, cObject *obj);
};

class LisAEConResNega : public AEListeners {
  public:
    LisAEConResNega(AE* nae) :  AEListeners(nae){};
    void virtual receiveSignal(cComponent *src, simsignal_t id, cObject *obj);
};

class LisAERelRes : public AEListeners {
  public:
    LisAERelRes(AE* nae) :  AEListeners(nae){};
    void virtual receiveSignal(cComponent *src, simsignal_t id, cObject *obj);
};

#endif /* AELISTENERS_H_ */
