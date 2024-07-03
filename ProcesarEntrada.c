/*
===============================================================================
Código Desarrollado por Mohammed Azzouz.
Asistido por ChatGPT (OpenAI).
===============================================================================
*/

#include "ProcesarEntrada.h" // Incluir el archivo de encabezado

// Función para separar los términos de la ecuación y almacenar coeficientes, exponentes y símbolos
void separarTerminos(const char *ecuacion, int coeficientes[], int exponentes[], char simbolos[], int *constante, int *num_terminos) {
    char copia[100]; // Copia de la ecuación para trabajar
    strcpy(copia, ecuacion);

    // Verificar si el primer término no tiene un símbolo de + o -
    if (ecuacion[0] != '+' && ecuacion[0] != '-') {
        simbolos[0] = '+';
    } else {
        simbolos[0] = ecuacion[0];
    }

    // Utilizamos strtok para separar por + y -
    char *termino = strtok(copia, "+-");
    int indice = 0;
    
    while (termino != NULL) {
        // Buscamos la posición de 'x' en el término
        char *pos_x = strchr(termino, 'x');
        
        if (pos_x != NULL) {
            // Encontramos 'x', ahora procesamos el coeficiente y el exponente
            int coeficiente;
            int exponente = 1; // Por defecto, si no hay exponente especificado
            
            // Verificamos si el término empieza con 'x' (ej. "x^3")
            if (termino[0] == 'x') {
                coeficiente = 1; // Si no hay coeficiente explícito, se asume 1
                sscanf(termino, "x^%d", &exponente);
            } else {
                // Utilizamos sscanf para extraer coeficiente y exponente
                sscanf(termino, "%dx^%d", &coeficiente, &exponente);
            }
            
            // Guardamos coeficiente y exponente en los arrays
            coeficientes[indice] = coeficiente;
            exponentes[indice] = exponente;
        } else {
            // No hay 'x' en el término, es un término constante
            // Convertimos el término a entero (si es solo un número)
            int valor = atoi(termino);
            
            // Verificamos si es un término al final de la ecuación (puede ser constante o igualdad)
            if (indice == 0 && strchr(termino, '=') != NULL) {
                // Es el término de igualdad, ignoramos
                // Puedes agregar lógica adicional si necesitas manejar este caso específico
            } else {
                // Es una constante normal en la ecuación
                *constante = valor;
            }
        }

        // Verificamos el símbolo siguiente para determinar si es suma (+) o resta (-)
        if (ecuacion[termino - copia + strlen(termino)] == '+') {
            simbolos[indice + 1] = '+';
        } else if (ecuacion[termino - copia + strlen(termino)] == '-') {
            simbolos[indice + 1] = '-';
        }

        // Pasamos al siguiente término
        indice++;
        termino = strtok(NULL, "+-");
    }

    // Actualizamos el número total de términos encontrados
    *num_terminos = indice;
}
