/*

MD Dumper CLI Version
X-death - 07/2024

MD Dumper SDL GUI Version
Jackobo Le Chocobo (Akina Usagi) - 31/08/2024

- Read mode automatic / manual
- Read mode bankswitch

*/

//Operating System Libraries and variables declarations
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//MD Dumper Functions
#include "md_dumper_main.h"
#include "md_dumper_read.h"
#include "md_dumper_write.h"

int main(int argc, char *argv[])
{
    SDL_LogSetPriority(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO); //Display informations on console

	if(argc == 1)
	{
		Display_Help(argv[0]);
		return 1;
	}
    else if (strcmp(argv[1], "-help") == 0)
    {
        Display_Help(argv[0]);
        return 1;
    }

    //Using GUI Mode ?
    if (strcmp(argv[1], "-gui") == 0)
    {
        use_gui=1;
        int quit = 0;
        SDL_Event event;
        int mouse_x, mouse_y;

        //Init Window
        SDL_Init(SDL_INIT_VIDEO);
        SDL_Window * window = SDL_CreateWindow("MD Dumper version 1.0 alpha", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1024, 600, 0);
        SDL_Renderer * renderer = SDL_CreateRenderer(window, -1, 0);

        //Create Background Texture
#if defined(_WIN32)
        SDL_Surface * image = IMG_Load(".\\images\\opts_background.png");
#else
        SDL_Surface * image = IMG_Load("./images/opts_background.png");
#endif
        SDL_Texture * texture = SDL_CreateTextureFromSurface(renderer, image);

        while (quit==0)
        {
            SDL_RenderCopy(renderer, texture, NULL, NULL);

            SDL_SetRenderDrawColor(renderer, 238, 67, 67, 255);
            switch(opts_choice)				//Create GUI Choice Texture
            {
            case 0:						//Read Mode / Game
                for (int x = 81; x <=86; x++)
                    for (int y = 96; y <=101; y++)
                        SDL_RenderDrawPoint(renderer, x, y);
                break;
            case 1:						//Read Mode / Save
                for (int x = 81; x <=86; x++)
                    for (int y = 275; y <=280; y++)
                        SDL_RenderDrawPoint(renderer, x, y);
                break;
            case 2:						//Write Mode / Game
                for (int x = 593; x <=598; x++)
                    for (int y = 96; y <=101; y++)
                        SDL_RenderDrawPoint(renderer, x, y);
                break;
            case 3:						//Write Mode / Save
                for (int x = 593; x <=598; x++)
                    for (int y = 142; y <=147; y++)
                        SDL_RenderDrawPoint(renderer, x, y);
                break;
            }

            SDL_SetRenderDrawColor(renderer, 250, 173, 5, 255);
            switch(dump_mode)				//Create Mode Texture
            {
            case 0:						//Auto Mode
                for (int x = 26; x <=31; x++)
                    for (int y = 116; y <=121; y++)
                        SDL_RenderDrawPoint(renderer, x, y);
                break;
            case 1:						//Manual Mode
                for (int x = 331; x <=336; x++)
                    for (int y = 116; y <=121; y++)
                        SDL_RenderDrawPoint(renderer, x, y);
                break;
            case 2:						//Bankswitch Mode
                for (int x = 173; x <=178; x++)
                    for (int y = 116; y <=121; y++)
                        SDL_RenderDrawPoint(renderer, x, y);
                break;
            }

            switch(dump_manual_size_opts)	//Create Manual Size Texture
            {
            case 0:						//32KB
                for (int x = 26; x <=31; x++)
                    for (int y = 187; y <=192; y++)
                        SDL_RenderDrawPoint(renderer, x, y);
                manual_game_size = 32;
                break;
            case 1:						//64KB
                for (int x = 146; x <=151; x++)
                    for (int y = 187; y <=192; y++)
                        SDL_RenderDrawPoint(renderer, x, y);
                manual_game_size = 64;
                break;
            case 2:						//128KB
                for (int x = 266; x <=271; x++)
                    for (int y = 187; y <=192; y++)
                        SDL_RenderDrawPoint(renderer, x, y);
                manual_game_size = 128;
                break;
            case 3:						//256KB
                for (int x = 386; x <=391; x++)
                    for (int y = 187; y <=192; y++)
                        SDL_RenderDrawPoint(renderer, x, y);
                manual_game_size = 256;
                break;
            case 4:						//512KB
                for (int x = 26; x <=31; x++)
                    for (int y = 203; y <=208; y++)
                        SDL_RenderDrawPoint(renderer, x, y);
                manual_game_size = 512;
                break;
            case 5:						//1024KB
                for (int x = 146; x <=151; x++)
                    for (int y = 203; y <=208; y++)
                        SDL_RenderDrawPoint(renderer, x, y);
                manual_game_size = 1024;
                break;
            case 6:						//2048KB
                for (int x = 266; x <=271; x++)
                    for (int y = 203; y <=208; y++)
                        SDL_RenderDrawPoint(renderer, x, y);
                break;
            case 7:						//4096KB
                for (int x = 386; x <=391; x++)
                    for (int y = 203; y <=208; y++)
                        SDL_RenderDrawPoint(renderer, x, y);
                manual_game_size = 4096;
                break;
            }

            switch(dump_manual_cart_mode_opts)	//Create Manual Cartridge Mode Texture
            {
            case 0:						//Mega Drive Mode
                for (int x = 26; x <=31; x++)
                    for (int y = 245; y <=250; y++)
                        SDL_RenderDrawPoint(renderer, x, y);
                manual_game_cart_mode = 0;
                break;
            case 1:						//Master System Mode
                for (int x = 146; x <=151; x++)
                    for (int y = 245; y <=250; y++)
                        SDL_RenderDrawPoint(renderer, x, y);
                manual_game_cart_mode = 1;
                break;
            }

            switch(write_flash)				//Create Write Mode Opts Texture
            {
            case 1:						//Write Flash
                for (int x = 538; x <=543; x++)
                    for (int y = 116; y <=121; y++)
                        SDL_RenderDrawPoint(renderer, x, y);
                break;
            case 0:						//Erase Flash
                for (int x = 645; x <=650; x++)
                    for (int y = 116; y <=121; y++)
                        SDL_RenderDrawPoint(renderer, x, y);
                break;
            }

            switch(write_save)				//Create Write Mode Opts Texture
            {
            case 1:						//Write Save
                for (int x = 538; x <=543; x++)
                    for (int y = 162; y <=167; y++)
                        SDL_RenderDrawPoint(renderer, x, y);
                break;
            case 0:						//Erase Save
                for (int x = 645; x <=650; x++)
                    for (int y = 162; y <=167; y++)
                        SDL_RenderDrawPoint(renderer, x, y);
                break;
            }

            switch(dump_sram_size_opts)		//Memory size opts
            {
            case 0:						//Automatic
                for (int x = 26; x <=31; x++)
                    for (int y = 318; y <=323; y++)
                        SDL_RenderDrawPoint(renderer, x, y);
                break;
            case 1:						//8192
                for (int x = 146; x <=151; x++)
                    for (int y = 318; y <=323; y++)
                        SDL_RenderDrawPoint(renderer, x, y);
                break;
            case 2:						//32768
                for (int x = 266; x <=271; x++)
                    for (int y = 318; y <=323; y++)
                        SDL_RenderDrawPoint(renderer, x, y);
                break;
            }
            
            switch(sram_type_opts)		//Memory type opts
            {
            case 0:						//Serial SPI
                for (int x = 26; x <=31; x++)
                    for (int y = 356; y <=361; y++)
                        SDL_RenderDrawPoint(renderer, x, y);
                for (int x = 538; x <=543; x++)
                    for (int y = 200; y <=205; y++)
                        SDL_RenderDrawPoint(renderer, x, y);
                break;
            case 1:						//Serial I2C
                for (int x = 146; x <=151; x++)
                    for (int y = 356; y <=361; y++)
                        SDL_RenderDrawPoint(renderer, x, y);
                for (int x = 658; x <=663; x++)
                    for (int y = 200; y <=205; y++)
                        SDL_RenderDrawPoint(renderer, x, y);
                break;
            case 2:						//Parallel SRAM
                for (int x = 266; x <=271; x++)
                    for (int y = 356; y <=361; y++)
                        SDL_RenderDrawPoint(renderer, x, y);
                for (int x = 778; x <=783; x++)
                    for (int y = 200; y <=205; y++)
                        SDL_RenderDrawPoint(renderer, x, y);
                break;
            }

            //Display Texture
            SDL_RenderPresent(renderer);

            SDL_GetMouseState(&mouse_x, &mouse_y);
            SDL_WaitEvent(&event);

            switch (event.type)		//Window Events according to mouse positions and left click on this Window
            {
            case SDL_QUIT:
                quit = 1;
                SDL_DestroyTexture(texture);
                SDL_FreeSurface(image);
                SDL_DestroyRenderer(renderer);
                SDL_DestroyWindow(window);
                SDL_Quit();
                return 1;
            case SDL_MOUSEBUTTONDOWN:
                if(mouse_x>=79  && mouse_x<=88)
                {
                    if (mouse_y>=94  && mouse_y<=103)
                        opts_choice = 0;						//Read Mode  / Game
                    else if (mouse_y>=273 && mouse_y<=282)
                        opts_choice = 1;						//Read Mode  / Save
                }
                else if(mouse_x>=591 && mouse_x<=600)
                {
                    if (mouse_y>=94  && mouse_y<=103)
                        opts_choice = 2;						//Write Mode / Game
                    else if (mouse_y>=140 && mouse_y<=149)
                        opts_choice = 3;						//Write Mode / Save
                }
                else if(mouse_x>=24  && mouse_x<=33 )
                {
                    if (mouse_y>=114 && mouse_y<=123)
                        dump_mode = 0;							//Automatic Mode
                    else if (mouse_y>=185 && mouse_y<=194)
                        dump_manual_size_opts = 0;				//32KB
                    else if (mouse_y>=201 && mouse_y<=210)
                        dump_manual_size_opts = 4;				//512KB
                    else if (mouse_y>=243 && mouse_y<=252)
                        dump_manual_cart_mode_opts = 0;			//Mega Drive Cartridge Mode
                    else if (mouse_y>=316 && mouse_y<=325)
                        dump_sram_size_opts = 0;				//Memory Size : Auto
                    else if (mouse_y>=354 && mouse_y<=363)
                        sram_type_opts = 0;						//Memory Type : Serial SPI
                }
                else if(mouse_x>=329 && mouse_x<=338)
                {
                    if (mouse_y>=114 && mouse_y<=123)
                        dump_mode = 1;							//Manual Mode
                }
                else if(mouse_x>=171 && mouse_x<=180)
                {
                    if (mouse_y>=114 && mouse_y<=123)
                        dump_mode = 2;							//Bankswitch Mode
                }
                else if(mouse_x>=144 && mouse_x<=153)
                {
                    if (mouse_y>=185 && mouse_y<=194)
                        dump_manual_size_opts = 1;				//64KB
                    else if (mouse_y>=201 && mouse_y<=210)
                        dump_manual_size_opts = 5;				//1024KB
                    else if (mouse_y>=243 && mouse_y<=252)
                        dump_manual_cart_mode_opts = 1;			//Master System Cartridge Mode
                    else if (mouse_y>=316 && mouse_y<=325)
                        dump_sram_size_opts = 1;				//Memory Size : 8192
                    else if (mouse_y>=354 && mouse_y<=363)
                        sram_type_opts = 1;						//Memory Type : Serial I2C
                }
                else if(mouse_x>=264 && mouse_x<=273)
                {
                    if (mouse_y>=185 && mouse_y<=194)
                        dump_manual_size_opts = 2;				//128KB
                    else if (mouse_y>=201 && mouse_y<=210)
                        dump_manual_size_opts = 6;				//2048KB
                    else if (mouse_y>=316 && mouse_y<=325)
                        dump_sram_size_opts = 2;				//Memory Size : 32768
                    else if (mouse_y>=354 && mouse_y<=363)
                        sram_type_opts = 2;						//Memory Type : Parallel SRAM
                }
                else if(mouse_x>=384 && mouse_x<=393)
                {
                    if (mouse_y>=185 && mouse_y<=194)
                        dump_manual_size_opts = 3;				//256KB
                    else if (mouse_y>=201 && mouse_y<=210)
                        dump_manual_size_opts = 7;				//4096KB
                }
                else if(mouse_x>=537 && mouse_x<=544)
                {
                    if (mouse_y>=115 && mouse_y<=122)
                        write_flash = 1;						//Write Flash
                    else if (mouse_y>=161 && mouse_y<=168)
                        write_save = 1;							//Write Save
                    else if (mouse_y>=198 && mouse_y<=206)
                        sram_type_opts = 0;						//Memory Type : Serial SPI
                }
                else if(mouse_x>=644 && mouse_x<=651)
                {
                    if (mouse_y>=115 && mouse_y<=122)
                        write_flash = 0;						//Erase Flash
                    else if (mouse_y>=161 && mouse_y<=168)
                        write_save = 0;							//Erase Save
                }
                else if(mouse_x>=656 && mouse_x<=665)
                {
					if (mouse_y>=198 && mouse_y<=206)
                        sram_type_opts = 1;						//Memory Type : Serial I2C
                }
				else if(mouse_x>=776 && mouse_x<=785)
                {
					if (mouse_y>=198 && mouse_y<=206)
                        sram_type_opts = 2;						//Memory Type : Parallel SRAM
                }
                else if(mouse_x>=16 && mouse_x<=199)
                {
                    if(mouse_y>=528 && mouse_y<=559)	//Exit
                    {
                        quit = 1;
                        SDL_DestroyTexture(texture);
                        SDL_FreeSurface(image);
                        SDL_DestroyRenderer(renderer);
                        SDL_DestroyWindow(window);
                        SDL_Quit();
                        return 1;
                    }
                }
                else if(mouse_x>=420 && mouse_x<=603)
                {
                    if(mouse_y>=528 && mouse_y<=559)	//Launch
                    {
                        quit = 1;
                        SDL_DestroyTexture(texture);
                        SDL_FreeSurface(image);
                        SDL_DestroyRenderer(renderer);
                        SDL_DestroyWindow(window);
                        SDL_Quit();
                        break;
                    }
                }
                else if(mouse_x>=824 && mouse_x<=1007)
                {
                    if(mouse_y>=528 && mouse_y<=559)	//Documentation
                    {
                        SDL_Log("Open PDF : TODO\n");
                    }
                }
                break;
            }
        }
    }
    else
    {
        SDL_Log("\n");
        SDL_Log("----------------------------------------------------------------------------\n");
        SDL_Log("8b   d8 888b.      888b. 8    8 8b   d8 888b. 8888 888b.      .d88b 8    888\n");
        SDL_Log("8YbmdP8 8   8      8   8 8    8 8YbmdP8 8  .8 8www 8  .8      8P    8     8\n");
        SDL_Log("8     8 8   8 wwww 8   8 8b..d8 8     8 8wwP' 8    8wwK'      8b    8     8\n");
        SDL_Log("8     8 888P'      888P' `Y88P' 8     8 8     8888 8  Yb wwww `Y88P 8888 888\n");
        SDL_Log("----------------------------------------------------------------------------\n");
        SDL_Log("\n");
        SDL_Log("Release : 1.0 alpha \n");
        SDL_Log("\n");
    }

    //LibUsb : Init & Detect
    if(Detect_Device()!=0)
        return 1;
    
    //LibCsv : Init & Open files
    if(Open_CSV_Files()!=0)
        return 1;

    //Read Game Header/Infos
    Game_Header_Infos();

    // Vérifier le nombre d'arguments
    if(use_gui==0)						//Vérifier que nous utilisons le mode CLI
    {
        //Lecture de la ROM
        if (strcmp(argv[1], "-read_rom") == 0)
		{
            if (strcmp(argv[2], "auto")==0)
            {
				opts_choice=0;
                dump_mode=0;
			}
			else  if (strcmp(argv[2], "manual")==0)
            {
				opts_choice=0;
				dump_mode=1;
                
                if (strcmp(argv[3], "32") == 0)
                {
                    manual_game_size = 32;
                }
                else if (strcmp(argv[3], "64") == 0)
                {
                    manual_game_size = 64;
                }
                else if (strcmp(argv[3], "128") == 0)
                {
                    manual_game_size = 128;
                }
                else if (strcmp(argv[3], "256") == 0)
                {
                    manual_game_size = 256;
                }
                else if (strcmp(argv[3], "512") == 0)
                {
                    manual_game_size = 512;
                }
                else if (strcmp(argv[3], "1024") == 0)
                {
                    manual_game_size = 1024;
                }
                else if (strcmp(argv[3], "2048") == 0)
                {
                    manual_game_size = 2048;
                }
                else if (strcmp(argv[3], "4096") == 0)
                {
                    manual_game_size = 4096;
                }
                else
                {
                    SDL_Log("You must write one of the following values to set the game size : 32, 64, 128, 256, 512, 1024, 2048, 4096.\n");
                    return 1;
                }
                
                if (strcmp(argv[4], "md") == 0)
                {
                    manual_game_cart_mode = 0;
                }
                else if (strcmp(argv[4], "sms") == 0)
                {
                    manual_game_cart_mode = 1;
                }
                else
                {
                    SDL_Log("You must write one of the following values to set the cartridge type : md, sms.\n");
                    return 1;
                }
			}
            else if (strcmp(argv[2], "bankswitch") == 0)
            {
				opts_choice=0;
                dump_mode=2;
            }
            else
			{
                SDL_Log("You must select 'a' (Auto), 'b' (Bankswitch) or 'm' (Manual).\n");
                return 1;
			}
        }
        else if (strcmp(argv[1], "-backup_memory") == 0)
		{
			if (strcmp(argv[2], "0") == 0)
				dump_sram_size_opts = 0;
            else if (strcmp(argv[2], "8192") == 0)
                dump_sram_size_opts = 1;
            else if (strcmp(argv[2], "32768") == 0)
                dump_sram_size_opts = 2;
            else
            {
                SDL_Log("You must write one of the following values to set the save size  : 0 (Auto), 8192, 32768.\n");
                return 1;
            }
            
            if (strcmp(argv[3], "serial_spi") == 0)
				sram_type_opts = 0;
            else if (strcmp(argv[3], "serial_i2c") == 0)
                sram_type_opts = 1;
            else if (strcmp(argv[3], "parallel_sram") == 0)
                sram_type_opts = 2;
            else
            {
                SDL_Log("You must write one of the following values to select the save type : serial_spi, serial_i2c, parallel_sram.\n");
                return 1;
            }
		}
        else if (strcmp(argv[1], "-erase_flash") == 0)
        {
			opts_choice=2;
            write_flash=0;
		}
		else if (strcmp(argv[1], "-write_flash") == 0)
        {
			opts_choice=2;
            write_flash=1;
		}
		else if (strcmp(argv[1], "-erase_memory") == 0)
        {
			opts_choice=3;
            write_save=0;
            
            if (strcmp(argv[2], "serial_spi") == 0)
				sram_type_opts = 0;
            else if (strcmp(argv[2], "serial_i2c") == 0)
                sram_type_opts = 1;
            else if (strcmp(argv[2], "parallel_sram") == 0)
                sram_type_opts = 2;
            else
            {
                SDL_Log("You must write one of the following values to select the save type : serial_spi, serial_i2c, parallel_sram.\n");
                return 1;
            }
		}
		else if (strcmp(argv[1], "-write_memory") == 0)
        {
			opts_choice=3;
            write_save=0;
            
            if (strcmp(argv[2], "serial_spi") == 0)
				sram_type_opts = 0;
            else if (strcmp(argv[2], "serial_i2c") == 0)
                sram_type_opts = 1;
            else if (strcmp(argv[2], "parallel_sram") == 0)
                sram_type_opts = 2;
            else
            {
                SDL_Log("You must write one of the following values to select the save type : serial_spi, serial_i2c, parallel_sram.\n");
                return 1;
            }
		}
        //Erreur
        else
        {
            SDL_Log("You must write '-read_rom', '-backup_memory', '-erase_flash', '-write_flash', '-erase_memory' or '-write_memory' .\n");
            return 1;
        }
    }

    if ( dump_mode==0 && opts_choice==0 )
    {
        return Read_ROM_Auto();
    }
    else if ( dump_mode==1 && opts_choice==0 )
    {
        return Read_ROM_Manual();
    }
    else if ( dump_mode==2 && opts_choice==0 )
    {
        return Read_ROM_Bankswitch();
    }
    else if (opts_choice==1)
    {
        return Read_RAM();
    }
    else if (opts_choice==2 && write_flash==0)
    {
        return Erase_Flash();
    }
    else if (opts_choice==2 && write_flash==1)
    {
        return Write_Flash();
    }
    else if (opts_choice==3 && write_save==1)
    {
        return Erase_RAM();
    }
    else if (opts_choice==3 && write_save==1)
    {
        return Write_RAM();
    }
    return 0;
}


