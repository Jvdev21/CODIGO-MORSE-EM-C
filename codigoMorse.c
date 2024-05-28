//Converte os caracteres em dados char
char charecters[] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '!', '"', '$', '&', '(', ')', '_', '+', '=', '-', ':', ';', '@', '\'', ',', '.', '/', '?', ' '};
char* morse[] = {".-", "-...", "-.-.", "-..", ".", "..-.", "--.", "....", "..", ".---", "-.-", ".-..", "--", "-.", "---", ".--.", "--.-", ".-.", "...", "-", "..-", "...-", ".--", "-..-", "-.--", "--..", "-----", ".----", "..---", "...--", "....-", ".....", "-....", "--...", "---..", "----.", "-·-·--", "·-··-·", "···-··-", "·-···", "-·--·", "-·--·-", "··--·-", "·-·-·", "-···-", "-····-", "---···", "-·-·-·", "·--·-·", "·----·", "--··--", "·-·-·-", "-··-·", "··--··", " "};
int len = 55;

//instancia em que pino o buzzer vai ficar
int buzzerpin = 12 ;

int dotLen = 150;    // Você pode ajustar a velocidade dos bips aqui
int dashLen = dotLen * 3;
int elemGap = dotLen;
int charGap = dotLen * 2;
int Space = dotLen * 6;

char charDelimiter = '@'; // Usa isso para separar os caracteres

String inputString = "";
boolean stringComplete = false;

void setup() {
  Serial.begin(9600);
  pinMode(buzzerpin, OUTPUT);
  inputString.reserve(200);
}

void loop() {
  serialEvent();
  if (stringComplete) {
    Serial.println(inputString); //imprime no monitor seria a mensagem que você escreveu
    String code = toMorse(inputString); 
    Display(code);
    inputString = "";
    stringComplete = false;
  }
}

String toMorse(String inputString) {
  inputString.toLowerCase();
  int inputString_len = inputString.length() + 1;
  char char_array[inputString_len];
  inputString.toCharArray(char_array, inputString_len);
  String finalcode = "";
  for (int i = 0; i < inputString_len; i++) {
    for (int n = 0; n < len; n++) {
      if (char_array[i] == charecters[n] )
      {
        finalcode += morse[n];
        finalcode += charDelimiter; 
      }
    }
  }
  return finalcode;
}

String toString(String code) {
  
  return "";
}

void Display(String code) {
  int code_len = code.length() + 1;
  char code_array[code_len];
  code.toCharArray(code_array, code_len);
  for (int i = 0; i < code_len; i++) {
    if (code_array[i] == '.')
    {
     
      digitalWrite(buzzerpin, HIGH);
      delay(dotLen);
      
      digitalWrite(buzzerpin , LOW);
      delay(elemGap);
      Serial.print(code_array[i]);
    }
    else if (code_array[i] == '-')
    {
     
      digitalWrite(buzzerpin , HIGH);
      delay(dashLen);
      
      digitalWrite(buzzerpin, LOW);
      delay(elemGap);
      Serial.print(code_array[i]);
    }
    else if (code_array[i] == ' ')
    {
      delay(Space);
      Serial.print("   ");
    }
    else if (code_array[i] == charDelimiter)
    {
      delay(charGap);
      Serial.print(" ");
    }
  }
  Serial.println();
  Serial.println("Pronto");
}
void serialEvent() {
  while (Serial.available()) {
    char inChar = (char)Serial.read();
    inputString += inChar;
    if (inChar == '\n') {
      stringComplete = true;
    }
  }
}