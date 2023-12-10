## Instalación de Ibex 2.8.9 con Docker-Compose

### Descripción

Este conjunto de instrucciones detalla el proceso de instalación de Ibex 2.8.9 utilizando Docker-Compose. Se ha creado un entorno automatizado y limpio para facilitar la configuración y ejecución de Ibex en contenedores.

### Requisitos

- [Docker](https://www.docker.com)
- [Docker-compose](https://docs.docker.com/compose/)

### Pasos instalación

1. Entrar en la carpeta Trabajo
2. Descomprimir archivos Abstaylor, Hill Climbing, Simulated Annealing
3. Buildear Docker compose:

```bash
docker-compose build
```

4. Dejarlo en segundo plano:

```bash
docker-compose up -d
```

5. Entrar bash de un contenedor:

```bash
docker exec -it [nombre-contenedor] bash
```

6. Configurar Ibex:

```bash
./waf configure --lp-lib=soplex --interval-lib=gaol --lp-lib=soplex
```

7. Instalar Ibex:

```bash
./waf install
```

8. Correr el problema, si quieres guardar los resultados agregar `>> commands.log`:

```bash
./__build__/src/ibexopt benchs/optim/medium/ex14_2_7.bch --random-seed=1 >> commands.log
```
