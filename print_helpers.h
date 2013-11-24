
void print_content(char *content) {
  Serial.print(content);
  Serial.flush();
}

void print_aligned_hex(byte data) {
  char buffer[24] = "";
  sprintf(buffer, "%X", data);

  if (1 == strlen(buffer)) {
    print_content("0");
  }

  print_content(buffer);
}

void print_address_section(unsigned char *address) {
  print_content("\"address\": \"");

  for(int i = 0; i < 8; i++) {
    print_aligned_hex(address[i]);
  }  

  print_content("\"");
}

void print_data_section(OneWire ds) {
  unsigned char data[24];
  
  print_content("{\"data\": \"");

  for (int i = 0; i < 9; i++) {
    data[i] = ds.read();
    print_aligned_hex(data[i]);  
  }

  print_content("\", \"crc\": \"");

  print_aligned_hex((byte) OneWire::crc8(data, 8));  

  print_content("\"}");
}

void print_crc32_error_message(unsigned char addr[]) {
  char buffer[128] = "";
  sprintf(buffer, "{\"address\": \"%s\", \"crc\": \"%X\", \"calculatedCRC\": \"%X\", \"message\": \"CRC is not valid\"}", addr, addr[7], OneWire::crc8(addr, 7));
  print_content(buffer);
}

void list_one_wire_devices(OneWire ds) {
  byte i;
  unsigned char addr[8];

  print_content("[");

  for (int counter = 0; ds.search(addr); counter++) {

    if (counter > 0) {
      print_content(",");
    }

    if (OneWire::crc8(addr, 7) != addr[7]) {
      print_crc32_error_message(addr);
      continue;
    }
  
    print_content("{");
    print_address_section(addr);    
    print_content("}");
  }
  
  print_content("]");
  
  ds.reset_search();
}
