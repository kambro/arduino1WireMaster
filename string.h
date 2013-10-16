long hex2int(char *a, unsigned int len) {
    int i;
    unsigned long val = 0;

    for(i=0;i<len;i++)
       if(a[i] <= 57)
    	val += (a[i]-48)*(1<<(4*(len-1-i)));
       else
    	val += (a[i]-55)*(1<<(4*(len-1-i)));
    return val;
}

void convert_char_arr_to_byte_arr(char *input, unsigned char output[], unsigned int length_limit) {
  unsigned int length = round((strlen(input) / 2.0));
  char buffer[3] = "";

  if (length > length_limit) {
    length = length_limit - 1;
  }

  for (int counter = 0; counter < length; counter++) {
    int caret_position = 0;
 
    buffer[caret_position++] = input[counter * 2];
 
    if (input[counter + 1] != '\0') {
      buffer[caret_position++] = input[(counter * 2) + 1];
    }
    
    buffer[caret_position++] = '\0';
    output[counter] = (byte) hex2int(buffer, 2);
  }
}
