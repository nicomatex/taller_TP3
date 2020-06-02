# Taller de Programacion I [75.42] - TP3

**Nombre: Nicolas Federico Aguerre**

**Padron: 102145**

**Repositorio: https://github.com/nicomatex/taller_TP3**

**Cuatrimestre: 1C 2020**

---

# Indice del informe
1. **[Sockets](#Sockets)**

2. **[Protocolo](#Protocol)**

3. **[Cliente](#Client)**
    * 3.1. [Comandos](#Commands)

4. **[Servidor](#Server)**
    * 4.1. [Handler de clientes](#ClientHandler)

5. **[Reentrega](#Reentrega)**


---
## 1. Sockets <a name="Sockets"></a>
La base sobre la cual esta construido todo el trabajo practico es la clase ```Socket```. Esta clase encapsula todo el comportamiento relacionado con la interaccion a traves de la red: El establecimiento de la conexion, envio y recepcion de mensajes, aceptacion de nuevas conexiones, etc. La decision de encapsular todo este comportamiento en el Socket se tomo luego de haber implementado una clase Socket con funcionalidades mas basicas (solo enviar y recibir mensajes), dejandole la funcionalidad de establecer la conexion o iniciar la escucha sobre el socket a clases ```servidor_generico``` y ```cliente_generico``` mas especificas. Pero este metodo solo resulto en una complicacion del codigo, y al final se opto por encapsular todo el comportamiento dentro de ```Socket```. 

El tipo de ```Socket``` que se va a instanciar se determina en el momento de la construccion, gracias a una sobrecarga del constructor. Existen tres tipos de constructor para ```Socket```: 

+ Uno que recibe un ```host``` y un ```port```, y que se utiliza para instanciar un ```Socket``` cliente.
+ Uno que recibe solo un ```port``` y se utiliza para instanciar un ```Socket``` acceptor (para el servidor).
+ Uno que recibe un ```socket_filedescriptor```, y se utiliza para instanciar un objeto socket a partir de un file descriptor creado por ```accept()```.

---
## 2. Protocolo <a name="Protocol"></a>
Debido a que los mensajes deben ser serializados en un formato especifico, para no sobrecargar las responsabilidades que ya tienen el cliente y el servidor, el procedimiento de transformar una cierta informacion que se desea enviar a traves de un socket desde el cliente al servidor o viceversa esta encapsulado dentro de la clase ```Protocol```. Esta clase tiene dentro de si un ```Socket```, e implementa todos los metodos necesarios para serializar y enviar a traves del socket todos los mensajes necesarios, como ser ```send_string(std::string)```,```send_int(uint16_t)```,```receive_string()```, etc. 
Para asegurarse de que aquello que se envia a traves de la red siempre sea un mensaje valido, serializado con el protocolo indicado, el cliente y el servidor no estan compuestos directamente por ningun objeto ```Socket```, sino que estan compuestos por un objeto ```Protocol```, y el envio/recepcion de mensajes se hace de forma unica a traves de este. 

![Imagen 1](img/protocol.png?raw=true)

_Imagen 1. Diagrama de Protocol-Socket_

---
## 3. Cliente <a name="Client"></a>
El cliente desarrollado para el presente trabajo práctico es una aplicacion relativamente sencilla. Se trata de un cliente donde el envio y recepcion de datos son manejados de forma sincrónica por el mismo hilo (debido a que no hay necesidad de transmitir y enviar datos de forma concurrente). Como se menciono antes, el ```Client``` encapsula un objeto ```Protocol``` a traves del cual se realiza toda la comunicacion con el servidor. Ademas, ```Client``` esta compuesto tambien por un objeto ```Parser``` que se encarga de generar los objetos ```Command``` a partir de la entrada ```stdin```,que luego le son pasados a ```Protocol``` y enviados por el server. La comprobacion de que el comando ingresado sea valido se realiza en ```Parser```.

**3.1. Comandos**<a name="Commands"></a>

Todos los comandos implementan la interfaz ```Command```, la cual tiene un unico metodo que es ```get_serialization()```, la cual todos los comandos implementan de forma polimorfica. 

![Imagen 2](img/parser_cliente.png?raw=true)

_Imagen 2. Diagrama del parser del cliente_

![Imagen 3](img/client.png?raw=true)

_Imagen 3. Diagrama del cliente_

---
## 4. Servidor <a name="Server"></a>

El servidor es donde esta concentrada toda la logica del juego implementado. Esta compuesto escencialmente por un hilo aceptor, que se encarga de aceptar las conexiones entrantes y lanzar nuevos  hilos handlers de clientes. La necesidad de tener un hilo aceptor nace a partir de la especificacion de que el servidor deber ser capaz de detener inmediatamente la escucha de nuevas conexiones cuando se recibe el comando "q" por entrada estandar. Esta implementacion tambien permite incorporar facilmente nuevos comandos en la interfaz del servidor (como por ejemplo un comando "stats" que muestre las estadisticas hasta el momento, sin cerrar el servidor). 

Para implementar la logica del juego, el servidor posee un objeto ```NumberParser```, que es el encargado de verificar la validez de los numeros ingresados por el cliente (y tambien de los numeros del archivo de numeros pasados al servidor). 

Para almacenar las estadisticas, el servidor tambien encapsula un objeto ```Statistics``` que lleva la cuenta de ganadores y perdedores, y es thread-safe. 

Con cada nueva conexion que llega al servidor, el thread aceptador lanza un nuevo hilo ```PlayerHandler```, y vuelve a la escucha de nuevas conexiones. 

**4.1. Handler de clientes**<a name="ClientHandler"></a>

El Handler de Clientes contiene toda la informacion necesaria para proveerle atender al jugador que se conecto: El numero que este debe adivinar, y metodos preparados para manejar todos los posibles comandos que el cliente pudiera enviar, como ser AYUDA, RENDIRSE o un numero (un intento de adivinar el numero oculto). Debido a que no existe necesidad de enviar y recibir mensajes de forma asíncrona, la recepcion y envio de mensajes se hacen ambas en este mismo hilo. Al igual que el cliente, toda la comunicacion esta encapsulada dentro de un objeto ```Protocol```.

Esta clase tambien tiene una referencia a las ```Statistics``` del servidor, y se encarga de agregar a la cuenta de ganadores o perdedores cuando el cliente que esta manejando gana o pierde el juego. Se adjunta a continuacion un diagrama de clases del Handler.

![Imagen 4](img/client_handler.png?raw=true)

_Imagen 4. Diagrama del PlayerHandler_

Quedando el servidor compuesto de la siguiente forma:

![Imagen 5](img/server.png?raw=true)

_Imagen 5. Diagrama del servidor_

---
## 5. Reentrega <a name="Reentrega"></a>

Para la reentrega del presente trabajo, se realizaron una serie de cambios en el código a bien de solucionar los problemas indicados en la corrección correspondiente a la primera entrega, así como también mejorar la legibilidad general del mismo. El cambio mas sustancial que se hizo fue convertir la clase ```NumberParser``` en una clase común tanto al cliente como al servidor, y que es utilizada para verificar la validez de números ingresados por el usuario. En esta versión, el parser del cliente manifiesta una relación de composición con ```NumberParser```, como se ilustra en el siguiente diagrama. 


![Imagen 6](img/parser_cliente_reentrega.png?raw=true)

_Imagen 6. Diagrama del parser del cliente_


Debido a que se convirtió el metodo ```is_number``` de ```NumberParser``` en un metodo publico, se adjunta a continuación el diagrama de clase del servidor que refleja dicho cambio. 


![Imagen 7](img/server_reentrega.png?raw=true)

_Imagen 7. Diagrama del servidor_
