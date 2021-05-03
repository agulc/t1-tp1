# CDyM-TE2
Trabajo entregable 2 CDyM

Desarrollo de cerradura electronica
MEF == Maquina de estados Finitos

Diagrama CDU:
  NOTA: Es necesario tener UMLet instalado. Es recomendable el uso de la extension para VSCode (https://marketplace.visualstudio.com/items?itemName=TheUMLetTeam.umlet).
  
  El mismo muestra la interacción del usuario y el tiemo con el sistema.
  
Diagrama MEF:
  NOTA: Es necesario tener UMLet instalado. Es recomendable el uso de la extension para VSCode (https://marketplace.visualstudio.com/items?itemName=TheUMLetTeam.umlet).
  
  Muestra los estados y la reacción a estimulos de la MEF inplementada para las funcionalidades del sistema.
  

Consideraciónes de diseño:
  -¿Una o varias MEF?
      Es posible que sea conveniente tener dos maquinas de estado separadas. Una que maneje el reloj y otra que controle todo lo demas.

  -Lectura del teclado
      podría realizarse una lectura programada cada cierta cantidad de tiempo en una MEF separada, o solo incluir la funcionalidad dentro de 
      la MEF encargada de las funcionalidades
