/**
 * Created by gatti2602 on 12/09/18.
 * Contiene la logica de cada comando posible de ejecutar
 */

#ifndef TP0_COMMAND_H
#define TP0_COMMAND_H

#include "file.h"

#define CMD_ENCODE 1
#define CMD_DECODE 0
#define CMD_NOENCODE 2
#define FALSE 0
#define TRUE 1

typedef struct {
    File input;
    File output;
    const char* input_route;
    const char* output_route;
    char error;
    char encode_opt;
} CommandOptions;

/**
 * Inicializa TDA CommandOptions
 * Pre: Puntero a Command Options escribible
 * Post: CommandOptions Inicializados a valores por default
 * Valores default:
 *      input: stdin
 *      output stdout
 *      error: FALSE
 *      encode_opt: decode
 */
void CommandCreate(CommandOptions* opt);

/**
 * Setea ruta de entrada
 * Pre: ruta valida
 * Post: ruta lista para abrir file
 */
void CommandSetInput(CommandOptions* opt, const char* input);

/**
 * Setea ruta de salida
 * Pre: ruta valida
 * Post: ruta lista para abrir file
 */
void CommandSetOutput(CommandOptions* opt, const char* output);

/**Setea Command Option
 * Pre: opt inicializado
 * Post: Setea el encoding.
 *      Si string no es encode/decode setea opt error flag.
 */
void CommandSetEncodeOpt(CommandOptions* opt, const char* encode_opt);

/**
 * Devuelve el flag de error
 */
char CommandHasError(CommandOptions *opt);

/**
 * Indica que hubo un error
 */
void CommandSetError(CommandOptions *opt);

/**
 * Ejecuta el comando
 * Pre: Asume parametros previamente validados y ok
 * Post: Ejecuta el comando generando la salida esperada
 *       Devuelve 0 si error y 1 si OK.
 */
char CommandProcess(CommandOptions* opt);

/**
 * Help Command
 * Imprime por salida estandar los distintos comandos posibles.
 * Pre: N/A
 * Post: N/A
 */
void CommandHelp();

/**
 * Imprime la ayuda por la salida de errores
 */
void CommandErrArg();

/**
 * Version Command
 * Imprime por salida estandar la version del codigo
 * Pre: N/A
 * Post: N/A
 */
void CommandVersion();

/**
 * Recibe los archivos abiertos y debe ejecutar la operacion de codificacion
 * Pre: opt->input posee el stream de entrada
 *      opt->output posee el stream de salida
 *      opt->encode_opt posee la opcion de codificacion
 * Post: Datos procesados y escritos en el stream, si error devuelve 0, sino 1.
 */
char _CommandEncodeDecode(CommandOptions *opt);

#endif //TP0_COMMAND_H
