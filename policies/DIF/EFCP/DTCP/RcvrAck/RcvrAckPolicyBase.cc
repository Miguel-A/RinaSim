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
/**
 * @file RcvrAckPolicyBase.cc
 * @author Marcel Marek (imarek@fit.vutbr.cz)
 * @date Jan 5, 2015
 * @brief
 * @detail
 */

#include "RcvrAckPolicyBase.h"
#include "DTP.h"

RcvrAckPolicyBase::RcvrAckPolicyBase()
{


}

RcvrAckPolicyBase::~RcvrAckPolicyBase()
{

}

void RcvrAckPolicyBase::defaultAction(DTPState* dtpState, DTCPState* dtcpState)
{
  DTP* dtp = getRINAModule<DTP*>(this, 1, {MOD_DTP});
  /* Default */

      unsigned int seqNum = dtpState->getRcvLeftWinEdge() - 1;

      if(dtpState->getRcvLeftWinEdge() == 0){
        seqNum = 0;
      }

      if (dtcpState->isImmediate())
      {
        //Update LeftWindowEdge removing allowed gaps;
        dtpState->updateRcvLWE(seqNum);
  //      unsigned int sduGap =  dtpState->getQoSCube()->getMaxAllowGap();
  //
  //      PDUQ_t::iterator it;
  //      PDUQ_t* pduQ = dtpState->getReassemblyPDUQ();
  //      for (it = pduQ->begin(); it != pduQ->end(); ++it)
  //      {
  //        if((*it)->getSeqNum() == dtpState->getRcvLeftWinEdge()){
  //          dtpState->incRcvLeftWindowEdge();
  //
  //        }else if((*it)->getSeqNum() < dtpState->getRcvLeftWinEdge()){
  //          continue;
  //        }else {
  //          if(pduQ->size() == 1 || it == pduQ->begin()){
  //            if((*it)->getSDUSeqNum() <= dtpState->getLastSduDelivered() + sduGap){
  //              dtpState->setRcvLeftWinEdge((*it)->getSeqNum());
  //            }
  //          }else{
  //            (*(it-1))->getSDUGap((*it));
  //          }
  //          break;
  //        }
  //      }

        //send an Ack/FlowControlPDU
        dtp->sendAckFlowPDU(seqNum, true);


        //stop any A-Timers asscociated with !!! this PDU !!! and earlier ones.
        //XXX How could there be any A-Timer when isImmediate returned true?

      }
      else
      {
        //set A-timer for this PDU
        dtp->startATimer(seqNum);
      }

      /* End default */
}
