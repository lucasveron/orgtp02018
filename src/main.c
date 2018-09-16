/**
 * Created by gatti2602 on 12/09/18.
 * Main
 */

#define ERROR 0
#define FALSE 0
#define TRUE 1


#include <stdio.h>
#include <string.h>
#include <getopt.h>

#include "command.h"
#include "file.h"
#include "encode.h"

/*enum ParameterState {
	 OKEY = 0, INCORRECT_QUANTITY_PARAMS = 1, INCORRECT_MENU = 2, ERROR_FILE = 3, ERROR_MEMORY = 4
};
*/

/*
 * static char encoding_table[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H',
                                'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P',
                                'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X',
                                'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f',
                                'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n',
                                'o', 'p', 'q', 'r', 's', 't', 'u', 'v',
                                'w', 'x', 'y', 'z', '0', '1', '2', '3',
                                '4', '5', '6', '7', '8', '9', '+', '/'};
 */

/*
 * char* encode(char* buffer){
	unsigned char* buff = (char*)malloc(sizeof(char)*4);
	unsigned char b1 = buffer[0];
	unsigned char b2 = buffer[1];
	unsigned char b3 = buffer[2];

	unsigned char b1aux = b1 >> 2;
	buff[0] = encoding_table[(int)b1aux];
	unsigned char b2aux = b1 << 6;
	b2aux = b2aux >> 2;
	b2aux = b2aux | (b2 >> 4);
	buff[1] = encoding_table[(int)b2aux];
	if(b2 != '\n'){
		if(b3 != '\n'){
			unsigned char b3aux = b3 >> 6;
			unsigned char b3aux2 = b2 << 4;
			b3aux2 = b3aux2 >> 2;
			b3aux = b3aux | b3aux2;
			buff[2] = encoding_table[(int)b3aux];
			unsigned char b4aux = b3 << 2;
			b4aux = b4aux >> 2;
			buff[3] =encoding_table[(int)b4aux];
			return buff;
		}
		unsigned char b3aux = b3 >> 6;
		unsigned char b3aux2 = b2 << 4;
		b3aux2 = b3aux2 >> 2;
		b3aux = b3aux | b3aux2;
		buff[2] = encoding_table[(int)b3aux];
		buff[3] = '=';
		return buff;
	}
	buff[2] = buff[3] = '=';
	return buff;
}
 */

/*
 * Función de conveniencia.
 */
/*
void executeEncode(File* input, File* output) {
	FileOpenForRead(input);
	int ichar = fgetc(input->file);

	FileOpenForWrite(output);

	char buffer[255];
	int i = 0;
	char* buff = (char*)malloc(sizeof(char)*3);
	while(ichar != EOF){

		char character = ichar;
		buffer[i] = character;
		ichar = fgetc(input->file);
		i++;
		if(i == 3){
			buff = Encode(buffer);
			//Escribo en el output.
			fputs(buff,output->file);
			i = 0;
		}
	}
	if(i == 2){
		buff = Encode(buffer);
		fputs(buff,output->file);
	}
	//Cierro los archivos.
	FileClose(input);
	FileClose(output);
}

/*
 * Función de conveniencia.
 */
/*
void executeDecode(File* input, File* output) {
	FileOpenForRead(input);
	int ichar = fgetc(input->file);

		FileOpenForWrite(output);

		char buffer[255];
		int i = 0;
		char* buff = (char*)malloc(sizeof(char)*3);
		while(ichar != EOF){

			char character = ichar;
			buffer[i] = character;
			ichar = fgetc(input->file);
			i++;
			if(i == 4){
				buff = Decode(buffer);
				//Escribo en el output.
				fputs(buff,output->file);
				i = 0;
			}
		}
		//Cierro los archivos.
		FileClose(input);
		FileClose(output);
}
*/
/* TODO: Cambiar options por esto:

 int main(int argc, char* argv[]) {
    static struct option long_options[] = {
            {"input",     required_argument, NULL,  'i'}
    };
    int opt;
    int opt_index = 0;
    while((opt = getopt_long(argc, argv, "i:o:a:h", long_options,&opt_index)) != -1){
        printf("%c: %s\n", opt, optarg);
    }
    return 0;
}

*/


int main(int argc, char** argv) {

    struct option arg_long[] = {
            {"input",   required_argument,  NULL,  'i'},
            {"output",  required_argument,  NULL,  'o'},
            {"action",  required_argument,  NULL,  'a'},
            {"help",    no_argument,        NULL,  'h'},
            {"version", no_argument,        NULL,  'V'},
    };
    char arg_opt_str[] = "i:o:a:hV";
    int arg_opt;
    int arg_opt_idx = 0;

    CommandOptions cmd_opt;
    CommandCreate(&cmd_opt);

    while((arg_opt =
            getopt_long(argc, argv, arg_opt_str, arg_long,&arg_opt_idx)) != -1){
        switch(arg_opt){
        	case 'i': //input file
        		CommandSetInput(&cmd_opt, optarg);
        		break;
        	case 'o':
                CommandSetOutput(&cmd_opt, optarg);
        	case 'h':
        		CommandHelp();
        		break;
        	case 'V':
        		CommandVersion();
        		break;
        	case 'a':
				if(strcmp(optarg,"encode") == 0){
					cmd_opt.encode_opt = CMD_ENCODE;
				} else {
					if(strcmp(optarg,"decode") == 0) {
						cmd_opt.encode_opt = CMD_DECODE;
					} else {
						fprintf(stderr, "Encoding option should be encode/decode");
						cmd_opt.error = TRUE;
					}
				}
				break;
        	default:
        		cmd_opt.error = TRUE;
        		CommandHelp();
        		break;
        }
    }

    return 0;

}
