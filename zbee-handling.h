#include <XBee.h>

XBee xbee = XBee();

using namespace zb;

bool has_received_presync{false};
int presync_sending_round{0};
Rx16Response rx16 = Rx16Response();

void _send16(uint16_t target, uint8_t* payload, size_t size) {
  Tx16Request tx=Tx16Request(target, payload, size);
  xbee.send(tx);
}

void handle_zb_as_cd(uint16_t target) {
  uint8_t payload[2] {1, 0};
  _send16(target, payload, sizeof(payload));
}

void handle_zb_as_cd() {
  if(presync_sending_round<=2) {
    handle_zb_as_cd(0x0002);
  } else {
    handle_zb_as_cd(0x0003);
  }
  presync_sending_round++;
}

void handle_zb_as_ed() {
  xbee.readPacket();
  if(!xbee.getResponse().isAvailable()) {
    //nothing to read
    return;
  }
  if(!xbee.getResponse().getApiId() == RX_16_RESPONSE) {
    //not something we expect, so dump it
    return;
  }
  has_received_presync=true;
}

constexpr long zb_bump_thrs=250;
timer_ms time_since_last_bump_via_zb{zb_bump_thrs+1};
/*
enum data_type : char {
  BUMP='B',
  HEARTBEAT='H',
};*/

void _heartbeat(uint16_t target) {
  uint8_t payload[1]={HEARTBEAT};
  _send16(target, payload, sizeof(payload));
}

int fight_state= 0;

void handle_zb_as_mk() {
  if(iterations_passed%64==0) {
    _heartbeat(0x0001);
  }
  
  xbee.readPacket();
  auto response=xbee.getResponse();
  if(!response.isAvailable() || response.isError()) {
    //nothing to read
    return;
  }
  if(response.getApiId() != RX_16_RESPONSE) {
    //not something we expect
    return;
  }

  //at this point we have actual data
  response.getRx16Response(rx16);
  switch(rx16.getData()[0]) {
    case BUMP: {
      fight_state = 1;
      //Serial.println("ghj");
    } break;

    case BUMP_N2M: {
      fight_state = 2;
      //Serial.println("jhg");
    } break;

    case TDD_BEGIN: {
      scene = 3;
    }

    case HEARTBEAT: {
      //do nothing
    } break;

    default: break;
  }
}
