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

cplusplus {{
#define PDU_HEADER_LEN 10
#include "Address.h"
#include "APN.h"
#include "ConnectionId.h"
//#include "UserDataField.h"

//typedef cMessage* cMessagePtr;
//typedef cObject* cObjectPtr;
//typedef UserDataField* UserDataFieldPtr;

}}
class noncobject Address;
class noncobject APN;
class noncobject ConnectionId;
//class noncobject cMessagePtr;
//class noncobject cObjectPtr;





enum PDUType{
    	EFCP_PDU 				= 0x8000;
    	DATA_TRANSFER_PDU 		= 0x8001;
    	CONTROL_ACK_PDU 		= 0x8003;
        ACK_ONLY_PDU 			= 0x8804;
        NACK_ONLY_PDU 			= 0x8805;
        SELECT_ACK_PDU 			= 0x8806;
        SELECT_NACK_PDU 		= 0x8807;
        FLOW_ONLY_PDU 			= 0x8808;
        ACK_FLOW_PDU 			= 0x880C;
        NACK_FLOW_PDU 			= 0x880D;
        SELECT_ACK_FLOW_PDU 	= 0x880E;
        SELECT_NACK_FLOW_PDU 	= 0x880F;

}

enum PDUTypeBits{
    	PDU_NACK_BIT	= 0x01;
    	PDU_SEL_BIT		= 0x02;
    	PDU_ACK_BIT		= 0x04;
    	PDU_FC_BIT		= 0x08;
}

//TODO A1
enum FLAGS{
}



packet PDU {
    @customize(true);
    string displayString;
    unsigned int version = 1;
    Address srcAddr;
    Address dstAddr;
    APN srcApn; 
    APN dstApn;  
    ConnectionId connId;
    int type enum(PDUType);
    int flags = 0; //8bits
    unsigned int pduLen = PDU_HEADER_LEN;
    unsigned int seqNum;
    unsigned int hopCount = 255;
    byteLength = 10;
    schedulingPriority = -1;
//    cObject userData; //unsigned char []? string?
//    unsigned char userData[];
//    cMessagePtr mUserData;
    
    
    
}

//packet DataTransferPDU extends PDU{
//    type = DATA_TRANSFER_PDU;
//    
//}





