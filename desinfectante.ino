// Configuramos los pines del sensor Trigger y Echo
int PinTrig = 6; // señal de PinTrig a pin 6
int PinEcho = 5; // señal de PinEcho a pin 5

const int rele = 4; // IN de rele a pin 4

 float distancia;
  
// Constante velocidad sonido en cm/s
const float VelSon = 34000.0;

void setup() 
{
    // Iniciamos el monitor serie para mostrar el resultado
    Serial.begin(9600);
    // Ponemos el pin Trig en modo salida
    pinMode(PinTrig, OUTPUT);
    // Ponemos el pin Echo en modo entrada
    pinMode(PinEcho, INPUT);
    // Ponemos el rele en modo salida
    pinMode(rele,OUTPUT);
}

void loop() 
{
  iniciarTrigger();
  
   // La función pulseIn obtiene el tiempo que tarda en cambiar entre estados, en este caso a HIGH
   unsigned long tiempo = pulseIn(PinEcho, HIGH);
  
    distancia = tiempo * 0.000001 * VelSon / 2.0;
    
    if (distancia <= 15.0){
      digitalWrite(rele, HIGH);
    }else{
      digitalWrite(rele, LOW);
    }
    Serial.println(distancia);
    delay(750);
}

// Método que inicia la secuencia del Trigger para comenzar a medir
void iniciarTrigger()
{
  // Ponemos el Triiger en estado bajo y esperamos 2 ms
  digitalWrite(PinTrig, LOW);
  delayMicroseconds(2);
  
  // Ponemos el pin Trigger a estado alto y esperamos 10 ms
  digitalWrite(PinTrig, HIGH);
  delayMicroseconds(10);
  
  // Comenzamos poniendo el pin Trigger en estado bajo
  digitalWrite(PinTrig, LOW);
}
