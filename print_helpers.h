
void print_content(char *content) {
  Serial.print(content);
}

void align_hex(byte data, char *aligned_hex) {
  char buffer[8] = "";
  sprintf(buffer, "%X", data);

  sprintf(aligned_hex, "%s%s", (1 == strlen(buffer) ? "0" : ""), buffer);
}

void convert_byte_array_to_char_array(unsigned int size, byte source[], char destination[]) {
  unsigned int i;
  
  for (i = 0; i < size; i++) {
    align_hex(source[i], &(destination[i*2]));
  }
  destination[(i * 2) + 1] = '\0';
}

void print_aligned_hex(byte data) {
  char buffer[8] = "";
  align_hex(data, buffer);
  print_content(buffer);
}

void print_address_section(unsigned char *address) {
  print_content("\"address\": \"");

  for(int i = 0; i < 8; i++) {
    print_aligned_hex(address[i]);
  }  

  print_content("\"");
}

void print_data_section(char *addr, OneWire ds) {
  char data[64];
  char buffer[128] = "";
  int i;

  for (i = 0; i < 9; i++) {
    align_hex(ds.read(), &(data[i*2]));
  }

  data[(i * 2) + 1] = '\0';

  sprintf(buffer, "{\"address\": \"%s\", \"crc\": \"%X\", \"data\": \"%s\"}", addr, addr[7], data);

  print_content(buffer);
}

void print_crc32_error_message(unsigned char addr[]) {
  char buffer[128] = "";
  char address[32];

  convert_byte_array_to_char_array(8, addr, address);

  sprintf(buffer, "{\"address\": \"%s\", \"crc\": \"%X\", \"calculatedCRC\": \"%X\", \"message\": \"CRC is not valid\"}", address, addr[7], OneWire::crc8(addr, 7));

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
