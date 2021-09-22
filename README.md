# Taller de Proyecto 1
## _Trabajo Practico 1 - Desarrollo de Cerradura Electronica_

Implementación de una cerradura electronica utilizando como base el microcontrolador STM32F103C6.

  - compatible con STM32F103C8.

![alt text](https://github.com/alcaolpg/t1-tp1/blob/main/Documentacion/Imagenes/imagenmd.jpg?raw=true)

## Caracteristicas

Los requerimientos del sistema son:


  - Cuando el equipo se inicia deberá mostrar en la primer línea del LCD un reloj con formato HH:MM:SS y en la segunda línea el estado de la cerradura “CERRADO”.
  
  - El sistema debe tener la clave numérica guardada por defecto 4321 de manera de poder activar o desactivar la cerradura. Si el usuario presiona la clave correcta se mostrará en la segunda línea “ABIERTO” durante 0.5 seg y luego volverá automáticamente al estado por defecto. Además se deberá activar un LED indicador en un terminal de salida.
  
  - Si la clave es incorrecta se mostrará el estado “DENEGADO” durante 0.2 seg y luego volverá automáticamente al estado por defecto.
  
  - Cuando se presione un tecla numérica se deberá mostrar ‘*’. para indicar que el sistema está recibiendo las entradas. El resto de las teclas no tienen ninguna función.

  - La implementación deberá hacerse aplicando la arquitectura de planificador despachador temporizada con un tick de sistema (sEOS) y desarrollando bibliotecas de funciones básicas para utilizar el LCD y el teclado.
