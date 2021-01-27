void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
}

void loop() {
  String data = Serial.readString();
  Serial.println(getData(data));

}

String getData(String Gcode) {

    // G1   X123.123 Y134.132 Z123.163 E000.000

    String Line = "";
    
    if(Gcode.substring(0,5) == "G1   ") {
        Line += "X: " + Gcode.substring(7, 14);
        Line += "Y: " + Gcode.substring(16, 23);
        Line += "Z: " + Gcode.substring(25, 32);
        Line += "E: " + Gcode.substring(34, 41);

    } else if(Gcode.substring(0, 5) == "M109 " || Gcode.substring(0, 5) == "M104 ") {
        Line = "S: " + Gcode.substring(6, 9);
    } else if(Gcode.substring(0, 5) == "G92  ") {

        if(Gcode[5] == 'E') {
            Line = "E_RESET: " + Gcode.substring(6, 13);
        } else if(Gcode[5] == 'X') {
            Line = "X_RESET: " + Gcode.substring(6, 13);
        } else if(Gcode[5] == 'Y') {
            Line = "Y_RESET: " + Gcode.substring(6, 13);
        } else if(Gcode[5] == 'Z') {
            Line = "Z_RESET: " + Gcode.substring(6, 13);
        }
    }

    return Line;
}
