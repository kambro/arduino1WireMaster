arduinoOneWireMaster
====================

Program arduinoOneWireMaster pozwala na komunikację z urządzeniami wpiętymi do szyny 1-wire.

Program wymaga biblioteki https://github.com/interactive-matter/aJson.git

Sposób podłączenia czujnika DS18B20 do szyny 1-wire arduino https://www.hacktronics.com/Tutorials/arduino-1-wire-tutorial.html

Przykłady zapytań:
 -  {"command":"list-devices"}
 -  {"command":"send-data-to-device", "address": "01ADDACEF0000BB", "value": "BE"}
 -  {"command":"send-data-to-device", "address": "28475D7202000077", "value": "BE"} -> {"data": "50054B467FFF0C101C", "crc": "1C"}
 -  {"command":"send-data-to-device", "address": "28475D7202000077", "value": "BE", "pin-state": 0}
 -  [{"command":"send-data-to-device", "address": "28475D7202000077", "value": "BE", "pin-state": 0}, {"command":"send-data-to-device", "address": "28475D7202000077", "value": "BE", "pin-state": 0}]
 -  [{"command":"list-devices"}, {"command":"send-data-to-device", "address": "28475D7202000077", "value": "BE", "pin-state": 0}]
 -  {"command":"send-data-to-device", "address": "01ADDACE0F0000BB", "value": "CC", "pin-state": 1}
 -  {"command":"send-data-to-device", "address": "01ADDACE0F0000BB", "value": "55", "pin-state": 1}
 -  {"command":"send-data-to-device", "address": "01ADDACE0F0000BB", "value": "33", "pin-state": 0}
 -  {"command":"send-data-to-device", "address": "01ADDACE0F0000BB", "value": "F0", "pin-state": 1} 
