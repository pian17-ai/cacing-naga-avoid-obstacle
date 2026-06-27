// --- Konfigurasi Pin Sensor Ultrasonik ---
const int TRIG_KIRI = 5;
const int ECHO_KIRI = 18;

const int TRIG_TENGAH = 19;
const int ECHO_TENGAH = 21;

const int TRIG_KANAN = 22;
const int ECHO_KANAN = 23;

// --- Konfigurasi Pin Driver Motor L298N ---
const int IN1 = 26;
const int IN2 = 27;
const int IN3 = 14;
const int IN4 = 12;

const int ENA = 25;
const int ENB = 33;

// --- Penyesuaian Jarak & Kecepatan (Robot 20x15 cm) ---
const int JARAK_AMAN_DEPAN  = 17;
const int JARAK_AMAN_SAMPING = 7;

const int KECEPATAN_MAJU    = 230;  // Naik dari 180 → 230
const int KECEPATAN_SPRINT  = 255;  // Full speed: jalan lurus panjang / sensor 999
const int KECEPATAN_BELOK   = 180;
const int KECEPATAN_MUNDUR  = 140;

void setup() {
  Serial.begin(115200);

  pinMode(TRIG_KIRI,   OUTPUT); pinMode(ECHO_KIRI,   INPUT);
  pinMode(TRIG_TENGAH, OUTPUT); pinMode(ECHO_TENGAH, INPUT);
  pinMode(TRIG_KANAN,  OUTPUT); pinMode(ECHO_KANAN,  INPUT);

  pinMode(IN1, OUTPUT); pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT); pinMode(IN4, OUTPUT);
  pinMode(ENA, OUTPUT); pinMode(ENB, OUTPUT);

  stopRobot();
}

void loop() {
  int jarakKiri   = bacaJarak(TRIG_KIRI,   ECHO_KIRI);
  int jarakTengah = bacaJarak(TRIG_TENGAH, ECHO_TENGAH);
  int jarakKanan  = bacaJarak(TRIG_KANAN,  ECHO_KANAN);

  Serial.print("Ki: "); Serial.print(jarakKiri);
  Serial.print(" | Te: "); Serial.print(jarakTengah);
  Serial.print(" | Ka: "); Serial.println(jarakKanan);

  // --- Logika Navigasi ---
  if (jarakTengah > JARAK_AMAN_DEPAN) {

    // Sensor tidak mendeteksi apa-apa (999) → SPRINT penuh
    if (jarakTengah == 999) {
      majuSprint();
    } else {
      maju();
    }

  } else {
    stopRobot();
    delay(500);

    jarakKiri  = bacaJarak(TRIG_KIRI,  ECHO_KIRI);
    jarakKanan = bacaJarak(TRIG_KANAN, ECHO_KANAN);

    if (jarakKanan > JARAK_AMAN_SAMPING && jarakKanan >= jarakKiri) {
      belokKanan();
      delay(450);
      stopRobot();
      delay(100);
    } else if (jarakKiri > JARAK_AMAN_SAMPING) {
      belokKiri();
      delay(450);
      stopRobot();
      delay(100);
    } else {
      mundur();
      delay(250);
      stopRobot();
      delay(200);
      belokKanan();
      delay(750);
      stopRobot();
      delay(100);
    }
  }

  delay(30);
}

// --- Fungsi Membaca Jarak ---
int bacaJarak(int trigPin, int echoPin) {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  long durasi = pulseIn(echoPin, HIGH, 25000);
  if (durasi == 0) return 999;

  return durasi * 0.034 / 2;
}

// --- Fungsi Pergerakan ---

// Maju normal (ada jalan terbaca jelas)
void maju() {
  analogWrite(ENA, KECEPATAN_MAJU);
  analogWrite(ENB, KECEPATAN_MAJU);
  digitalWrite(IN1, HIGH); digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH); digitalWrite(IN4, LOW);
}

// Maju sprint: jalan panjang / sensor return 999
void majuSprint() {
  analogWrite(ENA, KECEPATAN_SPRINT);
  analogWrite(ENB, KECEPATAN_SPRINT);
  digitalWrite(IN1, HIGH); digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH); digitalWrite(IN4, LOW);
}

void mundur() {
  analogWrite(ENA, KECEPATAN_MUNDUR);
  analogWrite(ENB, KECEPATAN_MUNDUR);
  digitalWrite(IN1, LOW);  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);  digitalWrite(IN4, HIGH);
}

void belokKiri() {
  analogWrite(ENA, KECEPATAN_BELOK);
  analogWrite(ENB, KECEPATAN_BELOK);   // ← typo asli diperbaiki
  digitalWrite(IN1, LOW);  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH); digitalWrite(IN4, LOW);
}

void belokKanan() {
  analogWrite(ENA, KECEPATAN_BELOK);
  analogWrite(ENB, KECEPATAN_BELOK);
  digitalWrite(IN1, HIGH); digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);  digitalWrite(IN4, HIGH);
}

void stopRobot() {
  digitalWrite(IN1, LOW); digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW); digitalWrite(IN4, LOW);
  analogWrite(ENA, 0);
  analogWrite(ENB, 0);
}