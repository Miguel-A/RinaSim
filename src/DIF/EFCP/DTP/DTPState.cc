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

#include "DTPState.h"

Define_Module(DTPState);

DTPState::DTPState() {


  initDefaults();
}

double DTPState::getMPL() const
{
  return mpl;
}

void DTPState::setMpl(double mpl)
{
  this->mpl = mpl;
}

bool DTPState::isBlockingPort() const
{
  return blockingPort;
}

void DTPState::setBlockingPort(bool blockingPort)
{
  this->blockingPort = blockingPort;
}

void DTPState::initialize(int step)
{
  if(step == 0){

    cDisplayString& disp = getDisplayString();
    disp.setTagArg("p", 0, 240);
    disp.setTagArg("p", 1, 50);

    maxFlowSDUSize = par("maxSDUSize");
    maxFlowPDUSize = par("maxPDUSize");

    rtt = par("rtt");
    if(getRINAModule<cModule*>(this, 2, {MOD_EFCP})->hasPar("rtt")){
      rtt = getRINAModule<cModule*>(this, 2, {MOD_EFCP})->par("rtt");

    }

    mpl = par("mpl");
    if(getRINAModule<cModule*>(this, 2, {MOD_EFCP})->hasPar("mpl")){
      mpl = getRINAModule<cModule*>(this, 2, {MOD_EFCP})->par("mpl");

    }


////    winBased = par("winBased");
////    rateBased = par("rateBased");
//    rateBased = false;
//
////    rxPresent = par("rxPresent");
//
//    if(qoSCube->isRxOn()){
//      rxPresent = true;
//    }else{
//      rxPresent = false;
//    }
    rxPresent = qoSCube->isRxOn();
    winBased = qoSCube->isWindowFcOn();
    rateBased = qoSCube->isRateFcOn();

//    if(qoSCube->getAvgBand() > 0){
//      winBased = true;
//    }else{
//      winBased = false;
//    }

    if(rxPresent || winBased || rateBased){
      dtcpPresent =  true;

    }
  }
}


void DTPState::initDefaults(){

  currentPDU = NULL;
  dropDup = 0;
  setDRFFlag = true;
  dtcpPresent = false;
  winBased = false;
  rateBased = false;
  incompDeliv = false;


  lastSDUDelivered = 0;
  rcvLeftWinEdge = 0;
  maxSeqNumRcvd = 0;
  nextSeqNumToSend = 1;
  qoSCube = NULL;

  seqNumRollOverThresh = INT_MAX - 1;
  lastSeqNumSent = 0;
  ecnSet = false;

  blockingPort = false;

}

void DTPState::clearPDUQ(std::vector<DataTransferPDU*>* pduQ)
{
  std::vector<DataTransferPDU*>::iterator itP;
  for (itP = pduQ->begin(); itP != pduQ->end();)
  {
    delete (*itP);
    //    delete (*it);
    itP = pduQ->erase(itP);
  }
}



void DTPState::clearReassemblyPDUQ()
{
  clearPDUQ(&reassemblyPDUQ);
}

void DTPState::clearGeneratedPDUQ()
{
  clearPDUQ(&generatedPDUs);
}

void DTPState::clearPostablePDUQ()
{
  clearPDUQ(&postablePDUs);
}

DTPState::~DTPState() {

  clearReassemblyPDUQ();
  clearGeneratedPDUQ();
  clearPostablePDUQ();
}

bool DTPState::isDtcpPresent() const {
    return dtcpPresent;
}

void DTPState::setDtcpPresent(bool dtcpPresent) {
    this->dtcpPresent = dtcpPresent;
}

bool DTPState::isIncompDeliv() const {
    return incompDeliv;
}

void DTPState::setIncompDeliv(bool incompDeliv) {
    this->incompDeliv = incompDeliv;
}

unsigned int DTPState::getMaxFlowPduSize() const {
    return maxFlowPDUSize;
}

void DTPState::setMaxFlowPduSize(unsigned int maxFlowPduSize) {
    maxFlowPDUSize = maxFlowPduSize;
}

unsigned int DTPState::getMaxFlowSduSize() const {
    return maxFlowSDUSize;
}

void DTPState::setMaxFlowSduSize(unsigned int maxFlowSduSize) {
    maxFlowSDUSize = maxFlowSduSize;
}

