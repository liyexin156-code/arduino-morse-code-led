int led = 8;

// A-Z Morse Code Mapping
const char* morseMap[26] = {
  ".-", "-...", "-.-.", "-..", ".", "..-.", "--.", "....", "..", ".---",
  "-.-", ".-..", "--", "-.", "---", ".--.", "--.-", ".-.", "...", "-",
  "..-", "...-", ".--", "-..-", "-.--", "--.."
};

// Timing 
int dotTime = 200;
int dashTime = 600;
int symbolGap = 200;
int letterGap = 600;
int wordGap = 1400;

// dot
void dot() {
  digitalWrite(led, HIGH);
  delay(dotTime);
  digitalWrite(led, LOW);
  delay(symbolGap);
}

// dash
void dash() {
  digitalWrite(led, HIGH);
  delay(dashTime);
  digitalWrite(led, LOW);
  delay(symbolGap);
}

// SHOW character
void playMorse(char c) {
  // 处理空格（单词间隔）
  if (c == ' ') {
    delay(wordGap);
    return;
  }

  // Turn to upper case
  if (c >= 'a' && c <= 'z') {
    c = c - 'a' + 'A';
  }

  // skip non letter
  if (c < 'A' || c > 'Z') return;

  const char* code = morseMap[c - 'A'];

  for (int i = 0; code[i] != '\0'; i++) {
    if (code[i] == '.') {
      dot();
    } else if (code[i] == '-') {
      dash();
    }
  }

  delay(letterGap); 
}

void setup() {
  pinMode(led, OUTPUT);
  Serial.begin(9600);

  Serial.println("Enter text to convert to Morse Code:");
}

void loop() {
  if (Serial.available()) {
    String input = Serial.readStringUntil('\n');

    for (int i = 0; i < input.length(); i++) {
      playMorse(input[i]);
    }

    Serial.println("Done.");
  }}
