#include "Stdio.h"

//#include "SymbolTable.h"

#include "Parser.h"
#include "Scanner.h"
#include <sys/timeb.h>
#include <wchar.h>
#include <iostream>
#include <string>
#include <fstream>
#include "../SymbolTable.h"

using namespace std;

int main(int argc, char* argv[])
{
	if (argc >= 2) {
		ofstream fileStream;
		fileStream.open("MIECCompiler_result", std::fstream::app);
		if (!fileStream.good()) {
			cout << "cant open file to write" << endl;
			return -1;
		}
		fileStream << "MIECCompiler.exe" << endl;
		for (int i = 0; i < argc - 1; i++) {
			std::string fileNameStr(argv[i+1]);
			if (fileNameStr.substr(fileNameStr.find_last_of(".") + 1) == "miec") {
				try{
				
				wchar_t *fileName = coco_string_create(fileNameStr.c_str());
				MIEC::Scanner *scanner = new MIEC::Scanner(fileName);
				MIEC::Parser *parser = new MIEC::Parser(scanner);
				//parser->tab = new MIEC::SymbolTable(parser);
				/*parser->gen = new MIEC::CodeGenerator();*/
				
			
					parser->Parse();				
				
				
				SymbolTable::GetInstance()->PrintTable();
				
				fileStream << fileNameStr;
				if (parser->errors->count == 0) {
					fileStream << ": OK" << endl;
					
					/*parser->gen->Decode();
					parser->gen->Interpret("Taste.IN");*/
				}
				else {
					fileStream << ": FAILED: " << parser->errors->count << " error(s) detected" << endl;
				}
				std::cout << parser->errors->count << std::endl;

				

				coco_string_delete(fileName);
				/*delete parser->gen;
				delete parser->tab;*/
				delete parser;
				delete scanner;
				}
				catch (std::exception ex) {
					cout << ex.what() << endl;
				}
				catch (std::string exStr){
					cout << exStr << endl;
				}

			}
			else {
				std::cout << "wrong file ending (.miec) expected" << std::endl;
			}
		}	

		fileStream.close();
	}
	else {
		std::cout << "-- No source file specified\n" << std::endl;
	}
	

	return 0;
}