unsigned int DTPState::getMaxSeqNumRcvd() const {
    return maxSeqNumRcvd;
}

void DTPState::setMaxSeqNumRcvd(unsigned int maxSeqNumRcvd) {

    this->maxSeqNumRcvd = (this->maxSeqNumRcvd > maxSeqNumRcvd) ? this->maxSeqNumRcvd : maxSeqNumRcvd;
}

void DTPState::incMaxSeqNumRcvd() {
  maxSeqNumRcvd++;
}

void DTPState::incRcvLeftWindowEdge() {
  rcvLeftWinEdge++;
}

/*
 * Returns value of nextSeqNumToSend and increments it
 * @return nextSeqNumToSend
 */
unsigned int DTPState::getNextSeqNumToSend() {

    return nextSeqNumToSend++;
}

unsigned int DTPState::getNextSeqNumToSendWithoutIncrement() {

    return nextSeqNumToSend;
}

void DTPState::setNextSeqNumToSend(unsigned int nextSeqNumToSend) {
    this->nextSeqNumToSend = nextSeqNumToSend;
}

void DTPState::incNextSeqNumToSend(){
  //TODO A1 what about threshold?
  this->nextSeqNumToSend++;
}

bool DTPState::isPartDeliv() const {
    return partDeliv;
}

void DTPState::setPartDeliv(bool partDeliv) {
    this->partDeliv = partDeliv;
}

bool DTPState::isRateBased() const {
    return rateBased;
}

void DTPState::setRateBased(bool rateBased) {
    this->rateBased = rateBased;
}

//bool DTPState::isRateFullfilled() const {
//    return rateFullfilled;
//}
//
//void DTPState::setRateFullfilled(bool rateFullfilled) {
//    this->rateFullfilled = rateFullfilled;
//}

unsigned int DTPState::getRcvLeftWinEdge() const {
    return rcvLeftWinEdge;
}

void DTPState::setRcvLeftWinEdge(unsigned int rcvLeftWinEdge) {
    this->rcvLeftWinEdge = rcvLeftWinEdge;
}

bool DTPState::isRxPresent() const {
    return rxPresent;
}

void DTPState::setRxPresent(bool rexmsnPresent) {
    this->rxPresent = rexmsnPresent;
}

unsigned int DTPState::getSeqNumRollOverThresh() const {
    return seqNumRollOverThresh;
}

void DTPState::setSeqNumRollOverThresh(unsigned int seqNumRollOverThresh) {
    this->seqNumRollOverThresh = seqNumRollOverThresh;
}

int DTPState::getState() const {
    return state;
}

void DTPState::setState(int state) {
    this->state = state;
}

bool DTPState::isWinBased() const {
    return winBased;
}

void DTPState::setWinBased(bool winBased) {
    this->winBased = winBased;
}

bool DTPState::isSetDrfFlag() const
{
  return setDRFFlag;
}

double DTPState::getRtt() const
{
  //TODO B1 RTT estimator policy
  return rtt;
}

void DTPState::setRtt(double rtt)
{
  this->rtt = rtt;
}

void DTPState::setSetDrfFlag(bool setDrfFlag)
{
  setDRFFlag = setDrfFlag;
}

unsigned int DTPState::getLastSeqNumSent() const
{
  return lastSeqNumSent;
}

void DTPState::setLastSeqNumSent(unsigned int lastSeqNumSent)
{
  this->lastSeqNumSent = lastSeqNumSent;
}

bool DTPState::isEcnSet() const
{
  return ecnSet;
}

void DTPState::setEcnSet(bool ecnSet)
{
  this->ecnSet = ecnSet;
}

const PDU* DTPState::getCurrentPdu() const
{
  return currentPDU;
}

void DTPState::setCurrentPdu(PDU* currentPdu)
{
  currentPDU = currentPdu;
}



std::vector<DataTransferPDU*>* DTPState::getReassemblyPDUQ()
{
  return &reassemblyPDUQ;
}

void DTPState::pushBackToReassemblyPDUQ(DataTransferPDU* pdu)
{
//TODO A2 check if this PDU is already on the queue (I believe the FSM is broken and it might try to add one PDU twice)

  take(pdu);
  reassemblyPDUQ.push_back(pdu);
}

