#include <Servo.h>
#include <LiquidCrystal_I2C.h>
#include <EEPROM.h>
#include <Keypad.h>
Servo motor1;
Servo motor2;
Servo motor3;

LiquidCrystal_I2C lcd(0x27, 16, 2);

const byte ROWS = 4;
const byte COLS = 4;
char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};
byte rowPins[ROWS] = {5, 4, 3, 2};
byte colPins[COLS] = {9, 8, 7, 6};

Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

void setup() {
    Serial.begin(9600);
    motor1.attach(12);
    motor2.attach(11);
    motor3.attach(10);
    lcd.init();
    lcd.backlight();
    lcd.clear();
    lcd.begin(16, 2);
    loading("Cargando");
  }

  

  void loop() {
    // el codigo que quieres que se repita...
  }

  char text(const String& linea1, const String& linea2, int& positionCounter) {
    lcd.clear(); // Borra el contenido actual de la pantalla LCD
    char key = ' '; // Variable de key que esta en blanco
    while (key != '1' && key != '2' && key != '3' && key != '4' && key != '5' && key != '6' && key != '7' && key != '8' && key != '9' && key != '0' && key != 'A' && key != 'B' && key != 'C' && key != 'D' && key != '*' && key != '#') { // Es un bucle hasta que no haya una tecla valida se repetira el bucle
      lcd.clear(); // Borra el contenido
      lcd.setCursor(0, 0); // Establece la posicion la columna 0 y fila 0 del lcd
      lcd.print(linea1.substring(positionCounter)); // Imprime en la pantalla LCD una porcion de la primera linea del mensaje
      lcd.setCursor(0, 1); // Establece la posicion la columna 0 y fila 1 del lcd
      lcd.print(linea2 + ": " + String(key)); // Imprime en la pantalla LCD la segunda linea del mensaje y al lado de los puntos aparecera el valor actual de la tecla
      delay(600); // Retraso de 600ms
      key = keypad.getKey(); // Lee la tecla presionada
      positionCounter++; // Sube el valor del positionCounter en 1 para mover la porcion del texto
      if (positionCounter >= linea1.length()) { // Verifica si ha alcanzado o superado la longitud de la primera linea del mensaje, si es asi se pone otra vez a 0 la variable positionCounter
        positionCounter = 0;
      }
    }

    return key; // Devuelve el valor de la tecla presionada fuera del bucle
  }

  void loading(char msg[]) {
    lcd.setCursor(0, 0); // Se establece en la posicion del cursos en la pantalla LCD en la columna 0 y fila 0.
    lcd.print(msg); // Escribe el mensaje

    for (int i = 0; i < 9; i++) { // Es un bucle for que se repite hasta 9 veces comenzando desde el "i = 0" hasta "i = 8"
      delay(1000); // Retraso de 1s
      lcd.print("."); // Despues del retraso se imprime un punto en la pantalla LCD
    }

    Open(); // Llama a la funcion Open();
  }

  void Open() {
    lcd.clear(); // Limpiamos el lcd
    static int positionCounter = 0; // declaramos una variable de 0 a la posicion de la letra
    char key = ' '; // declaramos una variable que inicia con un valor de un espacion en blanco

    key = text("1. Usuarios   2. Introducir Un Codigo", "Presionar", positionCounter); // Llama a la funcion text y pasa una informacion de texto que muestra las opciones del menú y un mensaje para indicar al usuario que presione una tecla ademas tambien pasa el valor de positioncounter

    switch (key) { // es un interruptor que realiza diferentes acciones segun el valor de la key que es la tecla presionada por el usuario
      case '1': // Si presiona 1 le llevara a otra funcion llamada codigo
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Presiono 1");
        delay(2000);
        lcd.setCursor(0, 1);
        lcd.print("Ing Codigo");
        delay(5000);
        codigo();
        break;
    case '*':
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Mantenimiento");
      lcd.setCursor(0, 1);
      delay(5000);
      lcd.print("*Leer manual*");
      delay(5000);
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("*Leer manual*");
      lcd.setCursor(0, 1);
      lcd.print("*Antes de Usar*");
      delay(5000);
      lcd.clear();
      lcd.print("Contraseña:");
      String password = "";
      while (password.length() < 7) {
      char key = keypad.getKey();
      if (key != NO_KEY) {
      password += key;
      lcd.setCursor(password.length() - 1, 1);
      lcd.print('*');
    }
    delay(100);
  }
  if (password == "1520A5B") {
    manual();
  } else {
    lcd.clear();
    lcd.print("Contraseña");
    lcd.setCursor(0, 1);
    lcd.print("incorrecta");
    delay(5000);
    reboot(); 
  }
  break;
      default:
        break;
    }
  }

  void manual() {
  lcd.clear();
  static int positionCounter = 0;
  char key = ' ';
  key = text("1. Borrar MEM   2. Reboot   3. Mostrar MEM", "Presionar", positionCounter);
  
  switch (key) {
    case '1':
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Seguro?Y(A)/N(D)");
      lcd.setCursor(0, 1);
      char choice;
      while (true) {
        char keyPress = keypad.getKey();
        if (keyPress == 'A' || keyPress == 'D') {
          choice = keyPress;
          break;
        }
        delay(100);
      }

      lcd.print(choice);
      delay(2000);

      switch (choice) {
        case 'A':
          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print("Borrando...");
          borrarEPROM();
          lcd.setCursor(0, 1);
          delay(2000);
          break;
        case 'D':
          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print("Volviendo...");
          lcd.setCursor(0, 1);
          delay(2000);
          return;
      }
      break;
      case '2':
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Reboot");
      delay(5000);
      reboot();
      break;
      case '3':
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Mostrar MEM");
      delay(5000);
      mostrarEEPROM();
      break;
  } 
  delay(1000);
}

  void mostrarEEPROM() {
  int address = 0;
  byte value;

  while (address < EEPROM.length()) {
    value = EEPROM.read(address);
    Serial.print("Address: ");
    Serial.print(address);
    Serial.print(" Value: ");
    Serial.println(value);
    address++;
  }
}

