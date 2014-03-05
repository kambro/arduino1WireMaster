#include <OneWire.h>
#include <aJSON.h>

#include "string.h"
#include "print_helpers.h"

#define BUFFER_SIZE 4096
#define DEVICE_PIN  3

OneWire ds(DEVICE_PIN);

void setup(void) {
  Serial.begin(115200);
}

void send_data_to_one_wire_device(char *address, char *input, byte pin_state) {
  unsigned char buffer[128];
  unsigned int bytes_number = round((strlen(input) / 2.0));
  unsigned int counter;
  unsigned char address_as_byte_array[8];
  convert_char_arr_to_byte_arr(address, address_as_byte_array, 8);

  convert_char_arr_to_byte_arr(input, buffer, 128);
  
  ds.reset();
  ds.select(address_as_byte_array);
  
  for (counter = 0; counter < bytes_number; counter++) {
    ds.write(buffer[counter], pin_state);
  }
  
  print_data_section(address, ds);
}

void processMessage(char *content) {
  aJsonObject* root = aJson.parse(content);
  aJsonObject* node = root;
  unsigned char counter = 0;
  unsigned char is_regular_array = content[0] == '[' && content[strlen(content) - 1] == ']';
  unsigned char items_number = is_regular_array ? aJson.getArraySize(root) : -1;

  if (NULL != root) {    
    if (is_regular_array) {
      print_content("[");
    }
    
    do {
      if (1 == is_regular_array && items_number > 0) {
        node = aJson.getArrayItem(root, counter);
      }
      
      aJsonObject *commandObject = aJson.getObjectItem(node, "command");
      aJsonObject *sessionIdObject = aJson.getObjectItem(node, "session-id");

      if (NULL != commandObject && commandObject->type == aJson_String) {
        if (0 == strcmp(commandObject->valuestring, "list-devices")) {
          list_one_wire_devices(ds);
        } else if (0 == strcmp(commandObject->valuestring, "send-data-to-device")) {
          aJsonObject *address = aJson.getObjectItem(node, "address");
          aJsonObject *value = aJson.getObjectItem(node, "value");
          aJsonObject *pin_state = aJson.getObjectItem(node, "pin-state");
          
          if (NULL != address && NULL != value) {

            send_data_to_one_wire_device(address->valuestring, value->valuestring, NULL == pin_state ? 0 : pin_state->valueint);
          }
        }
      } else {
          print_content("{\"message\": \"no data\"}");
          return;
      }
/*      
      if (NULL != sessionIdObject && sessionIdObject->type == aJson_String) {
          print_content("\", \"session-id\": \"");
          print_content(sessionIdObject->valuestring);
          print_content("\"");
      }
*/      
      counter++;
      
      if (1 == is_regular_array && items_number > counter) {
        print_content(",");
      }
    } while(1 == is_regular_array && items_number > counter);

    if (is_regular_array) {
      print_content("]");
    }
    print_content("\n");
    aJson.deleteItem(root);
  }
}

void loop(void) {
  char buffer[BUFFER_SIZE] = "";
  int lastChar = '\0';
  int counter = 0;
  
  if(Serial.available() > 0) {
    Serial.readBytes(buffer, BUFFER_SIZE);

    if (strlen(buffer) > 0) {
      processMessage(buffer);
    }
  }  
}