void DTPState::addPDUToReassemblyQ(DataTransferPDU* pdu)
{

  if (pdu != NULL)
  {
    take(pdu);
    if (reassemblyPDUQ.empty())
    {
      reassemblyPDUQ.push_back(pdu);
    }
    else
    {
      if (reassemblyPDUQ.front()->getSeqNum() > pdu->getSeqNum())
      {
        reassemblyPDUQ.insert(reassemblyPDUQ.begin(), pdu);
      }
      else
      {
        for (std::vector<DataTransferPDU*>::iterator it = reassemblyPDUQ.begin(); it != reassemblyPDUQ.end(); ++it)
        {
          if ((*it)->getSeqNum() == pdu->getSeqNum())
          {
            //Not sure if this case could ever happen; EDIT: No, this SHOULD not ever happen.
            //Throw Error.
            throw cRuntimeError("addPDUTo reassemblyQ with same seqNum. SHOULD not ever happen");
          }
          else if ((*it)->getSeqNum() > pdu->getSeqNum())
          {
            /* Put the incoming PDU before one with bigger seqNum */
            reassemblyPDUQ.insert(it, pdu);
            break;
          }
          else if (it == --reassemblyPDUQ.end())
          {
            //'it' is last element
            reassemblyPDUQ.insert(it + 1, pdu);
            break;
          }
        }
      }
    }
  }
}


PDUQ_t* DTPState::getGeneratedPDUQ(){

  return &generatedPDUs;
}

void DTPState::pushBackToGeneratedPDUQ(DataTransferPDU* pdu)
{
  generatedPDUs.push_back(pdu);
}

PDUQ_t* DTPState::getPostablePDUQ(){

  return &postablePDUs;
}

void DTPState::pushBackToPostablePDUQ(DataTransferPDU* pdu){
 postablePDUs.push_back(pdu);
}

unsigned int DTPState::getDropDup() const
{
  return dropDup;
}

const QoSCube* DTPState::getQoSCube() const
{
  return qoSCube;
}

unsigned int DTPState::getLastSduDelivered() const
{
  return lastSDUDelivered;
}

void DTPState::setLastSduDelivered(unsigned int lastSduDelivered)
{
  lastSDUDelivered = lastSduDelivered;
}

void DTPState::setQoSCube(const QoSCube*& qoSCube)
{
  this->qoSCube = qoSCube;
}

void DTPState::updateRcvLWE(unsigned int seqNum)
{
  //TODO A3
  //Update LeftWindowEdge removing allowed gaps;
  unsigned int sduGap = qoSCube->getMaxAllowGap();

  if (isDtcpPresent())
  {
    PDUQ_t::iterator it;
    PDUQ_t* pduQ = &reassemblyPDUQ;
    for (it = pduQ->begin(); it != pduQ->end(); ++it)
    {
      if ((*it)->getSeqNum() == getRcvLeftWinEdge())
      {
        incRcvLeftWindowEdge();

      }
      else if ((*it)->getSeqNum() < getRcvLeftWinEdge())
      {
        continue;
      }
      else
      {
        if (pduQ->size() == 1 || it == pduQ->begin())
        {
          if ((*it)->getSDUSeqNum() <= getLastSduDelivered() + sduGap)
          {
            setRcvLeftWinEdge((*it)->getSeqNum());
          }
        }
        else
        {
          (*(it - 1))->getSDUGap((*it));
        }
        break;
      }
    }
  }
  else
  {
    setRcvLeftWinEdge(std::max(getRcvLeftWinEdge(), seqNum));
//    if(state.getRcvLeftWinEdge() > timer->getSeqNum()){
//         throw cRuntimeError("RcvLeftWindowEdge SHOULD not be bigger than seqNum in A-Timer, right?");
//       }else{
//         state.setRcvLeftWinEdge(timer->getSeqNum());
//       }
  }



  if(getRcvLeftWinEdge() < seqNum){
    //TODO B1 Is it correct?
    //We did not manage to move the RLWE to seqNum even with A-Timer and allowed gap -> signal error
  }
}

void DTPState::handleMessage(cMessage* msg)
{
}

/* Dirty hacks */
ATimer* DTPState::getTmpAtimer() const
{
  return tmpAtimer;
}

void DTPState::setTmpAtimer(ATimer* tmpAtimer)
{
  this->tmpAtimer = tmpAtimer;
}

/* End dirty hacks */
