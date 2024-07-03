/*
===============================================================================
Código Desarrollado por Mohammed Azzouz.
===============================================================================
*/

#include "ProcesarEntrada.h" // Incluir el archivo de encabezado

void ayuda(const char *programa) {
    printf("Uso: %s <polinomio>\n", programa);
    printf("\n");
    printf("Argumentos:\n");
    printf("  <polinomio>    Polinomio a evaluar.\n");
    printf("                 Ejemplo: %s 3x^5-25x^3+60x+25\n", programa);
    printf("\n");
    printf("Opciones:\n");
    printf("  -p<valor>      Especifica la precisión del intervalo.\n");
    printf("                 Ejemplo: %s 3x^5-25x^3+60x+25 -p0.1\n", programa);
    printf("  -v             Muestra una salida detallada del proceso de cálculo.\n");
    printf("                 Ejemplo: %s 3x^5-25x^3+60x+25 -v\n", programa);
    printf("\n");
}

int calcIntervalos(int coeficientes[], int exponentes[], char simbolos[], int constante, int num_terminos, int* inicio, int* fin, int verbose) {

    //printf("\n---------------------------------\n");
    printf("\033[1;33m\nBusqueda de Intervalo f(a) y f(b)\n\033[0m");
    printf("---------------------------------\n\n");
    printf("Iniciando búsqueda de intervalos donde f(a) y f(b) tengan signos opuestos:\n");

    int inter1 = 1, inter2 = -1;  // Valores iniciales a probar para calcular el intervalo
    int resfinal=0, resfinal2=0;
    int a, b;
    int salto = 0;

    int absoluto, absoluto2;
    int error = 0;
    
    do {

        resfinal = 0; // Reiniciar resultado final para inter1
        resfinal2 = 0; // Reiniciar resultado final para inter2

        //Sustituir X por el valor de los intervalos f(a) y f(b)
        for (int i = 0; i < num_terminos; i++) {
            int ope1 = coeficientes[i] * pow(inter1, exponentes[i]);
            int ope2 = coeficientes[i] * pow(inter2, exponentes[i]);
            
            if (simbolos[i] == '+') {
                resfinal += ope1;
                resfinal2 += ope2;
            } else {
                resfinal -= ope1;
                resfinal2 -= ope2;
            }
        }
        if (simbolos[num_terminos-1]=='+'){
            resfinal += constante;
            resfinal2 += constante;
        } else {
            resfinal -= constante;
            resfinal2 -= constante;
        }

        // Guardar el valor de inter1 en a
        a = inter1;
        // Guardar el valor de inter2 en b
        b = inter2;

        if((resfinal > 0 && resfinal2 > 0) || (resfinal < 0 && resfinal2 < 0)){
            if(verbose){
                printf("\nIntento N%d con intervalos iniciales:\n", salto+1);
                printf("  - Intervalo: \033[1;31m[%d, %d]\n\033[0m", inter1, inter2);
                printf("  - f(a) = %d, f(b) = %d\n", resfinal, resfinal2);
                //printf("\033[1;31mResultado: f(%d) = %d y f(%d) = %d\n\033[0m", inter1, resfinal, inter2, resfinal2);
            }
        } else{
            absoluto = abs(resfinal); // Valores absolutos de los polinomios
            absoluto2 = abs(resfinal2);
            
            //2147329959 || 2147483647 
            if(absoluto>2100000000 || absoluto2>2100000000){ // Si el resultado se pasa del tamaño de un entero descartamos el poliomio
                printf("\n**Este polinomio no cumple con las condiciones de Bolzano.");
                error = 1;

            } else{
                printf("\nIntento N%d con intervalos iniciales:\n", salto+1);
                printf("  - Intervalo: \033[1;32m[%d, %d]\n\033[0m", inter1, inter2);
                printf("  - f(a) = %d, f(b) = %d\n", resfinal, resfinal2);
                printf("\nSe ha encontrado un intervalo donde f(a) y f(b) tienen signos opuestos.\n\n");
            }
        }

        // Ajuste de de valores a probar
        if (salto % 2 == 0) {
            inter2--;
        } else {
            inter1++;
        }

        salto++;
    } while ((resfinal > 0 && resfinal2 > 0) || (resfinal < 0 && resfinal2 < 0));

    printf("\n");

    *inicio = a;
    *fin = b;

    return error;
}

