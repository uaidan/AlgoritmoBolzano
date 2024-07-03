# 📐 Algoritmo de Bolzano para Encontrar Raíces de Polinomios 📊

¡Bienvenido al proyecto del Algoritmo de Bolzano! Este programa en C implementa un algoritmo eficaz para encontrar raíces de cualquier polinomio utilizando el Teorema de Bolzano.

## ✨ Características

- **Búsqueda de Intervalos:** Identifica intervalos `[a, b]` donde `f(a)` y `f(b)` tienen signos opuestos.
- **Aproximación Excacta:** Calcula intervalos con precisión variable especificada por el usuario, permitiendo una precisión de hasta 0.000002.
- **Visualización Detallada:** Proporciona una salida clara y detallada de cada paso del proceso.
- **Personalización:** Admite opciones de entrada como `-v` para el modo detallado y `-p` para especificar precisión, ofreciendo flexibilidad al usuario.

## 🛠️ Tecnologías Utilizadas

- **C:** Lenguaje de programación utilizado para la lógica del algoritmo y su implementación.
- **stdio.h:** Biblioteca estándar de entrada y salida en C, utilizada para manejar la entrada y salida de datos.
- **stdlib.h:** Proporciona funciones generales de utilidad, incluyendo gestión de memoria dinámica y conversiones numéricas.
- **string.h:** Ofrece funciones para la manipulación de cadenas de caracteres, como copia, concatenación y comparación.
- **math.h:** Biblioteca matemática estándar en C, utilizada para operaciones matemáticas.

## 🚀 Cómo Empezar

1. Clona este repositorio en tu máquina local:
    ```bash
    git clone https://github.com/uaidan/AlgoritmoBolzano.git
    ```
2. Navega al directorio del proyecto:
    ```bash
    cd AlgoritmoBolzano
    ```

### 📚 Compilación

Dependiendo del sistema operativo en el que estés trabajando, la compilación se realiza de diferentes maneras:

- **En Linux:**
    ```bash
    gcc -o bolzanoAlgoritmo bolzanoAlgoritmo.c ProcesarEntrada.c -lm
    ```

- **En Windows:**
    ```bash
    gcc bolzanoAlgoritmo.c ProcesarEntrada.c -o bolzanoAlgoritmo.exe
    ```
    Ten en cuenta que para ejecutar el programa en Windows, es posible que necesites un entorno como Cygwin o MinGW que proporcione un compilador GCC compatible.
  
### ▶️ Ejecución

- **En Linux:**
    ```bash
    ./bolzanoAlgoritmo <polinomio>
    ```

- **En Windows (usando Cygwin o similar):**
    ```bash
    bolzanoAlgoritmo.exe <polinomio>
    ```

## 🎯 Opciones de Línea de Comandos

El programa Algoritmo de Bolzano acepta varias opciones de línea de comandos que te permiten personalizar su ejecución:

- **Especificar Precisión (`-p valor`)**: Esta opción te permite ajustar la precisión deseada para la aproximación de los intervalos. El valor debe ser un número decimal positivo. Por ejemplo:
  
  ```bash
  ./bolzanoAlgoritmo 3x^5-25x^3+60x+25 -p0.05
  ```
  
- **Modo Detallado (`-v`)**: Utiliza esta opción para activar el modo detallado, que proporciona información adicional durante la ejecución del algoritmo. Por ejemplo:
  
  ```bash
  ./bolzanoAlgoritmo 3x^5-25x^3+60x+25 -v
  ```
  
## 🤝 Contribuir

¡Nos encantaría recibir contribuciones para mejorar este proyecto! Si tienes alguna idea o sugerencia, sigue estos pasos:

1. Haz un fork del repositorio.
2. Crea una rama para tu nueva funcionalidad (`git checkout -b feature/nueva-funcionalidad`).
3. Haz tus cambios y haz commit (`git commit -am 'Agrega nueva funcionalidad'`).
4. Sube tus cambios a tu repositorio (`git push origin feature/nueva-funcionalidad`).
5. Abre un Pull Request.

## 📋 Licencia

Este proyecto está licenciado bajo la Licencia MIT. Consulta el archivo `LICENSE` para obtener más detalles.

## 💬 Contacto

Si tienes alguna pregunta o sugerencia, no dudes en ponerte en contacto.

---

¡Gracias por utilizar el Algoritmo de Bolzano! Esperamos que te sea útil para encontrar raíces de polinomios de manera eficaz.

