#include "esphome.h"
#include "Wire.h"

class VELynxDistributor : public PollingComponent {
  public:
    BinarySensor *bus_bar = new BinarySensor();
    BinarySensor *fuse_1 = new BinarySensor();
    BinarySensor *fuse_2 = new BinarySensor();
    BinarySensor *fuse_3 = new BinarySensor();
    BinarySensor *fuse_4 = new BinarySensor();
    
    VELynxDistributor() : PollingComponent(10000) { }
 
    void setup() override {
      Wire.begin();
    }

    void update() override {
      unsigned char distributorState = 1;

      Wire.requestFrom(0x08,1);
      while(Wire.available()){
      distributorState = Wire.read();
            
      if (distributorState & (1 << 1)) {
        bus_bar->publish_state(false);
      }
      else {
        bus_bar->publish_state(true);

        fuse_1->publish_state(!(distributorState & (1 << 4)));
        fuse_2->publish_state(!(distributorState & (1 << 5)));
        fuse_3->publish_state(!(distributorState & (1 << 6)));
        fuse_4->publish_state(!(distributorState & (1 << 7)));
      }
    }      
  }
};