void aproximacionIntervalos(int coeficientes[], int exponentes[], char simbolos[], int constante, int num_terminos, float inter1, float inter2, float precision, int verbose){
	
    printf("\033[1;33mAproximacion de los Intervalos (<%f)\n\033[0m", precision);
    printf("------------------------------------------\n\n");
    printf("Comenzando aproximación de la raíz utilizando el método de bisección:\n\n");

	float diferencia = 1;
	float resInterNuevo, resInterA, resInterB, resFi1, resFi2;
    float  ope2, ope3;

    int contador=1;

	do{

        float mediaIntervalo = (inter1+inter2)/2;

        resInterNuevo = 0;
        resInterA = 0;
        resInterB = 0;

		//Sustituir X por el valor de los intervalos f(a) y f(b)
        for (int i = 0; i < num_terminos; i++) {
            float ope1 = coeficientes[i] * pow(mediaIntervalo, exponentes[i]);

            ope2 = coeficientes[i] * pow(inter1, exponentes[i]);
            ope3 = coeficientes[i] * pow(inter2, exponentes[i]);
            
            if (simbolos[i] == '+') {
                resInterNuevo += ope1;
                resInterA += ope2;
                resInterB += ope3;
            } else {
                resInterNuevo -= ope1;
                resInterA -= ope2;
                resInterB -= ope3;
            }
        }
        if (simbolos[num_terminos-1]=='+'){
            resInterNuevo += constante;
            resInterA += constante;
            resInterB += constante;
        } else {
            resInterNuevo -= constante;
            resInterA -= constante;
            resInterB -= constante;
        }

        if(verbose){
            printf("Iteración %d:\n", contador);
            //Saber que la posicion del intervalo, para mostar al usuario.
            if (inter1>inter2){
                printf("  - Intervalo actual: [%f,%f] | f(a) = %f, f(b) = %f\n",inter2, inter1, resInterA, resInterB);
            } else{
                printf("  - Intervalo actual: [%f,%f] | f(a) = %f, f(b) = %f\n",inter1, inter2, resInterA, resInterB);
            }
            
            printf("  - Evaluación en el punto medio: f(%f) = %f\n", mediaIntervalo, resInterNuevo);
        }

        // Seleccionar qla parte del intervalo valida
        if ((resInterNuevo >0 && resInterA>0)||(resInterNuevo <0 && resInterA<0)){
            diferencia = fabs(inter2 - mediaIntervalo); //Valor absoluto
            inter1 = mediaIntervalo;  // Ajustar inter2 para el próximo intervalo

            if(inter2>mediaIntervalo){

                resFi1=mediaIntervalo;
                resFi2=inter2;
                if(verbose){
                    printf("  - Intervalo actualizado: [%f,%f]\n",mediaIntervalo, inter2);
                    //printf("Como f(b) y f(media) tienen signos opuestos, la raíz está en el intervalo [%f,%f]\n",mediaIntervalo, inter2); //Codigo mas depurado
                }
            } else{

                resFi1=inter2;
                resFi2=mediaIntervalo;

                if(verbose){
                    printf("  - Intervalo actualizado: [%f,%f]\n",inter2 ,mediaIntervalo);
                    //printf("Como f(b) y f(media) tienen signos opuestos, la raíz está en el intervalo [%f,%f]\n", inter2, mediaIntervalo);
                }
            }
            
        }else{
            diferencia = fabs(inter1 - mediaIntervalo);
            inter2 = mediaIntervalo;
            
            if(inter1>mediaIntervalo){

                resFi1=mediaIntervalo;
                resFi2=inter1;

                if(verbose){
                    printf("  - Intervalo actualizado: [%f,%f]\n",mediaIntervalo, inter1);
                    //printf("Como f(a) y f(media) tienen signos opuestos, la raíz está en el intervalo [%f,%f]\n",mediaIntervalo, inter1);
                }

            } else{

                resFi1=inter1;
                resFi2=mediaIntervalo;

                if(verbose){
                    printf("  - Intervalo actualizado: [%f,%f]\n",inter1 ,mediaIntervalo);
                    //printf("Como f(a) y f(media) tienen signos opuestos, la raíz está en el intervalo [%f,%f]\n", inter1, mediaIntervalo);
                }
            }  
        }

        if (diferencia>precision){
            if(verbose){
                printf("\033[1;31m  - Aproximación entre intervalos: %f\n\n\033[0m", diferencia);
            }
        } else{
            if(verbose){
                printf("\033[1;32m  - Aproximación entre intervalos: %f\n\n\033[0m", diferencia);
            }

            printf("\033[0;36mResultado Final:\n\033[0m");
            printf("  - Intervalo donde se encuentra la raíz: \033[1;32m[%f, %f]\n\033[0m", resFi1, resFi2);    
            printf("  - Aproximación entre intervalos: \033[1;32m%f\n\n\033[0m", diferencia);
            printf("Proceso de búsqueda de intervalos y aproximación de la raíz completado con éxito.\n");
            
        }

        contador++;
	} while (diferencia>precision);
}

