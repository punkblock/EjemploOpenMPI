# Control2 OpenMPI
Control2 de paralela2019 sobre OpenMPI

## Stack de Construcción
Este proyecto está construido sobre la base de estar usando Ubuntu 18.04 LTS de 64 bits y las herramientas usadas fueron

- Make (apt-get install make)
- Gcc  (apt-get install build-essential)
- OpenMPI (apt-get install libopenmpi-dev)

### Construcción
Para construir el proyecto hay que pararse en la carpeta app y ejecutar **make**
Esto construirá un binario  **dist/programa**, que se deberá  distribuirse a todas las máquinas definidas en el archivo maquinas.txt

#### Disclamer
Se utilizó como base de referencia para el control02 https://github.com/sebasalazar/EjemploOpenMPI