void borrarEPROM() {
  for (int i = 0 ; i < EEPROM.length() ; i++) {
    EEPROM.write(i, 0);
  }
  lcd.clear();
  lcd.print("Ha sido borrado");
  delay(3000);
  reboot();
}

  String codigosDisponibles[] = {
    "AAA54",
    "BBB54",
    "ABC87",
    "BCB09",
    "CCD77",
    "CBC56",
    "900AB",
    "675CC",
    "90A6D",
    "CCC54"
  };

  const int CODIGO_EEPROM_ADDRESS = 120;

  void codigo() {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Ingrese codigo:");

    String codigo = "";
    while (codigo.length() < 5) {
      char key = keypad.getKey();
      if (key) {
        codigo += key;
        lcd.setCursor(codigo.length() - 1, 1);
        lcd.print("*");
      }
    }

    bool codigoValido = false;
    bool codigoUtilizado = false;

    for (int i = 0; i < sizeof(codigosDisponibles) / sizeof(codigosDisponibles[0]); i++) {
      if (codigo == codigosDisponibles[i]) {
        codigoValido = true;
        if (codigosDisponibles[i] == "") {
          codigoUtilizado = true;
        } else {
          codigosDisponibles[i] = "";
          guardarCodigoUtilizado(i);
        }
        break;
      }
    }

    if (codigoValido && !codigoUtilizado && !codigoCanjeado(codigo)) {

      guardarCodigoIngresado(codigo);

      lcd.clear();
      lcd.print("Codigo valido");
      delay(2000);
      servomotores();
    } else {
      lcd.clear();
      lcd.print("Codigo invalido");
      delay(2000);
    }
    reboot();
  }

  void reboot() {
    MCUSR = 0x80;
    asm volatile ("jmp 0");
  }

  void servomotores() {
    lcd.clear();
    static int positionCounter = 0;
    char key = ' ';

    key = text("1. Articulo 1   2. Articulo 2   3. Articulo 3", "Presionar", positionCounter);

    if (key == '1') {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Presiono 1");
      delay(2000);
      lcd.setCursor(0, 1);
      motor1.write(180);
      lcd.print("Articulo 1");
      delay(2000);
      motor1.write(90);
      delay(3000);
      Open();
    } else if (key == '2') {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Presiono 2");
      delay(2000);
      lcd.setCursor(0, 1);
      motor2.write(0);
      lcd.print("Articulo 2");
      delay(2000);
      motor2.write(90);
      delay(3000);
      Open();
      } else if (key == '3') {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Presiono 3");
      delay(2000);
      lcd.setCursor(0, 1);
      motor3.write(180);
      lcd.print("Articulo 3");
      delay(2000);
      motor3.write(90);
      delay(3000);
      Open();
    } else {

    }
  }

  void guardarCodigoUtilizado(int index) {
    String emptyString = "";
    for (int i = 0; i < emptyString.length(); i++) {
      EEPROM.write(CODIGO_EEPROM_ADDRESS + index * emptyString.length() + i, emptyString[i]);
    }
  }

  void guardarCodigoIngresado(const String& codigo) {
    int codigoIndex = CODIGO_EEPROM_ADDRESS / sizeof(String); // Calcula el indice inicial para guardar el codigo en el EEPROM

    while (true) { // El bucle se repetira hasta encontrar una posicion vacia en el EEPROM
      String codigoEnEEPROM; // En esta variable se guarda el codigo ingresado
      for (int i = 0; i < codigo.length(); i++) {
        char byteValue = EEPROM.read(CODIGO_EEPROM_ADDRESS + codigoIndex * codigo.length() + i);
        codigoEnEEPROM += byteValue;
      }

      if (codigoEnEEPROM == "") { // Verifica si la posición en la EEPROM está vacía
        for (int i = 0; i < codigo.length(); i++) { // Guarda el código ingresado en la posición vacía
          EEPROM.write(CODIGO_EEPROM_ADDRESS + codigoIndex * codigo.length() + i, codigo[i]);
        }
        EEPROM.write(CODIGO_EEPROM_ADDRESS + codigoIndex * codigo.length() + codigo.length(), '\0');
        break;
      }
      codigoIndex++; // Pasar a la siguiente posición de memoria en la EEPROM
    }
  }

  bool codigoCanjeado(const String& codigo) {
  int codigoIndex = CODIGO_EEPROM_ADDRESS / sizeof(String);

  while (true) {
    String codigoEnEEPROM;
    for (int i = 0; i < codigo.length(); i++) {
      char byteValue = EEPROM.read(CODIGO_EEPROM_ADDRESS + codigoIndex * codigo.length() + i);
      codigoEnEEPROM += byteValue;
    }

    if (codigoEnEEPROM == codigo) {
      return true; // El código ya ha sido canjeado y está almacenado en la EEPROM
    } else if (codigoEnEEPROM == "") {
      return false; // El código no ha sido canjeado
    }

    codigoIndex++;
  }
}