void bolzano(char ecuacion[50], float precision, int verbose) {

    //printf("Ecuacion original: %s\n\n", ecuacion);

    // Arrays para almacenar coeficientes, exponentes y símbolos
    int coeficientes[20];
    int exponentes[20];
    char simbolos[20];
    int num_terminos = 0;
    int constante = 0;

    // Llamamos a la función para separar términos y llenar los arrays
    separarTerminos(ecuacion, coeficientes, exponentes, simbolos, &constante, &num_terminos);

    if (constante != 0){ //Si hay constante hay que tratar el ultimo valor del array como nulo
        num_terminos--;
    }

    if(verbose){ // Mostrar una salida detallada

        printf("\033[1;33m\nDescomposición del polinomio\n\033[0m");
        printf("----------------------------\n\n");
        // Imprimimos la descomposicion de los coeficientes, exponentes y símbolos 
        printf("Coeficientes:\n");
        for (int i = 0; i < num_terminos; ++i) {
            printf("%d ", coeficientes[i]);
        }
        printf("\n\nExponentes:\n");
        for (int i = 0; i < num_terminos; ++i) {
            printf("%d ", exponentes[i]);
        }
        printf("\n\nSimbolos:\n");
        for (int i = 0; i < num_terminos+1; ++i) {
            printf("%c ", simbolos[i]);
        }
        printf("\n\nLa constante es: %d\n\n", constante);
    }

    int inter1, inter2, error;
    error = calcIntervalos(coeficientes, exponentes, simbolos, constante, num_terminos, &inter1, &inter2, verbose); //calcula el intervalo para los cuales el signo de f(a)!=f(b)
    
    if(error){
        //printf("Gracias por usar el Algoritmo de Bolzano.\n");
    } else{
        aproximacionIntervalos(coeficientes, exponentes, simbolos, constante, num_terminos, inter1, inter2, precision,verbose); //Aproxima el intervalo de f(a) y f(b) hasta que la diferecia sea menor que 0.1
    }
}

int main(int argc, char *argv[]) {
    
    float precision = 0.1;
    int verbose = 0;

    if (argc < 2 || argc > 4) {
        ayuda(argv[0]);
        return 1;
    }

    // Copiar el polinomio pasado como argumento a la variable ecuacion
    char funcion[50];
    strncpy(funcion, argv[1], sizeof(funcion) - 1);
    funcion[sizeof(funcion) - 1] = '\0';

    // Verificar los argumentos opcionales
    for (int i = 2; i < argc; i++) {
        if (strncmp(argv[i], "-p", 2) == 0) {
            // Extrae el valor después de -p
            if (argv[i][2] != '\0') {
                precision = atof(&argv[i][2]);
            } else {
                ayuda(argv[0]);
                return 1;
            }
        } else if (strcmp(argv[i], "-v") == 0) {
            verbose = 1;
        } else {
            ayuda(argv[0]);
            return 1;
        }
    }

    if(precision <= 0.0000015){ // Limitar la precision, para que evitar errores
        printf("Precision muy baja, aumentala");
    } else{
        bolzano(funcion, precision, verbose); // Funcion que realiza el Teorema de Bolzano
    }
    printf("\n----------------------------------------\n");
    printf("\033[1;35mGracias por usar el Algoritmo de Bolzano\033[0m\n");
    printf("----------------------------------------");

    return 0;
}
