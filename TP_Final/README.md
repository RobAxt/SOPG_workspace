# Alumno
i0616 Roberto Oscar Axt

# Enunciado Trabajo práctico
## Objetivo
Escribir un servidor TCP que permite almacenar información ASCII en forma de clave-valor.

El servidor debe:

1. Esperar a que un cliente se conecte mediante el protocolo TCP, puerto 5000.

2. Esperar a que el cliente envíe un comando a ejecutar. El comando se especifica como una secuencia de caracteres ASCII hasta el \n.

3. Realizar la operación correspondiente.

4. Cortar la conexión con el cliente y volver al paso 1.

Los comandos que acepta el servidor son:

* SET <clave> <valor>\n:
  * Se crea en el servidor un archivo llamado <clave> con el contenido indicado en <valor> (sin incluir el \n).
  * Se responde al cliente OK\n.
* GET <clave>:
  * Si existe el archivo correspondiente, se responde al cliente con: OK\n<valor>\n (es decir, una línea de texto que dice OK y otra que contiene el contenido del archivo).
 * Si no existe, se responde con NOTFOUND\n
* DEL <clave>:
  * Si existe la el archivo correspondiente, se elimina.
  * Tanto si existe como no, se responde OK\n.
Ante cualquier caso excepcional, informar la causa y finalizar el proceso con código de error.

## Cliente
Dado que el protocolo de comunicación es ASCII, no es necesario programar un cliente sino que se pueden utilizar herramientas como nc (netcat) o telnet.

En ubuntu se pueden instalar con: apt install netcat o apt install telnet.

## Ejemplo
En la consola #1 (server): ./server

En la consola #2 (client): nc localhost 5000. Si la conexión es exitosa, el proceso se queda esperando a recibir entrada de stdin.

```bash
$ nc localhost 5000
SET manzana apple
OK
$ nc localhost 5000
SET perro dog
OK
$ nc localhost 5000
SET hola hello
OK
$ nc localhost 5000
GET perro
OK
dog
$ nc localhost 5000
GET casa
NOTFOUND
$ nc localhost 5000
DEL perro
OK
$ nc localhost 5000
GET perro
NOTFOUND
$
```

# Proyecto TCP Server

Este proyecto presenta un servidor TCP básico implementado en C, organizado por directorios para facilitar la gestión del código.

## Estructura del Proyecto
```
TP_Final/
├── src/            # Archivos fuente (.c)
├── inc/            # Archivos de encabezado (.h)
├── bin/            # Ejecutables generados
├── Makefile        # Archivo de construcción
└── README.md       # Este archivo
```
## Compilación

Para compilar el proyecto, asegúrate de tener instalado `gcc` y `make`. Luego, simplemente ejecuta el siguiente comando en la terminal dentro de la carpeta del proyecto:

```bash
make
```

## Ejecución

Una vez que el proyecto está compilado, puedes ejecutar el servidor con el siguiente comando:

```bash
make run
```

## Limpieza de Archivos

Si deseas limpiar los archivos compilados y eliminar el contenido del directorio de construcción (bin), ejecuta:

```bash
make clean
```
