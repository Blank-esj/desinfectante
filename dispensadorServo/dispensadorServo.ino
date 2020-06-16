// Dispensador con un servo y un rele

// Incluímos la librería para poder controlar el servo
#include <Servo.h>

// Declaramos la variable para controlar el servo
Servo servoMotor;

// Configuramos los pines del sensor Trigger y Echo
const int pinTrigger = 5; // señal de pinTrigger a pin 6
const int pinEcho = 6;    // señal de pinEcho a pin 5

// Configuramos los Reles
const int releJabon = 4; // Relé para el jabón líquido
//const int releAgua = 3;  // Relé para el agua
 
// Constante velocidad sonido en cm/s
const float velocidadSonido = 34000.0;

// Variable que valida que dispensador se activará
boolean dispensarJabon = true;
boolean dispensaraJabon = true;

float distancia;

void setup()
{
  Serial.begin(9600); // Iniciamos el monitor serie para mostrar el resultado

  pinMode(pinTrigger, OUTPUT);   // Ponemos el pin Trigger en modo salida
  pinMode(pinEcho, INPUT);       // Ponemos el pin Echo en modo entrada
  digitalWrite(pinTrigger, LOW); //Inicializamos el pin con 0

  pinMode(releJabon, OUTPUT);  // Ponemos el releJabon en modo salida

  // Iniciamos el servo para que empiece a trabajar con el pin 9
  servoMotor.attach(3);
}

void loop()
{
  iniciarTrigger();

  // La función pulseIn obtiene el tiempo que tarda en cambiar entre estados, en este caso a HIGH
  unsigned long tiempo = pulseIn(pinEcho, HIGH); // Tiempo que tarda la onda en ir y regresar.

  distancia = tiempo * 0.000001 * velocidadSonido / 2.0;

  // Desplazamos a la posición 0º
  servoMotor.write(0);

  // Cuando es la primera vez que se mide < 15cm encienda el releJabon
  // Si es la segunda vez encianda el servo
  if (distancia <= 15.0)
  {
    Serial.print("Dispensando ");
    if (dispensarJabon == true)
    {
      Serial.println("jabon #####");
      digitalWrite(releJabon, HIGH); // Dispensamos jabon

      dispensaraJabon = false;
    }
    else
    {
      Serial.println("agua -----");
      digitalWrite(releJabon, LOW); // Dejamos de dispensar jabon
      
      // Desplazamos a la posición 180º
      servoMotor.write(180);
      // Esperamos 1 segundo
      //delay(1000);

      dispensaraJabon = true;
    }
  }
  else
  {
    // Tiene que haber algo que me diga que he sacado la mano.
    // Dispensar Jaboon es igual a DispensaraJabon
    Serial.println("NO DISPENSA ");
    dispensarJabon = dispensaraJabon;

    // Desplazamos a la posición 0º
    servoMotor.write(0);
    // Esperamos 1 segundo
    //delay(1000);

    digitalWrite(releJabon, LOW); // Dejamos de dispensar jabon
  }

  Serial.println("---------------");
  Serial.print(distancia); //Enviamos serialmente el valor de la distancia
  Serial.println("cm");
  Serial.print("dispensaraJabon: ");
  Serial.println(dispensaraJabon);
  Serial.print("dispensarJabon: ");
  Serial.println(dispensarJabon);
  Serial.println("---------------");
  Serial.println(" ");

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
