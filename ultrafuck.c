/*

Что я делаю со своей жизнью...

This is free software released in public domain; see UNLICENSE.txt for further details.

*/

#include "ultrafuck.h"

int main(int argc, char** argv)
{
    if (argc < 2)
    {
        printf("Usage:\nultrafuck <filename> [-c outfilename]\nultrafuck -v\n");
        return 0;
    };

    // -v shows Ultrafuck version

    if (strequ(argv[1], "-v"))
    {
        printf("Ultrafuck %.1f (%s %s) [gcc %s]\n", UF_VERSION, __DATE__, __TIME__, __VERSION__);
        printf("This is free software released in public domain; see UNLICENSE.txt for details.\n");
	printf("https://github.com/AngelOfV0id/Ultrafuck\n");
	return 0;
    };

    // Open file and read all its contents

    char* fn = argv[1];
    FILE* f = fopen(fn, "r");
    if (f == NULL)
    {
        printf("Failed to open '%s' file...\n", fn);
        return 1;
    };

    fseek(f, 0, SEEK_END); long flen = ftell(f); fseek(f, 0, SEEK_SET);
    char code[flen]; for (int i = 0; i < flen; i++) code[i] = fgetc(f);
    fclose(f);

    // -c = convert Brainfuck into Ultrafuck code

    if (argc > 3)
    {
		if (strequ(argv[2], "-c"))
		{
			char* fn2 = argv[3];
			FILE* f2 = fopen(fn2, "w+");
    		
			if (f2 == NULL)
			{
				printf("Failed to open '%s' file...\n", fn2);
				return 1;
			};

			char uf_code[flen * UF_FLEN_MULTIPLY];
			for (int i = 0; i < flen * UF_FLEN_MULTIPLY; i++) uf_code[i] = 0x00;
		    
			for (unsigned int i = 0; i < strlen(code); i++)
			{	
				switch (code[i])
				{
					case '>':
						strcat(uf_code, ">!<"); break;
					case '<':
						strcat(uf_code, ">>!<<"); break;
		    			case '+':
						strcat(uf_code, ">>>!<<<"); break;
		    			case '-':
						strcat(uf_code, ">>>>!<<<<"); break;
		    			case '.':
						strcat(uf_code, ">>>>>!<<<<<"); break;
		    			case ',':
						strcat(uf_code, ">>>>>>!<<<<<<"); break;
		    			case '[':
						strcat(uf_code, "["); break;
		    			case ']':
						strcat(uf_code, "]"); break;
		 	  	};
			};

			uf_code[strlen(code)] = EOF;		    	
	
			int uf_code_len = strlen(uf_code);
		
			for (int i = 0; i < uf_code_len; i++)
			{
				if (uf_code[i] != EOF)
		    			fputc(uf_code[i], f2);
		       		else
		        		break;
			};
		        	
			fclose(f2);

			return 0;
		};
	};

    uf_exec(code);

    printf("\n"); return 0;
}
