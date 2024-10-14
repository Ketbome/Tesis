# Configuración de Docker Compose para Algoritmos de Optimización

Este README explica cómo configurar y ejecutar los diversos servicios de algoritmos de optimización utilizando Docker Compose.

## Prerrequisitos

- Docker y Docker Compose instalados en tu sistema
- Recursos de CPU suficientes (se recomiendan al menos 5 núcleos para servicios paralelos)
- Jupyter Notebook instalado (para la comparación de resultados)

## Instrucciones de configuración

1. Descomprime las carpetas de los algoritmos:

   ```
   unzip simulated-annealing.zip
   unzip simulated-annealing-joa.zip
   unzip hill-climbing.zip
   unzip abstaylor.zip
   unzip simulated-annealing-parallel.zip
   unzip hill-climbing-parallel.zip
   unzip simulated-annealing-joa-parallel.zip
   ```

   **Importante:** No reemplaces ningún archivo existente al descomprimir. Si se te pregunta, elige omitir o mantener los archivos existentes.

2. Asegúrate de que el archivo `docker-compose.yml` esté en el mismo directorio que las carpetas descomprimidas.

## Ejecución de los servicios

### Servicios no paralelos

Para ejecutar los servicios no paralelos, utiliza el siguiente comando:

```
docker-compose up -d simulated-annealing simulated-annealing-joa hill-climbing abstaylor
```

### Servicios paralelos

Para ejecutar los servicios paralelos, utiliza los siguientes comandos:

```
docker-compose up -d simulated-annealing-parallel
docker-compose up -d hill-climbing-parallel
docker-compose up -d simulated-annealing-joa-parallel
```

## Monitoreo y logs

Para verificar el estado de los contenedores en ejecución:

```
docker-compose ps
```

Para ver los logs de un servicio específico:

```
docker-compose logs [nombre-del-servicio]
```

Reemplaza `[nombre-del-servicio]` con uno de los siguientes:

- simulated-annealing
- simulated-annealing-joa
- hill-climbing
- abstaylor
- simulated-annealing-parallel
- hill-climbing-parallel
- simulated-annealing-joa-parallel

## Detener los servicios

Para detener todos los servicios en ejecución:

```
docker-compose down
```

Para detener un servicio específico:

```
docker-compose stop [nombre-del-servicio]
```

## Ver resultados en Excel

Después de ejecutar los servicios, para ver los resultados en un archivo Excel, sigue estos pasos:

1. Navega al directorio Data:

   ```
   cd Data
   ```

2. Ejecuta el script bench.py:
   ```
   python bench.py
   ```

Este script generará un archivo Excel con los resultados de los algoritmos de optimización.

## Comparar resultados entre algoritmos

Para comparar los resultados entre dos algoritmos:

1. Navega al directorio Data/test:

   ```
   cd Data/test
   ```

2. Abre el archivo Jupyter Notebook (ipynb) que se encuentra en este directorio:

   ```
   jupyter notebook
   ```

3. En el navegador que se abre, selecciona el archivo .ipynb.

4. Sigue las instrucciones en el notebook para comparar los resultados entre dos algoritmos seleccionados.

## Notas

- Los servicios no paralelos están limitados a 1 núcleo de CPU cada uno.
- Los servicios paralelos pueden utilizar hasta 5 núcleos de CPU cada uno.
- Asegúrate de tener suficientes recursos del sistema disponibles al ejecutar múltiples o todos los servicios simultáneamente.
