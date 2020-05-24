// Configuramos los pines del sensor Trigger y Echo
const int pinTrigger = 6; // señal de pinTrigger a pin 6
const int pinEcho = 5;    // señal de pinEcho a pin 5

// Configuramos los Reles
const int releJabon = 4; // Relé para el jabón líquido
const int releAgua = 3;  // Relé para el agua

// Constante velocidad sonido en cm/s
const float velocidadSonido = 34000.0;

// Variable que valida que dispensador se activará
boolean dispensarJabon = true;

float distancia;

void setup()
{
  Serial.begin(9600); // Iniciamos el monitor serie para mostrar el resultado

  pinMode(pinTrigger, OUTPUT);   // Ponemos el pin Trigger en modo salida
  pinMode(pinEcho, INPUT);       // Ponemos el pin Echo en modo entrada
  digitalWrite(pinTrigger, LOW); //Inicializamos el pin con 0

  pinMode(releJabon, OUTPUT); // Ponemos el releJabon en modo salida
  pinMode(releAgua, OUTPUT);  // Ponemos el releAgua en modo salida
}

void loop()
{
  iniciarTrigger();

  // La función pulseIn obtiene el tiempo que tarda en cambiar entre estados, en este caso a HIGH
  unsigned long tiempo = pulseIn(pinEcho, HIGH); // Tiempo que tarda la onda en ir y regresar.

  distancia = tiempo * 0.000001 * velocidadSonido / 2.0;

  // Cuando es la primera vez que se mide < 15cm encienda el releJabon
  // Si es la segunda vez encianda el releAgua
  if (distancia <= 15.0)
  {
    if (dispensarJabon == true)
    {
      digitalWrite(releJabon, HIGH); // Dispensamos jabon
      dispensarJabon = false;        // Para la siguiente dispensará agua
    }
    else
    {
      digitalWrite(releAgua, HIGH); // Dispensamos agua
      dispensarJabon = true;        // Para la siguiente dispensará jabon líquido
    }
  }
  else
  {
    digitalWrite(releAgua, LOW);  // Dejamos de dispensar agua
    digitalWrite(releJabon, LOW); // Dejamos de dispensar jabon
  }

  Serial.println(distancia); //Enviamos serialmente el valor de la distancia

  delay(750); // Hacemos una pausa de 750ms
}

// Método que inicia la secuencia del Trigger para comenzar a medir
void iniciarTrigger()
{
  // Ponemos el Triger en estado bajo y esperamos 2 ms
  digitalWrite(pinTrigger, LOW);
  delayMicroseconds(2);

  // Ponemos el pin Trigger a estado alto y esperamos 10 ms
  digitalWrite(pinTrigger, HIGH);
  delayMicroseconds(10);

  // Comenzamos poniendo el pin Trigger en estado bajo
  digitalWrite(pinTrigger, LOW);
}
